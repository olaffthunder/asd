#include "calorie_calculator/inc/profile.h"

namespace calorie_calculator
{
    namespace profile
    {
        age::Age Profile::getAge() const
        {
            return age_;
        }
        
        height::Height Profile::getHeight() const
        {
            return height_;
        }

        weight::Weight Profile::getWeight() const
        {
            return weight_;
        }
        Gender Profile::getGender() const
        {
            return gender_;
        }
    }
}