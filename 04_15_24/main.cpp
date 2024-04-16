#include <iostream>
#include <random>
#include <vector>
#include "clock.h"
#include "drink.h"

template <class t>
t magicTemplate(t val1, t val2);
drink createDrink();

// in drink.h and drink.cpp add static maps to map the enum values to their prices
// change the getPrice function to use the maps instead of the switch statements.

int main()
{
    std::default_random_engine generator;
    std::uniform_int_distribution<int> distribution(1, 100);
    int x = distribution(generator);
    int y = distribution(generator);
    int z = magicTemplate<int>(x, y);

    std::uniform_real_distribution<double> distributionf(1, 50);
    double xf = distributionf(generator);
    double yf = distributionf(generator);
    double zf = magicTemplate<double>(xf, yf);

    std::cout << "z = " << z << std::endl;
    std::cout << "zf = " << zf << std::endl;
    clockType a(distribution(generator), distribution(generator), distribution(generator), TWELVE, PM);
    clockType b(distribution(generator), distribution(generator), distribution(generator), TWENTYFOUR);
    clockType c = magicTemplate<clockType>(a, b);
    std::cout << "c = " << c << std::endl;

    std::vector<clockType> clocks;
    clocks.push_back(a);
    clocks.push_back(clockType(1, 1, 1));
    for (int i = 0; i < clocks.size(); i++)
    {
        std::cout << clocks[i] << std::endl;
    }
    for (std::vector<clockType>::iterator it = clocks.begin(); it != clocks.end(); ++it)
    {
        std::cout << *it << std::endl;
    }
    for (auto it = clocks.begin(); it != clocks.end(); ++it)
    {
        std::cout << *it << std::endl;
    }
    drink d(COFFEE, HOT, SMALL, "", "");
    // drink::baseToStr.at(static_cast<baseType>(47));
    drink e(COFFEE, HOT, SMALL, "", "");
    std::vector<drink> drinks;
    drinks.push_back(d);
    drinks.push_back(e);
    drinks.push_back(createDrink());

    std::unique_ptr<drink> ePtr = e.clone();
    std::cout << ePtr->tostring() << std::endl;

    return 0;
}

template <class t>
t magicTemplate(t val1, t val2)
{
    t answer = val1 + val2;
    /*  if (val1 >= val2)
         answer = answer * val1;
     else
         answer = answer * val2; */
    return answer;
}

drink createDrink()
{
    std::string drinkSize;
    std::string drinkBase;
    std::string drinkTemp;
    std::string dairy;
    std::string flavor;
    std::cout << "Please enter the drink size (small, medium, large):" << std::endl;
    std::cin >> drinkSize;
    std::transform(drinkSize.begin(), drinkSize.end(), drinkSize.begin(), ::toupper);
    while (!drink::strToSize.count(drinkSize))
    {
        // std::cout << "You must enter small, medium, or large." << std::endl;
        std::cout << "You must enter ";
        auto it = drink::sizeToStr.begin();
        std::cout << it->second;
        for (++it; it != drink::sizeToStr.end(); ++it)
        {
            auto last = drink::sizeToStr.rbegin();
            if (last->second == it->second)
                std::cout << ", or " << it->second << "." << std::endl;
            else
                std::cout << ", " << it->second;
        }

        std::cout << "Please enter the drink size (small, medium, large):" << std::endl;
        std::cin >> drinkSize;
        std::transform(drinkSize.begin(), drinkSize.end(), drinkSize.begin(), ::toupper);
    }

    std::cout << "Please enter the drink base (coffee, tea, cream):" << std::endl;
    std::cin >> drinkBase;
    std::transform(drinkBase.begin(), drinkBase.end(), drinkBase.begin(), ::toupper);
    while (!drink::strToBase.count(drinkBase))
    {

        std::cout << "You must enter coffee, tea, or cream." << std::endl;
        std::cout << "Please enter the drink base (coffee, tea, cream):" << std::endl;
        std::cin >> drinkBase;
        std::transform(drinkBase.begin(), drinkBase.end(), drinkBase.begin(), ::toupper);
    }
    std::cout << "Please enter the drink temperature (hot, iced, blended):" << std::endl;
    std::cin >> drinkTemp;
    std::transform(drinkTemp.begin(), drinkTemp.end(), drinkTemp.begin(), ::toupper);

    while (!drink::strToTemp.count(drinkTemp))
    {

        std::cout << "You must enter hot, iced, or blended." << std::endl;
        std::cout << "Please enter the drink temperature (hot, iced, blended):" << std::endl;
        std::cin >> drinkTemp;
        std::transform(drinkTemp.begin(), drinkTemp.end(), drinkTemp.begin(), ::toupper);
    }
    std::cout << "Please enter a flavor for your drink: ";
    std::cin >> std::ws;
    std::getline(std::cin, flavor);
    std::cout << "What kind of dairy would you like? ";
    std::cin >> std::ws;
    std::getline(std::cin, dairy);
    /*  std::string dairyCpy = dairy;
     std::transform(dairyCpy.begin(), dairyCpy.end(), dairyCpy.begin(), ::tolower);
     while (!drink::dairyPrice.count(dairyCpy))
     {
         std::cout << "That is an invalid dairy type. " << std::endl;
         std::cout << "What kind of dairy would you like? ";
         std::cin >> std::ws;
         std::getline(std::cin, dairy);
         dairyCpy = dairy;
         std::transform(dairyCpy.begin(), dairyCpy.end(), dairyCpy.begin(), ::tolower);
     } */
    return drink(drinkBase, drinkTemp, drinkSize, dairy, flavor);
}
