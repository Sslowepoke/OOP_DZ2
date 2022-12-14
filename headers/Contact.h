#pragma once

#include "Number.h"
#include "Trie.h"
#include <string>
#include <iostream>


class Contact {
public:
    Contact(const std::string& name, const std::string& number) : name(name), number(number) {}
    
    friend std::ostream& operator<<(std::ostream& os, const Contact& contact);\
    std::string getName();
    void changeNumber(std::string& new_number);
    void changeName(std::string& new_name);

private:
    Number number;
    std::string name;
};