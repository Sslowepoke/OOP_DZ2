#include "Phonebook.h"
#include <fstream>
using std::ifstream;
#include <iostream>
using std::iostream;
#include <sstream>
using std::stringstream;
#include <iostream>
#include <list>


Phonebook::Phonebook() : tree(), call_history() {

}

Phonebook& Phonebook::getInstance(){
    static Phonebook instance;
    return instance;
}

void Phonebook::loadPhonebook(const string& filepath) {
    empty();
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
                catch (contact_already_exists& e) {

                }
            }
        }
    }
    catch (std::exception& e) {
        std::cout << "- " << e.what() << std::endl;
    }
}

void Phonebook::addContact(std::string&name, const std::string& number) {
    tree.insertContact(new Contact(name, number));
}

void Phonebook::addContactPrint(std::string& name, const std::string& number) {
    stringstream ss;
    ss << "- Added contact: " << std::endl << (*tree.insertContact(new Contact(name, number)));
    std::cout << ss.str();
}

void Phonebook::empty() {
    if(!tree.isEmpty()){
        tree.empty();
    } 
}

void Phonebook::openTerminal() {
    while(1) {
        try {
            string command;
            std::cout << "Enter the command: ";
            getline(std::cin, command, '\n');
            if(command == "NEW") terminalNew();
            if(command == "SEARCH") terminalSearch();
            if(command == "SELECT") terminalSelect();
            if(command == "DELETE") terminalDelete();
            if(command == "EDIT") terminalEdit();
            if(command == "EXIT") break;
            if(command == "HELP") terminalHelp();
            if(command == "CALL HISTORY") terminalCallHistory();
            if(command == "CALL") terminalCall();
        }
        catch (std::exception& e) {
            std::cout << "- " << e.what() << std::endl;
        }
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
    // flushCin();
    std::getline(std::cin, name, '\n');
    std::cout << "- Enter the contact number: ";
    string number;
    // flushCin();
    std::getline(std::cin, number, '\n');    
    addContactPrint(name, number);
}

// void Phonebook::terminalSearch() {
//     std::cout << "- Enter the contact name or first few letters: ";
//     std::string prefix;
//     // flushCin();
//     std::getline(std::cin, prefix, '\n');
//     tree.printPrefix(std::cout, prefix);
// }

// also prints number of contacts found
void Phonebook::terminalSearch() {
    std::cout << "- Enter the contact name or first few letters: ";
    std::string prefix;
    std::getline(std::cin, prefix, '\n');
    std::list<Contact*> matches = tree.startsWith(prefix);
    std::cout << "- " << matches.size() << " contacts have been found: " << std::endl;
    for(auto contact : matches) {
        std::cout << "-- " << (*contact) << std::endl;
    }
}

void Phonebook::terminalSelect() {
    std::cout << "- Enter the contact name: ";
    std::string name;
    // flushCin();
    std::getline(std::cin, name, '\n');
    tree.selectNode(name);
}

void Phonebook::terminalDelete() {
    tree.deleteSelected();
}

void Phonebook::terminalEdit() {
    std::cout << "- Enter 1 to change name, 2 to change number and 3 to change both ";
    int choice;
    std::cin >> choice;
    flushCin();
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
    // flushCin();
    std::getline(std::cin, name, '\n');
    tree.changeSelectedName(name);
}

void Phonebook::changeSelectedNumber() {
    std::cout << "- Enter the new number ";
    string number;
    std::getline(std::cin, number, '\n');
    tree.changeSelectedNumber(number);
}

void Phonebook::terminalHelp() {
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

void Phonebook::flushCin() {
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}
//CALLS CONTACT WITH GIVEN NAME
// void Phonebook::terminalCall() {
//     std::cout << "- Enter the contact name: ";
//     std::string name;
//     flushCin();
//     std::getline(std::cin, name);
//     Contact* contact = tree.getContact(name);
//     call_history.call(contact);
// }

void Phonebook::terminalCall() {
    call_history.call(tree.getSelectedContact());
}

void Phonebook::terminalCallHistory() {
    std::cout << call_history;
}
