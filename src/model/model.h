#ifndef MODEL_H
#define MODEL_H

#include <cmath>
#include <functional>
#include <iomanip>
#include <iostream>
#include <list>
#include <map>
#include <queue>
#include <regex>
#include <stack>
#include <string>
#include <variant>
#include <vector>

namespace s21 {
template <class... Ts>
struct overloaded : Ts... {
  using Ts::operator()...;
};

template <class... Ts>
overloaded(Ts...) -> overloaded<Ts...>;

enum Precedence {
  Zero,      // числа, скобки, все что не функция
  lBracket,  // левая скобка
  Low,       // плюс,минус
  Medium,  // умножить поделить остаток от деления
  High,    // возведение в степень
  Ultra,     // функция
  rBracket,  // правая скобка
};

enum Associativity {
  Nope,
  Left,   // минус деление остаток от деления
  Right,  // степень
};

enum Type {
  Num,      // число
  oBinary,  // бинарный оператор
  oUnary,   // унарный оператор
  Bracket,
};

using fUnary = std::function<double(double)>;
using fBinary = std::function<double(double, double)>;
using FuVariant = std::variant<double, fUnary, fBinary, std::nullptr_t>;

class Token {
 public:
  Token() = default;
  Token(const std::string& name, Precedence precedence,
        Associativity associativity, Type type, FuVariant function);
  ~Token() = default;

  std::string GetName();
  Precedence GetPrecedence();
  Associativity GetAssociativity();
  Type GetType();
  FuVariant GetFuVariant();

 private:
  std::string name_;
  Precedence precedence_;
  Associativity associativity_;
  Type type_;
  FuVariant function_;
};

class Calculator {
 public:
  Calculator();
  Calculator(const std::string expression, const double x);
  ~Calculator() = default;

  double GetAnswer();
  std::string GetExpression();
  double GetX();
  void SetX(const double newX);
  double Calc();
  void CalculateGraphic(double xMin, double xMax, double yMin, double yMax);
  void SetExpression(const std::string newExpression);
  std::vector<double>* GetXPoint();
  std::vector<double>* GetYPoint();
  void CleanAllStacksLinesAndVectors();

 private:
  void Validate();
  void IsBracketsPaired();
  void CreateTokenMap();
  void MakeCalculation();
  void ToRPN(const std::string& lexeme);
  void FindUnaryOperatorsAndAddAZero();
  double PopFromNumbers_Stack(std::stack<double>* stack);

  double answer_;
  double x_;
  std::string expression_;
  std::stack<double> numbers_;
  std::stack<s21::Token> operators_;
  std::queue<s21::Token> rpnLine_;
  std::map<std::string, s21::Token> tokenMap_;
  std::vector<double> xDotCoordinates_;
  std::vector<double> yDotCoordinates_;
};

}  // namespace s21

#endif  // MODEL_H
