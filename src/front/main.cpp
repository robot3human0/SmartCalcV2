#include "mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
//    model model
// controller(&model)
//    MainWindow(controller)
    MainWindow w;
    w.show();
    return a.exec();
}
