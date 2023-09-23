#ifndef MYLINEEDIT_H
#define MYLINEEDIT_H

#include <QLineEdit>
#include <QObject>
#include <QWidget>
#include <QKeyEvent>

class MyLineEdit : public QLineEdit
{
    Q_OBJECT
public:
    MyLineEdit(QWidget* parent = nullptr);
    void keyPressEvent(QKeyEvent* event) override;
    void returnPressed();
};

#endif // MYLINEEDIT_H
