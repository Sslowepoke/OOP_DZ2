#pragma once

#include "Number.h"
#include <string>
#include <iostream>


class Contact {
public:
    Contact(const std::string& name, const std::string& number);
    Contact(const Contact& contact);
    ~Contact();
    
    friend std::ostream& operator<<(std::ostream& os, const Contact& contact);
    std::string getName() const;
    void changeNumber(const std::string& new_number);
    void changeName(const std::string& new_name);

private:
    Number* number;
    std::string name;
};