#pragma once

#include <vector>
#include <string>
#include <iostream>
#include "Trie.h"
#include "Contact.h"

class Node {
public:
    friend Trie;

    Node() : contact(), children(256), is_terminal(false) {}
    Node(Contact* contact) : contact(contact), children(256), is_terminal(true) {}

    
    //prints a node
    friend std::ostream& operator<<(std::ostream& os, const Node& node);
    //prints all terminal nodes of a sub trie
    friend std::ostream& operator<<(std::ostream& os, Node* start);
    //checks if the node has any children
    bool hasChildren();

private:
    Contact* contact;
    std::vector<Node*> children;
    bool is_terminal;

};