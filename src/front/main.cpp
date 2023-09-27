#include <QApplication>

#include "mainwindow.h"

int main(int argc, char *argv[]) {
  QApplication a(argc, argv);
  s21::Calculator model;
  s21::Controller controller(&model);
  MainWindow w(&controller);
  w.show();
  return a.exec();
}
