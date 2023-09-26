#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "../model/model.h"

namespace s21 {
    class Controller {
    public:
        Controller(Calculator *calc) : calcuta_(calc) {};
        ~Controller() = default;
        
        double Calculation(std::string expression, const double x);

    private:
        Calculator *calcuta_;
    };
} // namespace s21
#endif  // CONTROLLER_H
