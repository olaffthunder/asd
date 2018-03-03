#pragma once
#include "age.h"
#include "height.h"
#include "weights.h"
#include "basic_utility.h"

namespace calorie_calculator
{
    namespace profile
    {
        class Profile
        {
        public:
            constexpr Profile(const age::Age &age, const height::Height &height, const weight::Weight &weight, const Gender gender)
                : age_(age), height_(height), weight_(weight), gender_(gender) {}
            age::Age getAge() const;
            height::Height getHeight() const;
            weight::Weight getWeight() const;
            Gender getGender() const;

        private:
            age::Age age_;
            height::Height height_;
            weight::Weight weight_;
            Gender gender_;
        };
    }
}