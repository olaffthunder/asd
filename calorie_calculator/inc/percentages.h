#pragma once
#include "dependencies/strong_types/strong_types.h"

namespace calorie_calculator
{
    namespace percentage
    {
        struct Percentage : StrongType<double, struct PercentageParameters>
        {
            constexpr explicit Percentage(const int value) :
                StrongType<double, struct PercentageParameters>(value) {}
            constexpr explicit Percentage(const double value) :
                StrongType<double, struct PercentageParameters>(value) {}
            constexpr explicit Percentage(const long double value) :
                StrongType<double, struct PercentageParameters>(static_cast<double>(value)) {}
            constexpr explicit Percentage(const unsigned long long value) :
                StrongType<double, struct PercentageParameters>(static_cast<double>(value)) {}
        };

        namespace literals
        {
            // Literal operators, always one for integers and one
            // for floating-point values.
            constexpr StrongType<double, struct PercentageParameters> operator""_per(const unsigned long long percentage)
            {
                return Percentage(percentage);
            }

            constexpr Percentage operator""_per(const long double percentage)
            {
                return Percentage(percentage);
            }
        }
    }
}