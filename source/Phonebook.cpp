#include "Phonebook.h"
#include <fstream>
using std::ifstream;
#include <iostream>
using std::iostream;
#include <sstream>
using std::stringstream;
#include <iostream>
#include <list>


Phonebook::Phonebook() : tree(), call_history() {}

Phonebook& Phonebook::getInstance(){
    static Phonebook instance;
    return instance;
}

void Phonebook::loadPhonebook(const string& filepath) {
    clear();
    ifstream file(filepath);
    std::string line;
    try {
        if(file.is_open()){
            while(getline(file, line, '\n')) {
                try{
                    int index2 = line.find_last_of('\r');
                    int index = line.find_last_of(',');
                    std::string name = line.substr(0, index);
                    std::string number = line.substr(index+1, index2-index-1);
                    addContact(name, number);
                }
                catch (std::exception& e) {
                    std::cout << e.what() << std::endl;
                }
            }
        }
    }
    catch (std::exception& e) {
        std::cout << "- " << e.what() << std::endl;
    }
}

void Phonebook::addContact(const std::string&name, const std::string& number) {
    tree.insertContact(new Contact(name, number));
}

void Phonebook::clear() {
    call_history.clear();
    if(!tree.empty()){
        tree.clear();
    } 
}

void Phonebook::openTerminal() {
    while(1) {
        try {
            string command;
            std::cout << "Enter the command: ";
            getline(std::cin, command, '\n');
            if(command == "NEW" || command == "new") terminalNew();
            if(command == "SEARCH" || command == "search") terminalSearch();
            if(command == "SELECT" || command == "select") terminalSelect();
            if(command == "DELETE" || command == "delete") terminalDelete();
            if(command == "EDIT" || command == "edit") terminalEdit();
            if(command == "EXIT" || command == "exit") break;
            if(command == "HELP" || command == "help") terminalHelp();
            if(command == "CALL HISTORY" || command == "call history") terminalCallHistory();
            if(command == "CALL" || command == "call") terminalCall();
        }
        catch (std::exception& e) {
            std::cout << "- " << e.what() << std::endl;
        }
    }
}

void Phonebook::welcomeMessage() const {
    std::cout << "--------------------------" << std::endl
        << "Welcome to your phonebook!" << std::endl 
        << "--------------------------" << std::endl;
}

void Phonebook::terminalNew() {
    std::cout << "- Enter the contact name: ";
    string name;
    std::getline(std::cin, name, '\n');
    std::cout << "- Enter the contact number: ";
    string number;
    std::getline(std::cin, number, '\n');    
    addContact(name, number);
    std::cout << "- Added contact: " << name << " " << number << std::endl;
}

// void Phonebook::terminalSearch() {
//     std::cout << "- Enter the contact name or first few letters: ";
//     std::string prefix;
//     std::getline(std::cin, prefix, '\n');
//     std::list<Contact*> matches = tree.startsWith(prefix);
//     std::cout << "- " << matches.size() << " contacts have been found: " << std::endl;
//     for(auto contact : matches) {
//         std::cout << "-- " << (*contact) << std::endl;
//     }
// }

void Phonebook::terminalSearch() const {
    std::cout << "- Enter the contact name or first few letters: ";
    std::string prefix;
    std::getline(std::cin, prefix, '\n');
    tree.printPrefix(prefix);
}

void Phonebook::terminalSelect() {
    std::cout << "- Enter the contact name: ";
    std::string name;
    std::getline(std::cin, name, '\n');
    selected_contact = tree.getContact(name);
}

void Phonebook::terminalDelete() {
    if(!selected_contact) throw no_contact_selected();
    call_history.deletedContact(selected_contact);
    tree.deleteContact(selected_contact);
    selected_contact = nullptr;
}

void Phonebook::terminalEdit() {
    if(!selected_contact) throw no_contact_selected();
    std::cout << "- Enter 1 to change name, 2 to change number and 3 to change both ";
    int choice;
    std::cin >> choice;
    //maybe not needed
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
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
    std::getline(std::cin, name, '\n');
    tree.changeContactName(selected_contact, name);
}

void Phonebook::changeSelectedNumber() {
    std::cout << "- Enter the new number ";
    string number;
    std::getline(std::cin, number, '\n');
    selected_contact->changeNumber(number);
}

void Phonebook::terminalHelp() const{
    std::cout << "List of commands: " << std::endl
        << "- NEW - adds a new contact" << std::endl
        << "- SEARCH - shows all contacts beginning with given prefix" << std::endl
        << "- SELECT - selects the contact with given name" << std::endl
        << "- DELETE - deletes the selected contact" << std::endl
        << "- EDIT - edits the selected contact" << std::endl
        << "- CALL - calls the selected contact" << std::endl
        << "- CALL_HISTORY - shows call history" <<std::endl
        << "- EXIT - quits program" << std::endl;
}

void Phonebook::terminalCall() {
    if(!selected_contact) throw no_contact_selected();
    call_history.call(selected_contact);
}

void Phonebook::terminalCallHistory() const{
    std::cout << call_history;
}
