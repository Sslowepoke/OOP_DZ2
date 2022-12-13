#include "Trie.h"


void Trie::insert (const std::string& name, Contact* contact) {
    Node* curr = root;
    for(auto& ch : name) {
        if(Node* tmp = curr->children[ch]) {
            curr = tmp;
        }
        else {
            //makes a new node
            tmp = new Node();
            curr = tmp;
        }
    }
    curr->is_terminal = true;
    curr->contact = contact;
}

void Trie::insertContact(Contact* contact) {
    Node* curr = root;
    for(auto& ch : contact->getName()) {
        if(curr->children[ch]) {
            curr = curr->children[ch];
        }
        else {
            //makes a new node
            curr->children[ch] = new Node();
            curr = curr->children[ch];
        }
    }
    curr->is_terminal = true;
    curr->contact = contact;
}

Node* Trie::getNode (const std::string& name) {
    Node* current = root;
    for(auto& ch : name) {    
        if(current->children[ch] == nullptr) return nullptr; 
        current = current->children[ch];
    }
    return current;
}   

Node* Trie::search (const std::string& name) {
    Node* tmp = getNode(name);
    if(tmp != nullptr && tmp->is_terminal) return tmp;
    else return nullptr;
}

void Trie::printFrom(Node* start, std::ostream os) {
    os << start;
}

std::ostream& operator<<(std::ostream& os, Trie tree) {
    return os << tree.root; 
}

void Trie::deleteNode(Node* to_delete) {
    if(!to_delete->is_terminal) return; //cant delete a non-terminal node
    to_delete->is_terminal = false;
    if(to_delete->hasChildren()) return;
    std::stack<Node*> stack = getPath(to_delete);
    Node* current;
    Node* previous;
    int depth = stack.size();
    while(1) {
        current = stack.top();
        stack.pop();
        previous = stack.top();
        if(current->hasChildren() || current->is_terminal) break;
        delete(current);
         //sets the pointer to deleted node to null
        previous->children[to_delete->contact->getName()[depth]] = nullptr;
    }
}

std::stack<Node*> Trie::getPath(Node* node) {
    Node* current = root;
    std::stack<Node*> stack;
    for(char& ch : node->contact->getName()) {
        // if(current->children[ch] == nullptr) //error
        current = current->children[ch];
        stack.push(current);
    }
    return stack;
}


