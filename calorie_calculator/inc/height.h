#pragma once
#include "dependencies/unit/unit.h"

namespace calorie_calculator
{
    namespace height
    {
        using Meter = unit::Unit<std::size_t>;
        using Centimeter = unit::Unit<std::size_t, std::centi>;

        namespace literals
        {
            constexpr Meter operator""_m(unsigned long long weight)
            {
                return Meter(weight);
            }

            constexpr Meter operator""_m(long double weight)
            {
                return Meter(static_cast<size_t>(weight));
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