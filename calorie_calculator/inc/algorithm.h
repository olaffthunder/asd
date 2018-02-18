#pragma once
#include "dependencies/weights/weights.h"
#include "calorie_calculator/inc/calories.h"

namespace calorie_calculator
{
    using Kilogramm = Weight::Unit<long double, std::kilo>;

    //TODO use dimensions for height
    Calories harris_benedict_equation(const Kilogramm &weight, int height, int age);
    Calories world_health_organization_equation(const Kilogramm &weight, int age);
}