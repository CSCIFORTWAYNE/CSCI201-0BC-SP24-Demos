#include <iostream>
#include <string>
#include <exception>
#include <limits>

int getPositiveInt(std::string prompt);
void resetStream();

int main()
{
    int x;
    // std::cin.exceptions(std::istream::badbit | std::istream::failbit);
    bool isValid = false;
    while (!isValid)
    {
        try
        {
            x = getPositiveInt("Enter a positive number: ");
            isValid = true;
        }
        catch (std::ios_base::failure e)
        {
            std::cout << e.what() << std::endl;
            std::cout << "There was an input error." << std::endl;
            resetStream();
        }
        catch (std::domain_error e)
        {
            std::cout << e.what() << std::endl;
        }
    }

    return 0;
}

int getPositiveInt(std::string prompt)
{
    int x;
    std::cout << prompt;
    std::cin >> x;
    std::cout << std::endl;
    if (!std::cin)
    {
        throw std::ios_base::failure("There was an error getting the positive integer. The user most likely entered a character instead.");
    }
    else if (x <= 0)
    {
        throw std::domain_error("The number entered is less than 0");
    }
    return x;
}

void resetStream()
{
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}
