#include "clockExcept.h"

invalid_hour::invalid_hour(std::string msg) : invalid_argument(msg)
{
}

const char *invalid_hour::what() const noexcept
{

    return invalid_argument::what();
}
