#include "Phonebook.h"
#include <fstream>
using std::ifstream;
#include <iostream>
using std::iostream;

Phonebook::Phonebook() {

}


Phonebook& Phonebook::getInstance() {
    static Phonebook instance;
    return instance;
}

void Phonebook::loadPhonebook(const string& filepath) {
    empty();
    ifstream myfile(filepath);
    



}

void Phonebook::empty() {
    if(!tree.isEmpty()){
        tree.empty();
    } 
}