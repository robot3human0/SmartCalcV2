#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "../model/model.h"

namespace s21 {
    class Controller {
    public:
        Controller(Calculator *calc) : calcuta_(calc) {};
        ~Controller() = default;
        
        void Calculation(const std::string expression, const double x);
        void CalculateGraphic(double xMin, double xMax, int amoutOfDots);
        void GetAnswer();
        void GetX();
        void GetY();
        bool IsEmptyQueueX();

    private:
        Calculator *calcuta_;
        std::queue<double> xDotCoordinates_;
        std::queue<double> yDotCoordinates_;
    };
} // namespace s21
#endif  // CONTROLLER_H