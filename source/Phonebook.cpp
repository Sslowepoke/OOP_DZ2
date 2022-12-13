#include "Phonebook.h"


Phonebook& Phonebook::getInstance() {
    static Phonebook instance;
    return instance;
}

