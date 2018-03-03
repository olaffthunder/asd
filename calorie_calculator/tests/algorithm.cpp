#define CATCH_CONFIG_MAIN
#include "dependencies/catch/catch.hpp"
#include "dependencies/strong_types/strong_types.h"

#include "calorie_calculator/inc/algorithm.h"

TEST_CASE("BMR calculation")
{
    namespace cc = calorie_calculator;
    namespace bmr = calorie_calculator::basal_metabolic_estimation;
    using namespace calorie_calculator::age::literals;
    using namespace calorie_calculator::height::literals;
    using namespace calorie_calculator::weight::literals;
    SECTION("harris_benedict_equation_original")
    {
        SECTION("all passed values 0")
        {
            auto calories = bmr::harris_benedict_equation_original(0._kg, 0_cm, 0_a);
            REQUIRE(calories == cc::calories::Calories{ 66 });
        }
        SECTION("weight == 1 - others == 0")
        {
            auto calories = bmr::harris_benedict_equation_original(1._kg, 0_cm, 0_a);
            INFO("Keep in mind: within the formular it's 66.5 + 13.75 which results in 80.25." 
                "Therefore it's 80 and not 79!");
            REQUIRE(calories == cc::calories::Calories{ 66.5 + 13.75 });
        }
        SECTION("height == 1 - others == 0")
        {
            auto calories = bmr::harris_benedict_equation_original(0._kg, 1_cm, 0_a);
            REQUIRE(calories == cc::calories::Calories{ 66.5 + 5.003 });
        }
        SECTION("age == 1 - others == 0")
        {
            auto calories = bmr::harris_benedict_equation_original(0._kg, 0_cm, 1_a);
            REQUIRE(calories == cc::calories::Calories{ 66.5 - 6.755 });
        }
        SECTION("age == 1 - weigth == 1 - others == 0")
        {
            auto calories = bmr::harris_benedict_equation_original(1._kg, 0_cm, 1_a);
            REQUIRE(calories == cc::calories::Calories{ 66.5 + 13.75 - 6.755 });
        }
        SECTION("age == 0 - weigth == 1 - height == 1")
        {
            auto calories = bmr::harris_benedict_equation_original(1._kg, 1_cm, 0_a);
            REQUIRE(calories == cc::calories::Calories{ 66.5 + 13.75 + 5.003 });
        }
        SECTION("all passed values == 1")
        {
            auto calories = bmr::harris_benedict_equation_original(1._kg, 1_cm, 1_a);
            REQUIRE(calories == cc::calories::Calories{ 66.5 + 13.75 + 5.003 - 6.755 });
        }
    }

    SECTION("harris_benedict_equation_revised")
    {
        SECTION("all passed values 0")
        {
            auto calories = bmr::harris_benedict_equation_revised(0._kg, 0_cm, 0_a);
            REQUIRE(calories == cc::calories::Calories{ 88.362 });
        }
        SECTION("weight == 1 - others == 0")
        {
            auto calories = bmr::harris_benedict_equation_revised(1._kg, 0_cm, 0_a);
            INFO("Keep in mind: within the formular it's 66.5 + 13.75 which results in 80.25."
                "Therefore it's 80 and not 79!");
            REQUIRE(calories == cc::calories::Calories{ 88.362 + 13.397 });
        }
        SECTION("height == 1 - others == 0")
        {
            auto calories = bmr::harris_benedict_equation_revised(0._kg, 1_cm, 0_a);
            REQUIRE(calories == cc::calories::Calories{ 88.362 + 4.799 });
        }
        SECTION("age == 1 - others == 0")
        {
            auto calories = bmr::harris_benedict_equation_revised(0._kg, 0_cm, 1_a);
            REQUIRE(calories == cc::calories::Calories{ 88.362 - 5.677 });
        }
        SECTION("age == 1 - weigth == 1 - height == 0")
        {
            auto calories = bmr::harris_benedict_equation_revised(1._kg, 0_cm, 1_a);
            REQUIRE(calories == cc::calories::Calories{ 88.362 + 13.397 - 5.677 });
        }
        SECTION("age == 0 - weigth == 1 - height == 1")
        {
            auto calories = bmr::harris_benedict_equation_revised(1._kg, 1_cm, 0_a);
            REQUIRE(calories == cc::calories::Calories{ 88.362 + 13.397 + 4.799 });
        }
            SECTION("all passed values == 1")
        {
            auto calories = bmr::harris_benedict_equation_revised(1._kg, 1_cm, 1_a);
            REQUIRE(calories == cc::calories::Calories{ 88.362 + 13.397 + 4.799 - 5.677 });
        }
    }


    SECTION("world_health_organization_equation")
    {
        SECTION("age < 3 - weight == 0")
        {
            auto calories = bmr::world_health_organization_equation(0._kg, 0_a);
            REQUIRE(calories == cc::calories::Calories{ 487 });
        }
        SECTION("age < 3 - weight == 1")
        {
            auto calories = bmr::world_health_organization_equation(1._kg, 0_a);
            REQUIRE(calories == cc::calories::Calories{ 13.5 + 487 });
        }
        SECTION("age >= 3 && age <= 9 - weight == 0" )
        {
            auto calories_3 = bmr::world_health_organization_equation(0._kg, 3_a);
            REQUIRE(calories_3 == cc::calories::Calories{ 495 });

            auto calories_9 = bmr::world_health_organization_equation(0._kg, 9_a);
            REQUIRE(calories_3 == calories_9);
        }
        SECTION("age >= 3 && age <= 9 - weight == 1")
        {
            auto calories_3 = bmr::world_health_organization_equation(1._kg, 3_a);
            REQUIRE(calories_3 == cc::calories::Calories{ 22.7 + 495 });

            auto calories_9 = bmr::world_health_organization_equation(1._kg, 9_a);
            REQUIRE(calories_3 == calories_9);
        }
        SECTION("age >= 10 && age <= 17 - weight == 0")
        {
            auto calories_10 = bmr::world_health_organization_equation(0._kg, 10_a);
            REQUIRE(calories_10 == cc::calories::Calories{ 651 });

            auto calories_17 = bmr::world_health_organization_equation(0._kg, 17_a);
            REQUIRE(calories_10 == calories_17);
        }
        SECTION("age >= 10 && age <= 17 - weight == 1")
        {
            auto calories_10 = bmr::world_health_organization_equation(1._kg, 10_a);
            REQUIRE(calories_10 == cc::calories::Calories{ 17.5 + 651 });

            auto calories_17 = bmr::world_health_organization_equation(1._kg, 17_a);
            REQUIRE(calories_10 == calories_17);
        }
        SECTION("age >= 18 && age <= 29 - weight == 0")
        {
            auto calories_18 = bmr::world_health_organization_equation(0._kg, 18_a);
            REQUIRE(calories_18 == cc::calories::Calories{ 679 });

            auto calories_29 = bmr::world_health_organization_equation(0._kg, 29_a);
            REQUIRE(calories_18 == calories_29);
        }
        SECTION("age >= 18 && age <= 29 - weight == 1")
        {
            auto calories_18 = bmr::world_health_organization_equation(1._kg, 18_a);
            REQUIRE(calories_18 == cc::calories::Calories{ 15.3 + 679 });

            auto calories_29 = bmr::world_health_organization_equation(1._kg, 29_a);
            REQUIRE(calories_18 == calories_29);
        }
        SECTION("age >= 30 && age <= 60 - weight == 0")
        {
            auto calories_30 = bmr::world_health_organization_equation(0._kg, 30_a);
            REQUIRE(calories_30 == cc::calories::Calories{ 879 });

            auto calories_60 = bmr::world_health_organization_equation(0._kg, 60_a);
            REQUIRE(calories_30 == calories_60);
        }
        SECTION("age >= 30 && age <= 60 - weight == 1")
        {
            auto calories_30 = bmr::world_health_organization_equation(1._kg, 30_a);
            REQUIRE(calories_30 == cc::calories::Calories{ 11.6 + 879 });

            auto calories_60 = bmr::world_health_organization_equation(1._kg, 60_a);
            REQUIRE(calories_30 == calories_60);
        }
        SECTION("age > 60 - weight == 0")
        {
            auto calories = bmr::world_health_organization_equation(0._kg, 61_a);
            REQUIRE(calories == cc::calories::Calories{ 487 });
        }
        SECTION("age > 60 - weight == 1")
        {
            auto calories = bmr::world_health_organization_equation(1._kg, 61_a);
            REQUIRE(calories == cc::calories::Calories{ 13.5 + 487 });
        }
    }

    SECTION("world_health_organization_equation")
    {
        SECTION("all passed values == 0")
        {
            auto calories = bmr::mifflin_st_jeor_equation(0._kg, 0_cm, 0_a);
            REQUIRE(calories == cc::calories::Calories{ 5 });
        }
        SECTION("weight == 1 - all others == 0")
        {
            auto calories = bmr::mifflin_st_jeor_equation(1._kg, 0_cm, 0_a);
            REQUIRE(calories == cc::calories::Calories{ 10 + 5 });
        }
        SECTION("height == 1 - all others == 0")
        {
            auto calories = bmr::mifflin_st_jeor_equation(0._kg, 1_cm, 0_a);
            REQUIRE(calories == cc::calories::Calories{ 6.25 + 5 });
        }
        SECTION("age == 1 - all others == 0")
        {
            auto calories = bmr::mifflin_st_jeor_equation(0._kg, 0_cm, 1_a);
            REQUIRE(calories == cc::calories::Calories{ 5 - 5 });
        }
        SECTION("weight == 1 - height == 1 - age == 0")
        {
            auto calories = bmr::mifflin_st_jeor_equation(1._kg, 1_cm, 0_a);
            REQUIRE(calories == cc::calories::Calories{ 10 + 6.25 + 5 });
        }
        SECTION("weight == 1 - height == 0 - age == 1")
        {
            auto calories = bmr::mifflin_st_jeor_equation(1._kg, 0_cm, 1_a);
            REQUIRE(calories == cc::calories::Calories{ 10 - 5 + 5 });
        }
        SECTION("weight == 0 - height == 1 - age == 1")
        {
            auto calories = bmr::mifflin_st_jeor_equation(0._kg, 1_cm, 1_a);
            REQUIRE(calories == cc::calories::Calories{ 6.25 - 5 + 5 });
        }
        SECTION("weight == 1 - height == 1 - age == 1")
        {
            auto calories = bmr::mifflin_st_jeor_equation(1._kg, 1_cm, 1_a);
            REQUIRE(calories == cc::calories::Calories{ 10 + 6.25 - 5 + 5 });
        }
    }

    SECTION("katch_mc_ardle_formular")
    {
        SECTION("weight == 0")
        {
            auto calories = bmr::katch_mc_ardle_formular(0._kg);
            REQUIRE(calories == cc::calories::Calories{ 370 });
        }
        SECTION("weight == 1")
        {
            auto calories = bmr::katch_mc_ardle_formular(1._kg);
            REQUIRE(calories == cc::calories::Calories{ 370 + 21.6 });
        }
    }

    SECTION("get_adult_body_fat_percentage_by_bmi")
    {
        namespace bfe = calorie_calculator::body_fat_estimation;
        SECTION("all passed values == 0")
        {
            auto bfp = bfe::get_adult_body_fat_percentage_by_bmi(0._kg, 0_m, 0_a);
            REQUIRE(isnan(*bfp));
        }
        SECTION("weight == 1 - others == 0")
        {
            auto bfp = bfe::get_adult_body_fat_percentage_by_bmi(1._kg, 0_m, 0_a);
            REQUIRE(isinf(*bfp));
        }
        SECTION("weight == 1 - height == 1 - age == 0")
        {
            auto bfp = bfe::get_adult_body_fat_percentage_by_bmi(1._kg, 1_m, 0_a);
            REQUIRE(bfp == cc::percentage::Percentage(1.20 * 1._kg - (10.8 * 1.) - 5.4));
        }
        SECTION("weight == 1 - height == 0 - age == 1")
        {
            auto bfp = bfe::get_adult_body_fat_percentage_by_bmi(1._kg, 0_m, 1_a);
            REQUIRE(isinf(*bfp));
        }
        SECTION("weight == 1 - height == 1 - age == 1")
        {
            auto bfp = bfe::get_adult_body_fat_percentage_by_bmi(1._kg, 1_m, 1_a);
            REQUIRE(bfp == cc::percentage::Percentage(1.20 * 1._kg + (0.23 * 1) - (10.8 * 1.) - 5.4));
        }
    }
}