#include "Contact.h"

std::ostream& operator<<(std::ostream& os, const Contact& contact) {
    os << "--- " << contact.name << " " << contact.number;
}

std::string Contact::getName() {
    return name;
}