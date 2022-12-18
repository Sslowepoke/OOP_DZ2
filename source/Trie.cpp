#include "Trie.h"
#include <queue>
using std::queue;


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

Trie::Node* Trie::insertContact(Contact* contact) {
    Node* curr = root;
    std::string name = contact->getName();
    for(char& ch : name) {
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
    if(curr->is_terminal) throw contact_already_exists();
    curr->is_terminal = true;
    curr->contact = contact;
    terminals.push_back(curr);
    return curr;
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
    if(tmp == nullptr) throw node_nonexistant();
    if(!tmp->is_terminal) throw node_not_terminal();
    return tmp;
}

void Trie::printFrom(Node* start, std::ostream os) {
    os << start;
}

std::ostream& operator<<(std::ostream& os, Trie tree) {
    return os << tree.root; 
}

void Trie::deleteNode(Node* to_delete) {
    if(!to_delete->is_terminal) return; //cant delete a non-terminal node
    if(to_delete->hasChildren()) {
        to_delete->is_terminal = false;
        delete(to_delete->contact);
        to_delete->contact = nullptr;
        return;
    }
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
    to_delete->is_terminal = false;
    delete(to_delete->contact);
    to_delete->contact = nullptr;
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
    // deleteSubtrie(root);
    for(auto node : terminals) {
        deleteNode(node);
    }
}

// recursive
// void Trie::deleteSubtrie(Node* root) {
//     if(!root->hasChildren()) {
//         delete root;
//         return;
//     }
//     for(char c = 0; c < alphabet_size; c++) {
//         if(root->children[c]) 
//             deleteSubtrie(root->children[c]);
//     }
// }

//levelOrder
void Trie::deleteSubtrie(Node* root) {
    if(!root->hasChildren()) {
        delete root;
        return;
    }
    if(root == nullptr) {
        return;
    }
    queue<Node*> queue;
    Node* curr;
    queue.push(root);
    while(queue.size() > 0) {
        curr = queue.front();
        queue.pop();

        if(curr == nullptr) {
        }
        else {
            for(char c = 0; c < alphabet_size; c++) {
                if(curr->children[c]) {
                    queue.push(curr->children[c]);
                }
            }
                delete curr;
        }
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

std::ostream& Trie::printPrefix(std::ostream& os, std::string& prefix) {
    return os << getNode(prefix);
}

void Trie::selectNode(std::string& name) {
    selected_node = search(name);
    std::cout << "- Contact " << (*selected_node->contact) << "is now selected." << std::endl;
}

void Trie::deleteSelected() {
    if(!selected_node) throw no_node_selected();
    deleteNode(selected_node);
}

void Trie::changeSelectedNumber( std::string& number) {
    if(!selected_node) throw no_node_selected();
    selected_node->contact->changeNumber(number);
}

void Trie::changeSelectedName(std::string& name) {
    if(!selected_node) throw no_node_selected();
    Contact* contact = new Contact(*selected_node->contact);
    contact->changeName(name);
    Node* inserted_node = insertContact(contact);
    deleteNode(selected_node);
    selected_node = inserted_node;
}

void Trie::printSelected() {
    if(!selected_node) throw no_node_selected();
    std::cout << (*selected_node);
}

Contact* Trie::getContact(const std::string& name) {
    Node* node = getNode(name);
    return node->contact;
}

Contact* Trie::getSelectedContact() {
    if(!selected_node) throw no_node_selected();
    return selected_node->contact;
}

std::list<Contact*> Trie::startsWith(const std::string& prefix) {
    Node* node = getNode(prefix);
    return terminalChildren(node);
}

std::list<Contact*> Trie::terminalChildren(Node* root) {
    std::stack<Node*> s;
    std::list<Contact*> list;
    if(!root) return list;
    Node* curr;
    s.push(root);
    while(s.size()) {
        curr = s.top();
        s.pop();
        if(curr->is_terminal) list.push_back(curr->contact);
        for(auto node : curr->children) {
            if(node) s.push(node);
        }
    }
    return list;
}


//node----------------------------------------------------------------------------------

std::ostream& operator<<(std::ostream& os, const Trie::Node& node){
    os << "-- " << (*node.contact) << std::endl;
    return os;
}

std::ostream& operator<<(std::ostream& os, Trie::Node* start) {
    if(start == nullptr) return os;
    if(start->is_terminal) os << (*start);
    for(char c = 0; c < Trie::alphabet_size; c++) {
        if(start->children[c]!=nullptr) os << start->children[c];
    }
    return os;
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
    else if(c >= 'A' && c <= 'Z')
        return c - 'A';
    else if(c == ' ')
        return 26;
    else if(c == '-')
        return 27;
    else if(c == '.')
        return 28;
    else 
        return 29;// sve ostale nepodrzane karaktere tretiram kao jedan (i guess dovoljno dobro)
}
Trie::Node::~Node() {
    if(contact) delete contact;
    contact = nullptr;
}