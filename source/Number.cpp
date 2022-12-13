#include "Number.h"

std::ostream& operator<<(std::ostream& os, const Number& number) {
    os << number.prefix << " " <<  number.call_number << " " << number.number << " ";
}