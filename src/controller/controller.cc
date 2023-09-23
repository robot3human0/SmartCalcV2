#include "controller.h"

using namespace s21;

void Controller::Calculation(const std::string expression, const double x) {
    try {
        calcuta_->Calc(expression, x);
    } catch(...) {
        throw "Error: Controller problem!";
    }
}



void GetAnswer() {
    // ...
}

void GetX() {
    // ...
}

void GetY() {
    // ...
}

bool IsEmptyQueueX() {
    // ...
}
