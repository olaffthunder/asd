#include "calorie_calculator/inc/algorithm.h"

namespace calorie_calculator
{
    Calories harris_benedict_equation(const Kilogramm &weight, int height, int age)
    {
        return Calories(66.5 + (13.75 * weight.weight()) + (5.003 * height) - (6.755 * age));
    }

    Calories world_health_organization_equation(const Kilogramm &weight, int age)
    {
        if (age >= 3 && age <= 9)
            return Calories{ 22.7 * weight.weight() + 495 };
        if (age >= 10 && age <= 17)
            return Calories{ 17.5 * weight.weight() + 651 };
        if (age >= 18 && age <= 29)
            return Calories{ 15.3 * weight.weight() + 679 };
        if (age >= 30 && age <= 60)
            return Calories{ 11.6 * weight.weight() + 879 };
        return Calories{ 13.5 * weight.weight() + 487 };
    }
}