#pragma once

#include <string>
using std::string;

#include "Trie.h"
#include "Contact.h"

class Phonebook {
public:
    
    static Phonebook& getInstance();
    //official requirements
    void openTerminal();
    void loadPhonebook(const string& filepath);


private:
    Phonebook();
    Trie tree;

    //empties phonebook (deletes all data)
    void empty();
    //makes a new contact and adds it to the trie
    Contact* addContact(std::string&name, const std::string& number);
    //prints a welcome message
    void welcomeMessage();
    //changes selected contact's number
    void changeSelectedNumber();
    //changes selected contact's name
    void changeSelectedName();

    //commmands
    void terminalNew();
    void terminalSearch();
    void terminalSelect();
    void terminalDelete();
    void terminalEdit();
    
};