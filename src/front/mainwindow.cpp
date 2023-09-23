#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->xLineEdit->setValidator(new QDoubleValidator( -1000000000, 1000000000 , 7,this));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_graphButton_clicked()
{
    ui->mainLineEdit->setText("NICE TRY!");
}

