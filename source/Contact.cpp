#include "Contact.h"

std::ostream& operator<<(std::ostream& os, const Contact& contact) {
    return os << contact.name << " " << contact.number;
}

std::string Contact::getName() {
    return name;
}

void Contact::changeNumber(std::string& new_number) {
    number.changeNumber(new_number);
}

void Contact::changeName(std::string& new_name) {
    name = new_name;
    std::cout << "- Name changed to " << name;
}