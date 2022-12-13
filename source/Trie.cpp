#include "Trie.h"


void Trie::insert (const std::string& name, Contact* contact) {
    Node* curr = root;
    for(auto& ch : name) {
        if(Node* tmp = curr->children[charToIndex(ch)]) {
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
        char index = charToIndex(ch);
        if(curr->children[index]) {
            curr = curr->children[index];
        }
        else {
            //makes a new node
            curr->children[index] = new Node();
            curr = curr->children[index];
        }
    }
    curr->is_terminal = true;
    curr->contact = contact;
}

Trie::Node* Trie::getNode (const std::string& name) {
    Node* current = root;
    for(auto& ch : name) {    
        char index = charToIndex(ch);
        if(current->children[index] == nullptr) return nullptr; 
        current = current->children[index];
    }
    return current;
}   

Trie::Node* Trie::search (const std::string& name) {
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

std::stack<Trie::Node*> Trie::getPath(Node* node) {
    Node* current = root;
    std::stack<Node*> stack;
    for(char& ch : node->contact->getName()) {
        // if(current->children[ch] == nullptr) //error
        current = current->children[charToIndex(ch)];
        stack.push(current);
    }
    return stack;
}

Trie::~Trie() {
    deleteSubtrie(root);
}

void Trie::deleteSubtrie(Node* root) {
    if(!root->hasChildren()) {
        delete(root);
        return;
    }
    for(char c = 0; c < alphabet_size; c++) {
        if(root->children[c]) 
            deleteSubtrie(root->children[c]);
    }
}

bool Trie::isEmpty() {
    return !root->hasChildren();
}

void Trie::empty() {
    for(char c = 0; c < alphabet_size; c++) {
        if(root->children[c])
            deleteSubtrie(root->children[c]);
    }
}

//node----------------------------------------------------------------------------------

std::ostream& operator<<(std::ostream& os, const Trie::Node& node){
    os << (*node.contact);
    return os;
}

std::ostream& operator<<(std::ostream& os, Trie::Node* start) {
    if(start == nullptr) return os;
    if(start->is_terminal) os << (*start);
    for(char c = 0; c < Trie::alphabet_size; c++) {
        if(start->children[c]!=nullptr) os << start->children[c];
    }
}

bool Trie::Node::hasChildren() const{
    for(Node* ptr : children) {
        if(ptr != nullptr) return true;
    }
    return false;
}

char Trie::charToIndex(char c) const{
    if(c >= 'a' && c <= 'z')
        return c - 'a';
    if (c >= 'A' && c <= 'Z')
        return c - 'A';
    if (c == ' ')
        return 52;
}
