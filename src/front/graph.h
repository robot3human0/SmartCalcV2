#ifndef GRAPH_H
#define GRAPH_H

#include <QWidget>

QT_BEGIN_NAMESPACE
namespace Ui {
class Graph;
}
QT_END_NAMESPACE

class Graph : public QWidget {
  Q_OBJECT

 public:
  //    explicit Graph(QVector<double> *xs, QVector<double> *ys, QWidget *parent
  //    = nullptr);
  explicit Graph(QWidget *parent = nullptr);
  ~Graph();
  void Draw(double xMin, double xMax, double yMin, double yMax);

 private:
  Ui::Graph *ui;
  QVector<double> *xs_;
  QVector<double> *ys_;
};

#endif  // GRAPH_H
