#include "Number.h"
#include <string>
#include <iostream>


class Contact {
public:


    friend std::ostream& operator<<(std::ostream& os, const Contact& contact);\
    std::string getName();

private:
    Number number;
    std::string name;

};