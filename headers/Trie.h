#pragma once 

#include <vector>
#include <string>
#include <stack>
#include <iostream>

#include "Number.h"
#include "Contact.h"

class Trie {
//node-------------------------------------------------------------------------------
private:
    class Node {
    public:

        Node() : contact(), children(alphabet_size), is_terminal(false) {}
        Node(Contact* contact) : contact(contact), children(alphabet_size), is_terminal(true) {}

        //checks if the node has any children
        bool hasChildren() const;


        Contact* contact;
        std::vector<Node*> children;
        bool is_terminal;


    };

public:
    Trie() : root(new Node()) {}
    ~Trie();

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
    //traverses the tree

    //checks if trie is empty
    bool isEmpty();
    //empties tree
    void empty();

    //node ---
    //prints a node
    friend std::ostream& operator<<(std::ostream& os, const Node& node);
    //prints all terminal nodes of a sub trie
    friend std::ostream& operator<<(std::ostream& os, Node* start);


private:
    Node* root;
    //returns a pointer to node with given name if it exists
    Node* getNode(const std::string& name);
    //returns a pointer to terminal node with given name if it exists, or nullptr if it doesn't
    Node* search (const std::string& name);
    //deletes a subtrie with given pointer as root
    void deleteSubtrie(Node* root);
    //translates ascii char to its counterpart index in vector children
    char charToIndex(char c) const;

    static constexpr int alphabet_size = 53;

};