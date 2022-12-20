#pragma once

#include <string>
using std::string;
#include <list>
using std::list;

#include "Trie.h"
#include "Contact.h"
#include "CallHistory.h"

class Phonebook {
public:
    static Phonebook& getInstance();
    //official requirements
    void openTerminal(); //static
    void loadPhonebook(const string& filepath); //static

    Phonebook(Phonebook const&) = delete;
    void operator=(Phonebook const&) = delete;

private:
    Phonebook();
    Trie tree;
    CallHistory call_history;
    Contact* selected_contact;

    //empties phonebook (deletes all data)
    void clear();
    //makes a new contact and adds it to the trie
    void addContact(std::string&name, const std::string& number);
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
    void terminalHelp();
    void terminalCall();
    void terminalCallHistory();
    
};
