#include "model.h"

s21::Token::Token(const std::string& name, Precedence precedence,
                  Associativity associativity, Type type, FuVariant function)
    : name_(name),
      precedence_(precedence),
      associativity_(associativity),
      type_(type),
      function_(function) {}

std::string s21::Token::GetName() { return name_; }
s21::Precedence s21::Token::GetPrecedence() { return precedence_; }
s21::Associativity s21::Token::GetAssociativity() { return associativity_; }
s21::Type s21::Token::GetType() { return type_; }
s21::FuVariant s21::Token::GetFuVariant() { return function_; }

s21::Calculator::Calculator() : x_(0), expression_("") {}
s21::Calculator::Calculator(const std::string expression, const double x)
    : x_(x), expression_(expression) {}

double s21::Calculator::GetAnswer() { return answer_; }
std::string s21::Calculator::GetExpression() { return expression_; }
double s21::Calculator::GetX() { return x_; }
void s21::Calculator::SetX(const double newX) { x_ = newX; }
void s21::Calculator::SetExpression(const std::string newExpression) {
  expression_ = newExpression;
}

double s21::Calculator::Calc() {
  if (expression_.empty()) throw "Error: The Expression is Empty!";
  std::transform(expression_.begin(), expression_.end(), expression_.begin(),
                 ::tolower);
  expression_.erase(std::remove(expression_.begin(), expression_.end(), ' '),
                    expression_.end());
  expression_.erase(std::remove(expression_.begin(), expression_.end(), '\t'),
                    expression_.end());
  IsBracketsPaired();
  CreateTokenMap();
  FindUnaryOperatorsAndAddAZero();
  Validate();
  MakeCalculation();
  GetAnswer();
  return answer_;
}

void s21::Calculator::CalculateGraphic(double xMin, double xMax, double yMin,
                                       double yMax) {
  xDotCoordinates_.reserve(20000);
  yDotCoordinates_.reserve(20000);
  xDotCoordinates_.clear();
  yDotCoordinates_.clear();
  if (xMin > xMax) std::swap(xMin, xMax);
  if (yMin > yMax) std::swap(yMin, yMax);
  double limit = yMax - yMin;
  double step = (xMax - xMin) / 150;
  double currentXPoint = xMin;
  double currentYPoint = 0;
  while (currentXPoint <= xMax) {
    SetX(currentXPoint);
    xDotCoordinates_.push_back(currentXPoint);
    currentYPoint = Calc();
    if (currentYPoint < yMin - limit || currentYPoint > yMax + limit)
      currentYPoint = NAN;
    yDotCoordinates_.push_back(currentYPoint);
    currentXPoint += step;
  }
}

std::vector<double>* s21::Calculator::GetXPoint() { return &xDotCoordinates_; }

std::vector<double>* s21::Calculator::GetYPoint() { return &yDotCoordinates_; }

void s21::Calculator::IsBracketsPaired() {
  size_t correctSequenceBrackets = 0;
  size_t brackets = 0;
  std::string::iterator iter = expression_.begin();
  while (iter < expression_.end()) {
    if (*iter == '(') {
      ++brackets;
      correctSequenceBrackets = 1;
    }
    if (*iter == ')') {
      --brackets;
      correctSequenceBrackets = 2;
    }
    if (*iter == ',') *iter = '.';
    ++iter;
  }
  if (brackets != 0) throw "Error: Unpaired bracket!";
  if (correctSequenceBrackets == 1) throw "Error: Wrong sequence or brackets!";
}

void s21::Calculator::FindUnaryOperatorsAndAddAZero() {
  bool beginnig = true;
  std::string newLine;
  std::string::iterator iter = expression_.begin();
  while (iter < expression_.end()) {
    if ((*iter == '-' || *iter == '+') && beginnig) {
      newLine += "0";
      newLine += *iter;
    } else if (*iter == '(' && (*(iter + 1) == '-' || *(iter + 1) == '+')) {
      newLine += *iter;
      newLine += "0";
    } else {
      newLine += *iter;
    }
    beginnig = false;
    ++iter;
  }
  newLine += '\n';
  expression_ = newLine;
}

void s21::Calculator::Validate() {
  std::regex const basicRegex(
      R"(x|sin|cos|tan|acos|asin|atan|sqrt|ln|log|mod|\+|\-|\*|\/|\(|\)|\^|\d+(\.\d+)?[e][-+]?\d+|\d+\.\d+|\d+)");
  std::smatch result;
  std::string copy_expression(expression_);
  while (std::regex_search(copy_expression, result, basicRegex)) {
    std::string lexeme = result.str();
    copy_expression = result.suffix().str();
    ToRPN(lexeme);
  }
  while (!operators_.empty()) {
    rpnLine_.push(operators_.top());
    operators_.pop();
  }
}

void s21::Calculator::ToRPN(const std::string& lexeme) {
  if (isdigit(lexeme[0])) {  // если число
    rpnLine_.push(s21::Token(lexeme, Zero, Nope, Num, std::stod(lexeme)));
  } else if (lexeme == "x") {  // если х
    rpnLine_.push(tokenMap_.find(lexeme)->second);
  } else {  // все прочее
    s21::Token token(tokenMap_.find(lexeme)->second);
    if (token.GetPrecedence() == rBracket) {  // если правая скобка
      while (operators_.top().GetPrecedence() != lBracket) {
        rpnLine_.push(operators_.top());
        operators_.pop();
      }
      operators_.pop();
    } else if (operators_.empty()  // если операторы пусты
               || token.GetPrecedence() == lBracket  // или левая скобка
               || token.GetPrecedence() >
                      operators_.top().GetPrecedence()) {  // или токен больше
                                                           // чем токен в операх
      operators_.push(token);
    } else if (token.GetPrecedence() <=
               operators_.top()
                   .GetPrecedence()) {  // если токен меньше или равен оперному
      while (!operators_.empty()) {
        if (token.GetPrecedence() <= operators_.top().GetPrecedence() &&
            token.GetName() != "^") {
          rpnLine_.push(operators_.top());
          operators_.pop();
        } else {
          break;
        }
      }
      operators_.push(token);
    }
  }
}

