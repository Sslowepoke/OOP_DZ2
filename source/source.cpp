#include <iostream>
#include "Phonebook.h"


int main() {   
        Phonebook& p = Phonebook::getInstance();
        std::cout << "radi";
        p.loadPhonebook("tst.csv");


    return 0;

}