#include <QApplication>

#include "controller.h"

int main(int argc, char *argv[]) {
  QApplication a(argc, argv);
  s21::Controller w;
  w.show();
  return a.exec();
}
