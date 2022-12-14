#pragma once

#include <string>
#include <iostream>

class Number {
public:
    Number(const std::string& string_number);
    friend std::ostream& operator<<(std::ostream& os, const Number& number);

    void changeNumber(std::string& string_number);

private:
    std::string prefix;
    std::string call_number;
    std::string number;

};