
#include <gtest/gtest.h>

#include "model/model.h"

TEST(TokenTest, GetName) {
  s21::Token token("name", s21::Precedence::Low, s21::Associativity::Left,
                   s21::Type::Num, nullptr);
  EXPECT_EQ(token.GetName(), "name");
  EXPECT_EQ(token.GetType(), s21::Type::Num);
}

TEST(CalculatorTest, Creation) {
  s21::Calculator calcuta;
  double res = calcuta.GetX();
  const std::string s;
  EXPECT_EQ(calcuta.GetExpression(), s);
  EXPECT_DOUBLE_EQ(res, 0.0);
}

TEST(CalculatorTest, SetNewExpressionAndX) {
  s21::Calculator calcuta;
  double newx = 6;
  std::string newExp = "2+2*2";
  calcuta.SetExpression(newExp);
  calcuta.SetX(newx);
  EXPECT_EQ(calcuta.GetExpression(), newExp);
  EXPECT_DOUBLE_EQ(calcuta.GetX(), newx);
}

TEST(CalculatorTest, Addition) {
  s21::Calculator calculator("2+2", 0);
  double result = calculator.Calc();
  EXPECT_DOUBLE_EQ(result, 4.0);
}

TEST(CalculatorTest, Subtraction) {
  s21::Calculator calculator("5-3", 0);
  double result = calculator.Calc();
  EXPECT_DOUBLE_EQ(result, 2.0);
}

TEST(CalculatorTest, Multiplication) {
  s21::Calculator calculator("4*3", 0);
  double result = calculator.Calc();
  EXPECT_DOUBLE_EQ(result, 12.0);
}

TEST(CalculatorTest, Division) {
  s21::Calculator calculator("10/2", 0);
  double result = calculator.Calc();
  EXPECT_DOUBLE_EQ(result, 5.0);
}

TEST(CalculatorTest, Exponentiation) {
  s21::Calculator calculator("2^3^2", 0);
  double result = calculator.Calc();
  EXPECT_DOUBLE_EQ(result, 512.0);
}

TEST(CalculatorTest, TrigonometricFunction) {
  s21::Calculator calculator("sin(x)", 0);
  double result = calculator.Calc();
  EXPECT_DOUBLE_EQ(result, 0.0);
}

TEST(CalculatorTest, Logarithm) {
  s21::Calculator calculator("log(x)", 100);
  double result = calculator.Calc();
  EXPECT_DOUBLE_EQ(result, 2.0);
}

TEST(CalculatorTest, SquareRoot) {
  s21::Calculator calculator("sqrt(x)", 16);
  double result = calculator.Calc();
  EXPECT_DOUBLE_EQ(result, 4.0);
}

TEST(CalculatorTest, MultipleOperators) {
  s21::Calculator calculator("2+3*4", 0);
  double result = calculator.Calc();
  EXPECT_DOUBLE_EQ(result, 14.0);
}

TEST(CalculatorTest, Parentheses) {
  s21::Calculator calculator("(2+3)*4/x", 5);
  double result = calculator.Calc();
  EXPECT_DOUBLE_EQ(result, 4.0);
}

TEST(CalculatorTest, NegativeNumber) {
  s21::Calculator calculator("-5+3.4", 0);
  double result = calculator.Calc();
  calculator.CleanAllStacksLinesAndVectors();
  EXPECT_DOUBLE_EQ(result, -1.6);
}

TEST(CalculatorTest, DecimalNumbers) {
  s21::Calculator calculator("1.3+2.7", 0);
  double result = calculator.Calc();
  EXPECT_DOUBLE_EQ(result, 4.0);
}

TEST(CalculatorTest, ScientificNotation) {
  s21::Calculator calculator("2e3+1e2", 0);
  double result = calculator.Calc();
  EXPECT_DOUBLE_EQ(result, 2100.0);
}

TEST(CalculatorTest, MultipleFunctions) {
  s21::Calculator calculator("sin(cos(x))", 0);
  double result = calculator.Calc();
  EXPECT_DOUBLE_EQ(result, 0.8414709848078965);
}

TEST(CalculatorTest, ComplexExpression) {
  s21::Calculator calculator("2*(3+4)-5/2", 0);
  double result = calculator.Calc();
  EXPECT_DOUBLE_EQ(result, 11.5);
}

TEST(CalculatorTest, InvalidExpression) {
  s21::Calculator calculator("2++2", 0);
  EXPECT_ANY_THROW(calculator.Calc());
}

TEST(CalculatorTest, UnpairedBrackets) {
  s21::Calculator calculator("(2+3", 0);
  EXPECT_ANY_THROW(calculator.Calc());
}

TEST(CalculatorTest, ErrorBrackets) {
  s21::Calculator calculator("(2+3))(", 0);
  EXPECT_ANY_THROW(calculator.Calc());
}

TEST(CalculatorTest, DivisionByZero) {
  s21::Calculator calculator("5/0", 0);
  EXPECT_ANY_THROW(calculator.Calc());
}

TEST(CalculatorTest, EmptyExpression) {
  s21::Calculator calculator;
  EXPECT_ANY_THROW(calculator.Calc());
}

TEST(GraphCalculation, MakeGraph) {
  s21::Calculator calculator("tan(x)", 1);
  calculator.CalculateGraphic(1, 1.3, 1, 1.3);
  std::vector<double> *x = calculator.GetXPoint();
  std::vector<double> *y = calculator.GetYPoint();
  std::vector<double> originalX = {1,     1.002, 1.004, 1.006,
                                   1.008, 1.01,  1.012, 1.014};
  std::vector<double> originalY = {1.5574077246549023, 1.5642801778832955,
                                   1.5711957678946682, 1.5781549579556347,
                                   1.5851582178947465, 1.5922060242195704,
                                   1.599298860236279};
  for (int i = 0; i < 7; ++i) {
    EXPECT_DOUBLE_EQ(originalX[i], (*x)[i]);
    EXPECT_DOUBLE_EQ(originalY[i], (*y)[i]);
  }
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
