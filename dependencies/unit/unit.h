#pragma once
#include <vcruntime.h>
#include <ratio>
#include "dependencies/strong_types/strong_types.h"

namespace unit
{
    /*
    // A Unit of weight is defined by a type T to represent the
    // weight, e.g. std::size_t or double (latter required for
    // proper conversion between units), as well as a ratio for
    // conversion between the Unit and our base unit: grams.
    // The ratio defaults to a ratio of 1/1 for grams.
    */
    template<typename T, typename R = std::ratio<1>>
    struct Unit : StrongType<T, R>
    {
        using Type = T;

        using Ratio = R;

        /*
        // Constructor taking the weight, of whatever Type is
        // used to represent weights for this Unit. Must be
        // constexpr to have the literal operator be constexpr too.
        */
        constexpr explicit Unit(Type weight)
            : StrongType<T, R>(weight)
        { }

        constexpr Unit(const Unit& other)
            : StrongType<T, R>(other.get())
        { }

        Unit& operator=(const Unit& other)
        {
            if (this != &other)
            {
                value_ = other.value_;
            }

            return *this;
        }

        /*
        // This may be the most important method. It takes care
        // of implicit conversion between different units of weight
        // to implicitly convert this unit of weight to another unit
        // represented by type U, with a ratio S, the ratio of this
        // unit is simply divided by the ratio of the other. For example
        // to convert 100 ounces (28/1 g) to milligrams (1/1000 g), the
        // factor applied to the weight (in ounces) equal to (28/1)/(1/1000)
        // = 28000, i.e. 100 ounces are 2'800'000 milligrams. (a/b)/(c/d)
        // is equivalent to (a*d)/(b*c) and takes better care of integer
        // division here (as Ratio::num and Ratio::den are integers).
        // We return an object of the unit we're casting to.
        */
        template<typename U, typename S>
        operator Unit<U, S>()
        {
            using W = Unit<U, S>;

            double conversion = Ratio::num * W::Ratio::den;

            conversion /= Ratio::den * W::Ratio::num;

            return W(static_cast<U>(this->get() * conversion));
        }

        /*
        // All appropriate operator overloads follow. Note that
        // any unit that isn't this Unit will be implicitly cast
        // to this Unit first via the implicit conversion operator
        // above. This means that the weight of the other object
        // is already in the unit of this Unit (has the proper
        // ratio) and thus we can add the weights together without
        // a problem.
        */
        Unit& operator+=(const Unit& other)
        {
            value_ += other.value_;

            return *this;
        }

        Unit operator+(Unit other)
        {
            other.value_ += value_;

            return other;
        }

        Unit& operator-=(const Unit& other)
        {
            value_ -= other.value_;

            return *this;
        }

        Unit operator-(Unit other)
        {
            other.value_ += value_;

            return other;
        }

        Unit& operator*=(Type factor)
        {
            value_ *= factor;

            return *this;
        }

        Unit& operator/=(Type factor)
        {
            value_ /= factor;

            return *this;
        }

        Unit operator/(Type factor)
        {
            return Unit(value_ / factor);
        }

        friend Unit operator/(Type factor, const Unit& weight)
        {
            return weight / factor;
        }
    };

    // Alias declarations for ease of use
}