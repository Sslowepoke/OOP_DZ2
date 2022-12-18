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
    void openTerminal();
    void loadPhonebook(const string& filepath);

    Phonebook(Phonebook const&) = delete;
    void operator=(Phonebook const&) = delete;

private:
    Phonebook();
    Trie tree;
    CallHistory call_history;

    static constexpr int call_history_length = 10;



    //empties phonebook (deletes all data)
    void empty();
    //makes a new contact and adds it to the trie
    void addContact(std::string&name, const std::string& number);
    //and prints out new contact added
    void addContactPrint(std::string& name, const std::string& nubmer);
    //prints a welcome message
    void welcomeMessage();
    //changes selected contact's number
    void changeSelectedNumber();
    //changes selected contact's name
    void changeSelectedName();
    //clears cin buffer
    void flushCin();
    //adds the contact to call_history
    void addToCallHistory(Contact* contact);

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