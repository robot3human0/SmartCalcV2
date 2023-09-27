#ifndef MYLINEEDIT_H
#define MYLINEEDIT_H

#include <QKeyEvent>
#include <QLineEdit>
#include <QObject>
#include <QWidget>

class MyLineEdit : public QLineEdit {
  Q_OBJECT
 public:
  MyLineEdit(QWidget* parent = nullptr);
  void keyPressEvent(QKeyEvent* event) override;
};

#endif  // MYLINEEDIT_H
