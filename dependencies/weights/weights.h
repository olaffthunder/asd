#pragma once
#include <vcruntime.h>
#include <ratio>

namespace Weight
{
    /*
    // A Unit of weight is defined by a type T to represent the
    // weight, e.g. std::size_t or double (latter required for
    // proper conversion between units), as well as a ratio for
    // conversion between the Unit and our base unit: grams.
    // The ratio defaults to a ratio of 1/1 for grams.
    */
    template<typename T, typename R = std::ratio<1>>
    struct Unit
    {
        using Type = T;

        using Ratio = R;

        /*
        // Constructor taking the weight, of whatever Type is
        // used to represent weights for this Unit. Must be
        // constexpr to have the literal operator be constexpr too.
        */
        constexpr explicit Unit(Type weight)
            : _weight(weight)
        { }

        constexpr Unit(const Unit& other)
            : _weight(other._weight)
        { }

        Unit& operator=(const Unit& other)
        {
            if (this != &other)
            {
                _weight = other._weight;
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

            return W(_weight * conversion);
        }

        // Member access
        Type weight() const
        {
            return _weight;
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
            _weight += other.weigth;

            return *this;
        }

        Unit operator+(Unit other)
        {
            other._weight += _weight;

            return other;
        }

        Unit& operator-=(const Unit& other)
        {
            _weight -= other._weight;

            return *this;
        }

        Unit operator-(Unit other)
        {
            other._weight += _weight;

            return other;
        }

        Unit& operator*=(Type factor)
        {
            _weight *= factor;

            return *this;
        }

        Unit operator*(Type factor)
        {
            return Unit(_weight * factor);
        }

        friend Unit operator*(Type factor, const Unit& weight)
        {
            return weight * factor;
        }

        Unit& operator/=(Type factor)
        {
            _weight /= factor;

            return *this;
        }

        Unit operator/(Type factor)
        {
            return Unit(_weight / factor);
        }

        friend Unit operator/(Type factor, const Unit& weight)
        {
            return weight / factor;
        }

        bool operator==(const Unit& other)
        {
            return _weight == other._weight;
        }

        bool operator<(const Unit& other)
        {
            return _weight < other._weight;
        }

        bool operator>(const Unit& other)
        {
            return _weight > other._weight;
        }

        bool operator<=(const Unit& other)
        {
            return _weight <= other._weight;
        }

        bool operator>=(const Unit& other)
        {
            return _weight >= other._weight;
        }

        bool operator!=(const Unit& other)
        {
            return _weight != other._weight;
        }

    private:

        Type _weight;
    };

    // Alias declarations for ease of use
    using Milligrams = Unit<std::size_t, std::milli>;

    using Grams = Unit<std::size_t>;

    using Kilograms = Unit<std::size_t, std::kilo>;

    using Ounce = Unit<std::size_t, std::ratio<28>>;

    namespace Literals
    {
        // Literal operators, always one for integers and one
        // for floating-point values.

        constexpr Milligrams operator""_mg(unsigned long long weight)
        {
            return Milligrams(weight);
        }

        constexpr Unit<long double, std::milli> operator""_mg(long double weight)
        {
            return Unit<long double, std::milli>(weight);
        }

        constexpr Grams operator""_g(unsigned long long weight)
        {
            return Grams(weight);
        }

        constexpr Unit<long double> operator""_g(long double weight)
        {
            return Unit<long double>(weight);
        }


        constexpr Kilograms operator""_kg(unsigned long long weight)
        {
            return Kilograms(weight);
        }

        constexpr Unit<long double, std::kilo> operator""_kg(long double weight)
        {
            return Unit<long double, std::kilo>(weight);
        }

        constexpr Ounce operator""_oz(unsigned long long weight)
        {
            return Ounce(weight);
        }

        constexpr Unit<long double, std::ratio<28>> operator""_oz(long double weight)
        {
            return Unit<long double, std::ratio<28>>(weight);
        }
    }

    using namespace Literals;
}