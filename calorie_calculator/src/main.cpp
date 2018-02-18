#include <iostream>

#include "calorie_calculator/inc/algorithm.h"

int main()
{
    calorie_calculator::Kilogramm weigth{72.8};
    std::cout << calorie_calculator::basal_metabolic_estimation::harris_benedict_equation_original(weigth, 184, 25).get();
    return 0;
}