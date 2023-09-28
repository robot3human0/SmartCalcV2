#include "graph.h"

#include <QVector>
#include <sstream>

#include "ui_graph.h"

s21::Graph::Graph(QWidget *parent) : QWidget(parent), ui(new Ui::Graph) {
  ui->setupUi(this);
}

s21::Graph::~Graph() { delete ui; }

QVector<double> *s21::Graph::GetAddressOfxCoordinatesVec() {
  return &xCoordinates_;
}

QVector<double> *s21::Graph::GetAddressOfyCoordinatesVec() {
  return &yCoordinates_;
}

void s21::Graph::Draw(double xMin, double xMax, double yMin, double yMax) {
  ui->graphicsView->xAxis->setRange(xMin, xMax);
  ui->graphicsView->yAxis->setRange(yMin, yMax);
  ui->graphicsView->clearGraphs();
  ui->graphicsView->addGraph();
  ui->graphicsView->graph(0)->setLineStyle(QCPGraph::lsNone);
  ui->graphicsView->graph(0)->setScatterStyle(
      QCPScatterStyle(QCPScatterStyle::ssCircle, 5));
  ui->graphicsView->graph(0)->addData(xCoordinates_, yCoordinates_);
  ui->graphicsView->replot();
  ui->graphicsView->setInteraction(QCP::iRangeZoom, true);
  ui->graphicsView->setInteraction(QCP::iRangeDrag, true);
  xCoordinates_.clear();
  yCoordinates_.clear();
}
