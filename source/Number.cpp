#include "Number.h"
#include <sstream>


std::ostream& operator<<(std::ostream& os, const Number& number) {
    return os << number.prefix << " " <<  number.call_number << " " << number.number << " ";
}

Number::Number(const std::string& string_number) {
    std::stringstream ss(string_number);
    ss >> prefix >> call_number >> number;
}

void Number::changeNumber(std::string& string_number) {
    std::stringstream ss(string_number);
    ss >> prefix >> call_number >> number;
    std::cout << "- Number changed to " << (*this) << std::endl;
}
