#pragma once

#include <string>
#include <iostream>

class Number {
public:
    
    friend std::ostream& operator<<(std::ostream& os, const Number& number);

private:
    std::string prefix;
    std::string call_number;
    std::string number;

};