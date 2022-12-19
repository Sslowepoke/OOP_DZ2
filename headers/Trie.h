#pragma once 

#include <vector>
#include <string>
#include <stack>
#include <iostream>
#include <list>
using std::vector;

#include "Contact.h"
#include "PhonebookException.h"
class Trie {
//node-------------------------------------------------------------------------------
private:
    class Node {
    public:

        Node() : children(alphabet_size), contacts(0){}
        ~Node();

        //translates ascii char to its counterpart index in vector children
        static char charToIndex(char c);
        static constexpr int alphabet_size = 30;
        //checks if its a terminal
        bool isTerminal() const { return !contacts.empty(); }
        //checks if the node has any children
        bool hasChildren() const;
        //inserts a contact
        void insertContact(Contact* contact);
        //adds all contacs to the given list
        void addToList(std::list<Contact*> *list);
        //returns a contact with given name
        Contact* getContact(const std::string& name);
        //deletes the given contact
        void deleteContact(Contact* contact);
        //returns the prefix that leads to this node
        std::string getPrefix();

        std::list<Contact*> contacts;
        std::vector<Node*> children;
    };
public:
    Trie() : root(new Node()) {}
    ~Trie();

    //inserts a node with given contact and returns a pointer to it
    void insertContact(Contact* contact);
    //deletes a node at given pointer (must be terminal node)
    void deleteNode(Node* to_delete);
    //returns a stack of Node* with a path to given node
    std::stack<Node*> getPath(Node* node);

    //checks if trie is empty
    bool empty();
    //empties tree
    void clear();
    //prints all terminal nodes with names that begin with given prefix
    std::ostream& printPrefix(std::ostream& os, std::string& prefix);
    //deletes the given contact
    void deleteContact(Contact* contact);

    //changes name of given contact
    Contact* changeContactName(Contact* contact, const std::string& new_name);
    //returns a contact pointer to contact with given name
    Contact* getContact(const std::string& name);
    //returns a list of pointers to contacts whose names start with given string
    std::list<Contact*> startsWith(const std::string& prefix);
    //returns a list of contacts who are descendants of given node
    std::list<Contact*> descendantContacts(Node* root);


private:
    Node* root;
    vector<Node*> terminals;
    //returns a pointer to node with given name if it exists
    Node* getNode(const std::string& name);

    static constexpr int max_depth = 10;

};