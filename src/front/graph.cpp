#include "graph.h"

#include <QVector>

#include "ui_graph.h"

// Graph::Graph(QVector<double> *xs, QVector<double> *ys, QWidget *parent)
//     : QWidget(parent)
//     , ui(new Ui::Graph)
//     , xs_(xs = new QVector<double>)
//     , ys_(ys = new QVector<double>)
//{
//     ui->setupUi(this);
// }

Graph::Graph(QWidget *parent) : QWidget(parent), ui(new Ui::Graph) {
  xs_ = new QVector<double>;
  ys_ = new QVector<double>;
  ui->setupUi(this);
}

Graph::~Graph() {
  delete xs_;
  delete ys_;
  delete ui;
}

void Graph::Draw(double xMin, double xMax, double yMin, double yMax) {
  ui->graphicsView->xAxis->setRange(xMin, xMax);
  ui->graphicsView->yAxis->setRange(yMin, yMax);
  ui->graphicsView->clearGraphs();
  ui->graphicsView->addGraph();
  ui->graphicsView->graph(0)->setLineStyle(QCPGraph::lsNone);
  ui->graphicsView->graph(0)->setScatterStyle(
      QCPScatterStyle(QCPScatterStyle::ssCircle, 5));
  ui->graphicsView->graph(0)->addData(*xs_, *ys_);
  ui->graphicsView->replot();
  ui->graphicsView->setInteraction(QCP::iRangeZoom, true);
  ui->graphicsView->setInteraction(QCP::iRangeDrag, true);
  xs_->clear();
  ys_->clear();
}
