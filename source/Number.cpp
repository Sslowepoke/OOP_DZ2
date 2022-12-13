#include "Number.h"
#include <sstream>


std::ostream& operator<<(std::ostream& os, const Number& number) {
    os << number.prefix << " " <<  number.call_number << " " << number.number << " ";
}

Number::Number(const std::string& string) {
    std::stringstream ss(string);
    ss >> prefix >> call_number >> number;
}

