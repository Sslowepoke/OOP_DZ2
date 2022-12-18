#pragma once
#include <exception>
#include <string>
using std::string;
using std::logic_error;
using std::runtime_error;


class PhonebookException : public std::exception {
public:
    string whatstr;
    PhonebookException(const string& what) : whatstr(what) {}
    const char* what() const _NOEXCEPT override {
        return whatstr.c_str();
    }
};

class no_node_selected : public PhonebookException {
public:
    no_node_selected() : PhonebookException("No node was selected") {}
};

class node_not_terminal : public PhonebookException {
public:
    node_not_terminal() : PhonebookException("The node you're trying to acces is not a terminal node.") {}
};

class node_nonexistant : public PhonebookException {
public:
    node_nonexistant() : PhonebookException("The node you're trying to access doesn't exist.") {}
};

class invalid_node_selected : public PhonebookException {
public:
    invalid_node_selected() : PhonebookException("The selected node is not a terminal node") {}
};

class invalid_number_format : public PhonebookException {
public:
    invalid_number_format(const std::string& number) : PhonebookException("The number you entered is not in a valid format." + number) {}
};

class number_too_long : public PhonebookException {
public:
    number_too_long() : PhonebookException("The number you entered is too long.") {}
};

class contact_already_exists : public PhonebookException {
public:
    contact_already_exists() : PhonebookException("A contact with that name already exists.") {}
};

