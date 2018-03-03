#pragma once
#include "dependencies/unit/unit.h"

namespace calorie_calculator
{
    namespace height
    {
        using Meter = unit::Unit<double>;
        using Centimeter = unit::Unit<std::size_t, std::centi>;
        using Height = Meter;

        namespace literals
        {
            constexpr Meter operator""_m(unsigned long long weight)
            {
                return Meter(static_cast<double>(weight));
            }

            constexpr Meter operator""_m(long double weight)
            {
                return Meter(weight);
            }

            constexpr Centimeter operator""_cm(unsigned long long weight)
            {
                return Centimeter(weight);
            }

            constexpr Centimeter operator""_cm(long double weight)
            {
                return Centimeter(static_cast<size_t>(weight));
            }

        }
    }
}