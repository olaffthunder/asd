#pragma once
#include "age.h"
#include "height.h"
#include "weights.h"

namespace calorie_calculator
{
    namespace profile
    {
        class Profile
        {
        public:
            constexpr Profile(const age::Age &age, const height::Height &height, const weight::Weight &weight)
                : age_(age), height_(height), weight_(weight) {}
            age::Age getAge() const;
            height::Height getHeight() const;
            weight::Weight getWeight() const;

        private:
            age::Age age_;
            height::Height height_;
            weight::Weight weight_;
        };
    }
}