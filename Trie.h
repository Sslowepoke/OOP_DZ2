#pragma once 

#include "Node.h"
#include <string>
#include <Number.h>
#include <stack>

class Trie {
public:
    Trie() : root(new Node()) {}

    //returns a pointer to terminal node with given name if it exists, or nullptr if it doesn't
    Node* search (const std::string& name);
    //inserts a node with given name and contact
    void insert(const std::string& name, Contact* contact);
    //inserts a node with given contact
    void insertContact(Contact* contact);
    //prints to ostream all terminal nodes that are descendants of given node (will print all nodes if root is given)
    void printFrom(Node* start, std::ostream os);
    //prints the whole tree
    friend std::ostream& operator<<(std::ostream& os, Trie tree);
    //deletes a node at given pointer (must be terminal node)
    void deleteNode(Node* to_delete);
    //returns a stack of Node* with a path to given node
    std::stack<Node*> getPath(Node* node);

private:
    Node* root;
    //returns a pointer to node with given name if it exists
    Node* getNode(const std::string& name);
};