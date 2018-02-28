#pragma once
#include "dependencies/strong_types/strong_types.h"

namespace calorie_calculator
{
    namespace calories
    {
        //TODO: think of a better solution
        struct Calories : StrongType<int, struct CalorieParameters>
        {
            constexpr explicit Calories(const int value) :
                StrongType<int, struct CalorieParameters>(value) {}
            constexpr explicit Calories(const double value) :
                StrongType<int, struct CalorieParameters>(static_cast<int>(value)) {}
            constexpr explicit Calories(const long double value) :
                StrongType<int, struct CalorieParameters>(static_cast<int>(value)) {}
            constexpr explicit Calories(const unsigned long long value) :
                StrongType<int, struct CalorieParameters>(static_cast<int>(value)) {}
        };

        namespace literals
        {
            // Literal operators, always one for integers and one
            // for floating-point values.
            constexpr StrongType<int, struct CalorieParameters> operator""_kcal(const unsigned long long calories)
            {
                return Calories(calories);
            }

            constexpr Calories operator""_kcal(const long double calories)
            {
                return Calories(calories);
            }
        }
    }
}