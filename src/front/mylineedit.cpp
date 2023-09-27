#include "mylineedit.h"

MyLineEdit::MyLineEdit(QWidget* parent) : QLineEdit(parent) {}

void MyLineEdit::keyPressEvent(QKeyEvent* event) {
  if (event->text() == "c") setText(text() + "cos(");
  if (event->text() == "s") setText(text() + "sin(");
  if (event->text() == "t") setText(text() + "tan(");
  if (event->text() == "C") setText(text() + "acos(");
  if (event->text() == "S") setText(text() + "asin(");
  if (event->text() == "T") setText(text() + "atan(");
  if (event->text() == "q") setText(text() + "sqrt(");
  if (event->text() == "l") setText(text() + "ln(");
  if (event->text() == "L") setText(text() + "log(");
  if (event->text() == "%") setText(text() + "%");
  if (event->text() == "^") setText(text() + "^");
  if (event->text() == "1") setText(text() + "1");
  if (event->text() == "2") setText(text() + "2");
  if (event->text() == "3") setText(text() + "3");
  if (event->text() == "4") setText(text() + "4");
  if (event->text() == "5") setText(text() + "5");
  if (event->text() == "6") setText(text() + "6");
  if (event->text() == "7") setText(text() + "7");
  if (event->text() == "8") setText(text() + "8");
  if (event->text() == "9") setText(text() + "9");
  if (event->text() == "0") setText(text() + "0");
  if (event->text() == "(") setText(text() + "(");
  if (event->text() == ")") setText(text() + ")");
  if (event->text() == "+") setText(text() + "+");
  if (event->text() == "-") setText(text() + "-");
  if (event->text() == "*") setText(text() + "*");
  if (event->text() == "/") setText(text() + "/");
  if (event->text() == ".") setText(text() + ".");
  if (event->text() == "x") setText(text() + "x");
  if (event->key() == Qt::Key_Delete) clear();
  if (event->key() == Qt::Key_Backspace) backspace();
}
