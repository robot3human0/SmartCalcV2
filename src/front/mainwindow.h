#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QKeyEvent>
#include <QMainWindow>
#include <QRegularExpression>
#include <QRegularExpressionValidator>

#include "../controller/controller.h"
#include "../model/model.h"
#include "graph.h"
#include "mylineedit.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
  Q_OBJECT

 public:
  MainWindow(s21::Controller *controller, QWidget *parent = nullptr);
  ~MainWindow();

 private slots:
  void on_equalButton_clicked();

  void on_graphButton_clicked();

 private:
  Ui::MainWindow *ui;
  Graph *graph_;
  s21::Calculator *model_;
  s21::Controller *controller_;
};

#endif  // MAINWINDOW_H
