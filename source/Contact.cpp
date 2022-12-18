#include "Contact.h"

std::ostream& operator<<(std::ostream& os, const Contact& contact) {
    return os << contact.name << " " << contact.number;
}

std::string Contact::getName() {
    return this->name;
}

void Contact::changeNumber(std::string& new_number) {
    delete number;
    number = Number::makeNumber(new_number);
    std::cout << "- Number changed to: " << number << std::endl;
}

void Contact::changeName(std::string& new_name) {
    name = new_name;
    std::cout << "- Name changed to " << name << std::endl;
}

Contact::Contact(const std::string& name, const std::string& number)  
    : name(name), number(Number::makeNumber(number)) {}

Contact::Contact(const Contact& contact) 
    :name(contact.name), number(contact.number->makeCopy()) {}
    
Contact::~Contact() {
    delete number;
}