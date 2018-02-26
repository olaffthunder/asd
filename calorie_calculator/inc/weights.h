#pragma once
#include <vcruntime.h>
#include <ratio>
#include "dependencies/strong_types/strong_types.h"

namespace calorie_calculator
{

    namespace weight
    {
        /*
        // A Unit of weight is defined by a type T to represent the
        // weight, e.g. std::size_t or double (latter required for
        // proper conversion between units), as well as a ratio for
        // conversion between the Unit and our base unit: grams.
        // The ratio defaults to a ratio of 1/1 for grams.
        */
        
        //TODO weights in size_t?! use a primitive floating point type instead!

        // Alias declarations for ease of use
        using Milligrams = unit::Unit<std::size_t, std::milli>;

        using Grams = unit::Unit<std::size_t>;

        using Kilograms = unit::Unit<std::size_t, std::kilo>;

        using Ounce = unit::Unit<std::size_t, std::ratio<28>>;

        namespace Literals
        {
            // Literal operators, always one for integers and one
            // for floating-point values.

            constexpr Milligrams operator""_mg(unsigned long long weight)
            {
                return Milligrams(static_cast<size_t>(weight));
            }

            constexpr Milligrams operator""_mg(long double weight)
            {
                return Milligrams(static_cast<size_t>(weight));
            }

            constexpr Grams operator""_g(unsigned long long weight)
            {
                return Grams(static_cast<size_t>(weight));
            }

            constexpr Grams operator""_g(long double weight)
            {
                return Grams(static_cast<size_t>(weight));
            }


            constexpr Kilograms operator""_kg(unsigned long long weight)
            {
                return Kilograms(static_cast<size_t>(weight));
            }

            constexpr Kilograms operator""_kg(long double weight)
            {
                return Kilograms(static_cast<size_t>(weight));
            }

            constexpr Ounce operator""_oz(unsigned long long weight)
            {
                return Ounce(static_cast<size_t>(weight));
            }

            constexpr Ounce operator""_oz(long double weight)
            {
                return Ounce(static_cast<size_t>(weight));
            }
        }

        using namespace Literals;
    }
}