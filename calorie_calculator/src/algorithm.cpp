#include "calorie_calculator/inc/algorithm.h"
#include "calorie_calculator/inc/profile.h"
namespace calorie_calculator
{
    namespace basal_metabolic_estimation
    {
        using namespace age::literals;
        calories::Calories harris_benedict_equation_original(const profile::Profile &profile)
        {
            return harris_benedict_equation_original(profile.getWeight(), profile.getHeight(), profile.getAge());
        }

        calories::Calories harris_benedict_equation_revised(const profile::Profile &profile)
        {
            return harris_benedict_equation_revised(profile.getWeight(), profile.getHeight(), profile.getAge());
        }

        calories::Calories world_health_organization_equation(const profile::Profile &profile)
        {
            return world_health_organization_equation(profile.getWeight(), profile.getAge());
        }

        calories::Calories mifflin_st_jeor_equation(const profile::Profile &profile)
        {
            return mifflin_st_jeor_equation(profile.getWeight(), profile.getHeight(), profile.getAge());
        }

        calories::Calories katch_mc_ardle_formular(const profile::Profile &profile)
        {
            return katch_mc_ardle_formular(profile.getWeight());
        }

        //TODO add women too!
        //this is the original formular for men only
        calories::Calories harris_benedict_equation_original(const weight::Kilograms &weight, const height::Centimeter &height, const age::Age &age)
        {
            return calories::Calories(66.5 + (13.75 * weight) + (5.003 * height) - (6.755 * age));
        }

        calories::Calories harris_benedict_equation_revised(const weight::Kilograms &weight, const height::Centimeter &height, const age::Age &age)
        {
            return calories::Calories(88.362 + (13.397 * weight) + (4.799 * height) - (5.677 * age));
        }

        calories::Calories world_health_organization_equation(const weight::Kilograms &weight, const age::Age &age)
        {
            if (age >= 3_a && age <= 9_a)
                return calories::Calories{ 22.7 * weight + 495 };
            if (age >= 10_a && age <= 17_a)
                return calories::Calories{ 17.5 * weight + 651 };
            if (age >= 18_a && age <= 29_a)
                return calories::Calories{ 15.3 * weight + 679 };
            if (age >= 30_a && age <= 60_a)
                return calories::Calories{ 11.6 * weight + 879 };
            return calories::Calories{ 13.5 * weight + 487 };
        }

        calories::Calories mifflin_st_jeor_equation(const weight::Kilograms &weight, const height::Centimeter &height, const age::Age &age)
        {
            return calories::Calories{ 10 * weight + 6.25 * height - (5 * age) + 5 };
        }

        calories::Calories katch_mc_ardle_formular(const weight::Kilograms &weight)
        {
            return calories::Calories(370 + (21.6 * weight));
        }
    }

    namespace body_fat_estimation
    {
        using namespace age::literals;
        percentage::Percentage get_adult_body_fat_percentage_by_bmi(const profile::Profile & profile)
        {
            return get_adult_body_fat_percentage_by_bmi(profile.getWeight(), profile.getHeight(), profile.getAge());
        }
        percentage::Percentage get_adult_body_fat_percentage_by_bmi(const weight::Kilograms &weight, const height::Meter &height, const age::Age &age)
        {
            //TODO
            //int sex_factor = 0;
            //if (sex = male)
            //    sex_factor = 1;
            return percentage::Percentage(( (1.20 * weight) / *(height * height)) + (0.23 * age) - (10.8 * 1.) - 5.4);
        }
    }
}