#include <iostream>
#include "Phonebook.h"


int main() {   
        Phonebook& p = Phonebook::getInstance();
        p.loadPhonebook("tst.csv");
        p.openTerminal();


    return 0;

}