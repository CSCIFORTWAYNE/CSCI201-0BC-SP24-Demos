#ifndef CLOCKE_H
#define CLOCKE_H
#include <stdexcept>
#include <string>

class invalid_hour : public std::invalid_argument
{
public:
    invalid_hour(std::string msg = "Invalid hour exception");
    const char *what() const noexcept;
};

#endif