void s21::Calculator::CreateTokenMap() {
  std::initializer_list<std::pair<const std::string, s21::Token>> list = {
      {"+", s21::Token("+", s21::Precedence::Low, s21::Associativity::Left,
                       s21::Type::oBinary, std::plus<double>())},
      {"-", s21::Token("-", s21::Precedence::Low, s21::Associativity::Right,
                       s21::Type::oBinary, std::minus<double>())},
      {"*", s21::Token("*", s21::Precedence::Medium, s21::Associativity::Left,
                       s21::Type::oBinary, std::multiplies<double>())},
      {"/", s21::Token("/", s21::Precedence::Medium, s21::Associativity::Right,
                       s21::Type::oBinary, std::divides<double>())},
      {"^", s21::Token("^", s21::Precedence::High, s21::Associativity::Right,
                       s21::Type::oBinary, powl)},
      {"cos", s21::Token("cos", s21::Precedence::Ultra,
                         s21::Associativity::Right, s21::Type::oUnary, cosl)},
      {"sin", s21::Token("sin", s21::Precedence::Ultra,
                         s21::Associativity::Right, s21::Type::oUnary, sinl)},
      {"tan", s21::Token("tan", s21::Precedence::Ultra,
                         s21::Associativity::Right, s21::Type::oUnary, tanl)},
      {"acos", s21::Token("acos", s21::Precedence::Ultra,
                          s21::Associativity::Right, s21::Type::oUnary, acosl)},
      {"asin", s21::Token("asin", s21::Precedence::Ultra,
                          s21::Associativity::Right, s21::Type::oUnary, asinl)},
      {"atan", s21::Token("atan", s21::Precedence::Ultra,
                          s21::Associativity::Right, s21::Type::oUnary, atanl)},
      {"sqrt", s21::Token("sqrt", s21::Precedence::Ultra,
                          s21::Associativity::Right, s21::Type::oUnary, sqrtl)},
      {"ln", s21::Token("ln", s21::Precedence::Ultra, s21::Associativity::Right,
                        s21::Type::oUnary, logl)},
      {"log", s21::Token("log", s21::Precedence::Ultra,
                         s21::Associativity::Right, s21::Type::oUnary, log10l)},
      {"mod", s21::Token("mod", s21::Precedence::Medium,
                         s21::Associativity::Left, s21::Type::oBinary, fmodl)},
      {"(", s21::Token("(", s21::Precedence::lBracket, s21::Associativity::Nope,
                       s21::Type::Bracket, nullptr)},
      {")", s21::Token(")", s21::Precedence::rBracket, s21::Associativity::Nope,
                       s21::Type::Bracket, nullptr)},
      {"x", s21::Token("x", s21::Precedence::Zero, s21::Associativity::Nope,
                       s21::Type::Num, nullptr)},
  };
  tokenMap_.insert(list);
}

void s21::Calculator::MakeCalculation() {
  if (rpnLine_.empty()) throw "Error: Invalid Expression!";
  s21::Associativity associativity = rpnLine_.front().GetAssociativity();
  std::string name;
  while (!rpnLine_.empty()) {
    name = rpnLine_.front().GetName();
    std::visit(overloaded{
                   [&](double function) {
                     numbers_.push(function);
                     rpnLine_.pop();
                   },
                   [&](s21::fUnary function) {
                     double num = PopFromNumbers_Stack(&numbers_);
                     numbers_.push(function(num));
                     rpnLine_.pop();
                   },
                   [&](s21::fBinary function) {
                     double rightArg = PopFromNumbers_Stack(&numbers_);
                     double leftArg = PopFromNumbers_Stack(&numbers_);
                     if (associativity == Right) {
                       if (name == "/" && rightArg == 0)
                         throw "Error: Division by Zero is Not Allowed!";
                       numbers_.push(function(leftArg, rightArg));
                     } else {
                       numbers_.push(function(rightArg, leftArg));
                     }
                     rpnLine_.pop();
                   },
                   [&](auto) {
                     numbers_.push(x_);
                     rpnLine_.pop();
                   },
               },
               rpnLine_.front().GetFuVariant());
    associativity = rpnLine_.front().GetAssociativity();
  }
  if (numbers_.size() != 1) throw "Error: Invalid Expression";
  answer_ = numbers_.top();
  numbers_.pop();
}

double s21::Calculator::PopFromNumbers_Stack(std::stack<double>* stack) {
  if (stack->empty()) throw "Error: Invalid Expression!";
  double value = stack->top();
  stack->pop();
  return value;
}

void s21::Calculator::CleanAllStacksLinesAndVectors() {
  std::stack<s21::Token> cleanStack;
  std::swap(operators_, cleanStack);
  std::stack<double> cleanStack2;
  std::swap(numbers_, cleanStack2);
  std::queue<s21::Token> clean_pnLine;
  std::swap(rpnLine_, clean_pnLine);
  xDotCoordinates_.clear();
  yDotCoordinates_.clear();
}
