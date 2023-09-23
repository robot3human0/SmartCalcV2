#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QKeyEvent>
#include <QDoubleValidator>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
//    MainWindow(Controller *imya) : imya(imya_);
    ~MainWindow();

private slots:
    void on_graphButton_clicked();
//    Controller *imya_;
private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
