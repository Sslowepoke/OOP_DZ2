#pragma once 

#include <vector>
#include <string>
#include <stack>
#include <iostream>
#include <list>
using std::vector;

#include "Contact.h"
#include "PhonebookException.h"
#include "List.h"
class Trie {
//node-------------------------------------------------------------------------------
private:
    class Node {
    public:
        Node() : contacts(0){}
        ~Node();

        //checks if its a terminal
        bool isTerminal() const { return !contacts.empty(); }
        //checks if the node has any children
        bool hasChildren() const;
        //inserts a contact
        void insertContact(Contact* contact);
        //adds all contacs to the given list
        void addToList(std::list<Contact*> *list, const std::string& prefix) const;
        //prints all contacts
        void print(int& cnt, const std::string& prefix) const;
        //returns a contact with given name
        Contact* getContact(const std::string& name);
        //deletes the given contact
        void deleteContact(Contact* contact);
        //returns the prefix that leads to this node
        std::string getPrefix() const;
        //replaces contact with it's copy
        Contact* unlinkContact(const Contact* contact);
        //returns no of contacts
        int contactCount() const;
        //deletes all contacts
        void clear();

        std::list<Contact*> contacts;
        List<Node*> children;
    };
public:
    Trie() : root(new Node()) {}
    ~Trie();

    //inserts a node with given contact and returns a pointer to it
    void insertContact(Contact* contact);
    //checks if trie is empty
    bool empty() const;
    //empties tree
    void clear();
    //prints all terminal nodes with names that begin with given prefix
    void printPrefix(const std::string& prefix) const;
    //deletes the given contact
    void deleteContact(Contact* contact);
    //changes name of given contact
    void changeContactName(Contact* contact, const std::string& new_name);
    //returns a contact pointer to contact with given name
    Contact* getContact(const std::string& name);
    //returns a list of pointers to contacts whose names start with given string
    std::list<Contact*> startsWith(const std::string& prefix);

private:
    Node* root;
    vector<Node*> terminals;
    //returns a pointer to node with given name if it exists
    Node* getNode(const std::string& name) const;
    //removes given terminal node from vector terminals
    void removeFromTerminals(const Node* node);
    //returns a list of contacts who are descendants of given node
    std::list<Contact*> descendantContacts(Node* root, const std::string& prefix);
    //unlinks contact from tree
    void unlinkContact(const Contact* contact);
    //deletes a node at given pointer (must be terminal node)
    void deleteNode(Node* to_delete);
    //returns a stack of Node* with a path to given node
    std::stack<Node*> getPath(const Node* node) const;

    static constexpr int max_depth = 12;

};