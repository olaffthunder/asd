#define CATCH_CONFIG_MAIN
#include "dependencies/catch/catch.hpp"
#include "dependencies/strong_types/strong_types.h"

#include "calorie_calculator/inc/algorithm.h"

TEST_CASE("BMR calculation")
{
    namespace cc = calorie_calculator;
    SECTION("harris_benedict_equation")
    {
        SECTION("all passed values 0")
        {
            cc::Kilogramm weight{ 0. };
            auto calories = cc::harris_benedict_equation(weight, 0, 0);
            REQUIRE(calories.get() == cc::Calories{ 66 }.get());
        }
        SECTION("weight == 1 - others == 0")
        {
            cc::Kilogramm weight{ 1. };
            auto calories = cc::harris_benedict_equation(weight, 0, 0);
            INFO("Keep in mind: within the formular it's 66.5 + 13.75 which results in 80.25." 
                "Therefore it's 80 and not 79!");
            REQUIRE(calories.get() == cc::Calories{ 66.5 + 13.75 }.get());
        }
        SECTION("height == 1 - others == 0")
        {
            cc::Kilogramm weight{ 0. };
            auto calories = cc::harris_benedict_equation(weight, 1, 0);
            REQUIRE(calories.get() == cc::Calories{ 66.5 + 5.003 }.get());
        }
        SECTION("age == 1 - others == 0")
        {
            cc::Kilogramm weight{ 0. };
            auto calories = cc::harris_benedict_equation(weight, 0, 1);
            REQUIRE(calories.get() == cc::Calories{ 66.5 - 6.755 }.get());
        }
        SECTION("age == 1 - weigth == 1 - others == 0")
        {
            cc::Kilogramm weight{ 1. };
            auto calories = cc::harris_benedict_equation(weight, 0, 1);
            REQUIRE(calories.get() == cc::Calories{ 66.5 + 13.75 - 6.755 }.get());
        }
        SECTION("age == 1 - weigth == 1 - others 0")
        {
            cc::Kilogramm weight{ 1. };
            auto calories = cc::harris_benedict_equation(weight, 1, 0);
            REQUIRE(calories.get() == cc::Calories{ 66.5 + 13.75 + 5.003 }.get());
        }\
        SECTION("all passed values == 1")
        {
            cc::Kilogramm weight{ 1. };
            auto calories = cc::harris_benedict_equation(weight, 1, 1);
            REQUIRE(calories.get() == cc::Calories{ 66.5 + 13.75 + 5.003 - 6.755 }.get());
        }
    }

    SECTION("world_health_organization_equation")
    {
        SECTION("age < 3 - weight == 1")
        {
            cc::Kilogramm weight{ 0. };
            auto calories = cc::world_health_organization_equation(weight, 0);
            REQUIRE(calories.get() == cc::Calories{ 487 }.get());
        }
        SECTION("age < 3 - weight == 1")
        {
            cc::Kilogramm weight{ 1. };
            auto calories = cc::world_health_organization_equation(weight, 0);
            REQUIRE(calories.get() == cc::Calories{ 13.5 + 487 }.get());
        }
        SECTION("age >= 3 && age <= 9 - weight == 0" )
        {
            cc::Kilogramm weight{ 0. };
            auto calories_3 = cc::world_health_organization_equation(weight, 3);
            REQUIRE(calories_3.get() == cc::Calories{ 495 }.get());

            auto calories_9 = cc::world_health_organization_equation(weight, 9);
            REQUIRE(calories_3.get() == calories_9.get());
        }
        SECTION("age >= 3 && age <= 9 - weight == 1")
        {
            cc::Kilogramm weight{ 1. };
            auto calories_3 = cc::world_health_organization_equation(weight, 3);
            REQUIRE(calories_3.get() == cc::Calories{ 22.7 + 495 }.get());

            auto calories_9 = cc::world_health_organization_equation(weight, 9);
            REQUIRE(calories_3.get() == calories_9.get());
        }
        SECTION("age >= 10 && age <= 17 - weight == 0")
        {
            cc::Kilogramm weight{ 0. };
            auto calories_10 = cc::world_health_organization_equation(weight, 10);
            REQUIRE(calories_10.get() == cc::Calories{ 651 }.get());

            auto calories_17 = cc::world_health_organization_equation(weight, 17);
            REQUIRE(calories_10.get() == calories_17.get());
        }
        SECTION("age >= 10 && age <= 17 - weight == 1")
        {
            cc::Kilogramm weight{ 1. };
            auto calories_10 = cc::world_health_organization_equation(weight, 10);
            REQUIRE(calories_10.get() == cc::Calories{ 17.5 + 651 }.get());

            auto calories_17 = cc::world_health_organization_equation(weight, 17);
            REQUIRE(calories_10.get() == calories_17.get());
        }
        SECTION("age >= 18 && age <= 29 - weight == 0")
        {
            cc::Kilogramm weight{ 0. };
            auto calories_18 = cc::world_health_organization_equation(weight, 18);
            REQUIRE(calories_18.get() == cc::Calories{ 679 }.get());

            auto calories_29 = cc::world_health_organization_equation(weight, 29);
            REQUIRE(calories_18.get() == calories_29.get());
        }
        SECTION("age >= 18 && age <= 29 - weight == 1")
        {
            cc::Kilogramm weight{ 1. };
            auto calories_18 = cc::world_health_organization_equation(weight, 18);
            REQUIRE(calories_18.get() == cc::Calories{ 15.3 + 679 }.get());

            auto calories_29 = cc::world_health_organization_equation(weight, 29);
            REQUIRE(calories_18.get() == calories_29.get());
        }
        SECTION("age >= 30 && age <= 60 - weight == 0")
        {
            cc::Kilogramm weight{ 0. };
            auto calories_30 = cc::world_health_organization_equation(weight, 30);
            REQUIRE(calories_30.get() == cc::Calories{ 879 }.get());

            auto calories_60 = cc::world_health_organization_equation(weight, 60);
            REQUIRE(calories_30.get() == calories_60.get());
        }
        SECTION("age >= 30 && age <= 60 - weight == 1")
        {
            cc::Kilogramm weight{ 1. };
            auto calories_30 = cc::world_health_organization_equation(weight, 30);
            REQUIRE(calories_30.get() == cc::Calories{ 11.6 + 879 }.get());

            auto calories_60 = cc::world_health_organization_equation(weight, 60);
            REQUIRE(calories_30.get() == calories_60.get());
        }
        SECTION("age > 60 - weight == 0")
        {
            cc::Kilogramm weight{ 0. };
            auto calories = cc::world_health_organization_equation(weight, 61);
            REQUIRE(calories.get() == cc::Calories{ 487 }.get());
        }
        SECTION("age > 60 - weight == 1")
        {
            cc::Kilogramm weight{ 1. };
            auto calories = cc::world_health_organization_equation(weight, 61);
            REQUIRE(calories.get() == cc::Calories{ 13.5 + 487 }.get());
        }
    }

    SECTION("world_health_organization_equation")
    {
        SECTION("all passed values == 0")
        {
            cc::Kilogramm weight{ 0. };
            auto calories = cc::mifflin_st_jeor_equation(weight, 0, 0);
            REQUIRE(calories.get() == cc::Calories{ 5 }.get());
        }
        SECTION("weight == 1 - all others == 0")
        {
            cc::Kilogramm weight{ 1. };
            auto calories = cc::mifflin_st_jeor_equation(weight, 0, 0);
            REQUIRE(calories.get() == cc::Calories{ 10 + 5 }.get());
        }
        SECTION("height == 1 - all others == 0")
        {
            cc::Kilogramm weight{ 0. };
            auto calories = cc::mifflin_st_jeor_equation(weight, 1, 0);
            REQUIRE(calories.get() == cc::Calories{ 6.25 + 5 }.get());
        }
        SECTION("age == 1 - all others == 0")
        {
            cc::Kilogramm weight{ 0. };
            auto calories = cc::mifflin_st_jeor_equation(weight, 0, 1);
            REQUIRE(calories.get() == cc::Calories{ 5 - 5 }.get());
        }
        SECTION("weight == 1 - height == 1 - age == 0")
        {
            cc::Kilogramm weight{ 1. };
            auto calories = cc::mifflin_st_jeor_equation(weight, 1, 0);
            REQUIRE(calories.get() == cc::Calories{ 10 + 6.25 + 5 }.get());
        }
        SECTION("weight == 1 - height == 0 - age == 1")
        {
            cc::Kilogramm weight{ 1. };
            auto calories = cc::mifflin_st_jeor_equation(weight, 0, 1);
            REQUIRE(calories.get() == cc::Calories{ 10 - 5 + 5 }.get());
        }
        SECTION("weight == 0 - height == 1 - age == 1")
        {
            cc::Kilogramm weight{ 0. };
            auto calories = cc::mifflin_st_jeor_equation(weight, 1, 1);
            REQUIRE(calories.get() == cc::Calories{ 6.25 - 5 + 5 }.get());
        }
        SECTION("weight == 1 - height == 1 - age == 1")
        {
            cc::Kilogramm weight{ 1. };
            auto calories = cc::mifflin_st_jeor_equation(weight, 1, 1);
            REQUIRE(calories.get() == cc::Calories{ 10 + 6.25 - 5 + 5 }.get());
        }
    }

    SECTION("katch_mc_ardle_formular")
    {
        SECTION("weight == 0")
        {
            cc::Kilogramm weight{ 0. };
            auto calories = cc::katch_mc_ardle_formular(weight);
            REQUIRE(calories.get() == cc::Calories{ 370 }.get());
        }
        SECTION("weight == 1")
        {
            cc::Kilogramm weight{ 1. };
            auto calories = cc::katch_mc_ardle_formular(weight);
            REQUIRE(calories.get() == cc::Calories{ 370 + 21.6 }.get());
        }
    }
}