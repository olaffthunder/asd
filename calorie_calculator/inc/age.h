#pragma once
#include "dependencies/strong_types/strong_types.h"

namespace calorie_calculator
{
    namespace age
    {
        //TODO: think of a better solution
        struct Age : StrongType<int, struct AgeParameters>
        {
            constexpr explicit Age(const int value) :
                StrongType<int, struct AgeParameters>(value) {}
            constexpr explicit Age(const double value) :
                StrongType<int, struct AgeParameters>(static_cast<int>(value)) {}
            constexpr explicit Age(const long double value) :
                StrongType<int, struct AgeParameters>(static_cast<int>(value)) {}
            constexpr explicit Age(const unsigned long long value) :
                StrongType<int, struct AgeParameters>(static_cast<int>(value)) {}
        };

        namespace literals
        {
            // Literal operators, always one for integers and one
            // for floating-point values.
            constexpr Age operator""_a(const unsigned long long age)
            {
                return Age(age);
            }

            //TODO is this really necessary?
            constexpr Age operator""_a(const long double age)
            {
                return Age(age);
            }
        }
    }
}