#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <QMainWindow>
#include <QRegularExpression>
#include <QRegularExpressionValidator>
#include <QMessageBox>
#include "../model/model.h"
#include "graph.h"
#include "mylineedit.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class Controller;
}
QT_END_NAMESPACE

namespace s21 {
class Controller : public QMainWindow {
  Q_OBJECT

 public:
  Controller(QWidget *parent = nullptr);
  ~Controller();
  void SetValidatorsAndDefaultSettings();

 private slots:
  void on_equalButton_clicked();
  void on_printGraphButton_clicked();

private:
  Ui::Controller *ui;
  s21::Graph *graph_;
  s21::Calculator model_;
  QVector<double> *xCoordinateVec_;
  QVector<double> *yCoordinateVec_;
};
}
#endif  // CONTROLLER_H
