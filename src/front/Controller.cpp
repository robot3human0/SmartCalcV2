#include "controller.h"

#include "ui_graph.h"
#include "ui_controller.h"

s21::Controller::Controller(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Controller) {
  ui->setupUi(this);
  setWindowTitle("Myeshask Smart Calculator v2");
  SetValidatorsAndDefaultSettings();
}

s21::Controller::~Controller() { delete ui; }

void s21::Controller::SetValidatorsAndDefaultSettings() {
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
    ui->xMinLine->setText("-1");
    ui->xMaxLine->setText("1");
    ui->yMinLine->setText("-1");
    ui->yMaxLine->setText("1");
}

void s21::Controller::on_equalButton_clicked() {
    model_.SetExpression(ui->mainLineEdit->text().toStdString());
    model_.SetX(ui->xLineEdit->text().toDouble());
    try {
        ui->mainLineEdit->setText(QString::number(model_.Calc()));
        ui->mainLineEdit->setStyleSheet("QLineEdit{background: #73f09d;}");
    } catch(...) {
        ui->mainLineEdit->setText("Error!");
        ui->mainLineEdit->setStyleSheet("QLineEdit{background: #e51e67;}");
    }
}

void s21::Controller::on_printGraphButton_clicked() {
    try {
        graph_ = new s21::Graph();
        graph_->show();
        graph_->setWindowTitle("Grapic");
        model_.SetExpression(ui->mainLineEdit->text().toStdString());
        model_.SetX(ui->xLineEdit->text().toDouble());
        model_.CalculateGraphic(ui->xMinLine->text().toDouble(), ui->xMaxLine->text().toDouble(), ui->yMinLine->text().toDouble(), ui->yMaxLine->text().toDouble());
        xCoordinateVec_ = graph_->GetAddressOfxCoordinatesVec();
        yCoordinateVec_ = graph_->GetAddressOfyCoordinatesVec();
        *xCoordinateVec_ = QVector<double>(model_.GetXPoint()->begin(), model_.GetXPoint()->end());
        *yCoordinateVec_ = QVector<double>(model_.GetYPoint()->begin(), model_.GetYPoint()->end());

        graph_->Draw(ui->xMinLine->text().toDouble(), ui->xMaxLine->text().toDouble(), ui->yMinLine->text().toDouble(), ui->yMaxLine->text().toDouble());
    } catch (const char* err) {
        QMessageBox msg;
        msg.setWindowTitle("Error message");
        msg.setText(err);
        msg.exec();
    }
}
