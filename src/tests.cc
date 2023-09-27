#include <gtest/gtest.h>

#include "./controller/controller.h"

class MockCalculator : public Calculator {
public:
    MOCK_METHOD(double, Calc, (), (override));
    MOCK_METHOD(void, CalculateGraphic, (double, double, double, double), (override));
    MOCK_METHOD(std::vector<double>*, GetXPoint, (), (override));
    MOCK_METHOD(std::vector<double>*, GetYPoint, (), (override));
};

TEST(ControllerTest, CalculationTest) {
    MockCalculator mockCalculator;
    s21::Controller controller(&mockCalculator);

    EXPECT_CALL(mockCalculator, SetExpression("2 + 2"));
    EXPECT_CALL(mockCalculator, SetX(0));
    EXPECT_CALL(mockCalculator, Calc()).WillOnce(testing::Return(4.0));

    double result = controller.Calculation("2 + 2", 0);
    EXPECT_EQ(result, 4.0);
}

TEST(ControllerTest, DrowPlotTest) {
    MockCalculator mockCalculator;
    s21::Controller controller(&mockCalculator);

    EXPECT_CALL(mockCalculator, CalculateGraphic(-10, 10, -10, 10));

    controller.DrowPlot(-10, 10, -10, 10);

    EXPECT_TRUE(controller.GetXPoints() != nullptr);
    EXPECT_TRUE(controller.GetYPoints() != nullptr);
}

TEST(ControllerTest, GetPointsTest) {
    MockCalculator mockCalculator;
    s21::Controller controller(&mockCalculator);

    EXPECT_TRUE(controller.GetXPoints() != nullptr);
    EXPECT_TRUE(controller.GetYPoints() != nullptr);
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}