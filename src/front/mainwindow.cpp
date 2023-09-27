#include "mainwindow.h"

#include "ui_graph.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(s21::Controller *controller, QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow), controller_(controller) {
  ui->setupUi(this);
  ui->xLineEdit->setValidator(new QRegularExpressionValidator(
      QRegularExpression("[-+]?[0-9]+(\.[0-9]+)?"), this));
  ui->xMinLine->setValidator(new QRegularExpressionValidator(
      QRegularExpression("[-+]?[0-9]+(\.[0-9]+)?"), this));
  ui->xMaxLine->setValidator(new QRegularExpressionValidator(
      QRegularExpression("[-+]?[0-9]+(\.[0-9]+)?"), this));
  ui->yMinLine->setValidator(new QRegularExpressionValidator(
      QRegularExpression("[-+]?[0-9]+(\.[0-9]+)?"), this));
  ui->yMaxLine->setValidator(new QRegularExpressionValidator(
      QRegularExpression("[-+]?[0-9]+(\.[0-9]+)?"), this));
  ui->xMinLine->setText("-10");
  ui->xMaxLine->setText("10");
  ui->yMinLine->setText("-10");
  ui->yMaxLine->setText("10");
}

MainWindow::~MainWindow() { delete ui; }

void MainWindow::on_graphButton_clicked() {
  try {
    graph_ = new Graph();
    double xs = (ui->xMinLine->text()).toDouble(),
           xl = (ui->xMaxLine->text()).toDouble(),
           ys = (ui->yMinLine->text()).toDouble(),
           yl = (ui->yMaxLine->text()).toDouble();
    controller_->DrowPlot(xs, xl, ys, yl);
    graph_->Draw(xs, xl, ys, yl);
    graph_->show();
  } catch (const std::exception &er) {
    ui->mainLineEdit->setText(er.what());
  }

  if (!graph_->isActiveWindow()) graph_->~Graph();
}

void MainWindow::on_equalButton_clicked() {
  QString expression = ui->mainLineEdit->text();
  QString xValue = ui->xLineEdit->text();
  try {
    ui->mainLineEdit->setText(QString::number((controller_->Calculation(
        expression.toStdString(), xValue.toDouble()))));
  } catch (...) {
    ui->mainLineEdit->setText("Error!");
  }
}
