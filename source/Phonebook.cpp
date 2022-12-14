#include "Phonebook.h"
#include <fstream>
using std::ifstream;
#include <iostream>
using std::iostream;
#include <sstream>
using std::stringstream;
#include <iostream>


Phonebook::Phonebook() : tree() {

}

Phonebook& Phonebook::getInstance() {
    static Phonebook instance;
    return instance;
}

void Phonebook::loadPhonebook(const string& filepath) {
    empty();
    ifstream file(filepath);
    std::string line;
    if(file.is_open()){
        while(getline(file, line, '\n')) {
            stringstream ss = stringstream(line);
            std::string name, number;
            getline(ss, name, ',');
            getline(ss, number, '\r');
            addContact(name, number);
        }
    }
}

Contact* Phonebook::addContact(std::string&name, const std::string& number) {
    return tree.insertContact(new Contact(name, number));
}

void Phonebook::empty() {
    if(!tree.isEmpty()){
        tree.empty();
    } 
}

void Phonebook::openTerminal() {
    while(1) {
        string command;
        std::cout << "Enter the command: ";
        std::cin >> command;
        if(command == "NEW") terminalNew();
        if(command == "SEARCH") terminalSearch();
        if(command == "SELECT") terminalSelect();
        if(command == "DELETE") terminalDelete();

    }
}

void Phonebook::welcomeMessage() {
    std::cout << "--------------------------" << std::endl
        << "Welcome to your phonebook!" << std::endl 
        << "--------------------------" << std::endl;
}

void Phonebook::terminalNew() {
    std::cout << "- Enter the contact name: ";
    string name;
    std::cin >> name;
    std::cout << "- Enter the contact number: ";
    string number;
    std::cin >> number;
    Contact* added_contact = addContact(name, number);
    std::cout << "- Contact " << added_contact << "has been added" << std::endl;
}

void Phonebook::terminalSearch() {
    std::cout << "- Enter the contact name or first few letters: ";
    std::string prefix;
    std::cin >> prefix;
    tree.printPrefix(std::cout, prefix);
}

void Phonebook::terminalSelect() {
    std::cout << "- Enter the contact name: ";
    std::string name;
    std::cin >> name;
    tree.selectNode(name);
}

void Phonebook::terminalDelete() {
    tree.deleteSelected();
}

void Phonebook::terminalEdit() {
    std::cout << "- Enter 1 to change name, 2 to change number and 3 to change both ";
    int choice;
    std::cin >> choice;
    switch(choice){
    case 1:
        changeSelectedName(); break;
    case 2:
        changeSelectedNumber(); break;
        break;
    case 3:
        changeSelectedName();
        changeSelectedNumber();
        break;
    default:
        std::cout << "- No contact is selected" << std::endl;
        break;
    }
}

void Phonebook::changeSelectedName() {
    std::cout << "- Enter the new name ";
    string name;
    std::cin >> name;
    tree.changeSelectedName(name);
}

void Phonebook::changeSelectedNumber() {
    std::cout << "- Enter the new number ";
    string number;
    std::cin >> number;
    tree.changeSelectedNumber(number);
}

