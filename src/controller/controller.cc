#include "controller.h"

double s21::Controller::Calculation(std::string expression, double x) {
  calcuta_->SetExpression(expression);
  calcuta_->SetX(x);
  return calcuta_->Calc();
}

void s21::Controller::DrowPlot(double xMin, double xMax, double yMin,
                               double yMax) {
  calcuta_->CalculateGraphic(xMin, xMax, yMin, yMax);
}

std::vector<double> *s21::Controller::GetXPoints() { return calcuta_->GetXPoint(); }

std::vector<double> *s21::Controller::GetYPoints() { return calcuta_->GetYPoint(); }
