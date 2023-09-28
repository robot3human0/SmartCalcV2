#ifndef GRAPH_H
#define GRAPH_H

#include <QWidget>

#include "qcustomplot.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class Graph;
}
QT_END_NAMESPACE

namespace s21 {
class Graph : public QWidget {
  Q_OBJECT

 public:
  explicit Graph(QWidget *parent = nullptr);
  ~Graph();
  QVector<double> *GetAddressOfxCoordinatesVec();
  QVector<double> *GetAddressOfyCoordinatesVec();
  void Draw(double xMin, double xMax, double yMin, double yMax);

 private:
  Ui::Graph *ui;

  QVector<double> xCoordinates_;
  QVector<double> yCoordinates_;
};
}  // namespace s21

#endif  // GRAPH_H
