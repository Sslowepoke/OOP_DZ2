#include "Trie.h"
#include <queue>
using std::queue;

void Trie::insertContact(Contact* contact) {
    Node* curr = root;
    std::string name = contact->getName();
    for(int pos = 0; pos < name.length() && pos < max_depth; pos++) {
        char ch = name[pos];

        if(curr->children.has(ch)) {
            curr = curr->children[ch];
        }
        else {
            //makes a new node
            curr->children.insert(ch, new Node());
            curr = curr->children[ch];
            if(pos == max_depth - 1) terminals.push_back(curr); // ??
        }
    }
    curr->insertContact(contact);
}

Trie::Node* Trie::getNode (const std::string& name) const{
    Node* curr = root;
    int depth = 0;
    for(auto& ch : name) {   
        if(depth == max_depth) return curr; 
        depth++;
        if(!curr->children.has(ch)) throw contact_nonexistant(); 
        else curr = curr->children[ch];
    }
    return curr;
}

void Trie::deleteNode(Node* to_delete) {
    if(!to_delete->isTerminal()) throw node_not_terminal();
    if(to_delete->hasChildren()) return;
    std::string name = to_delete->getPrefix();
    std::stack<Node*> stack = getPath(to_delete);
    //======================================
    if(to_delete->contactCount() == 1) {
        to_delete->clear();
    }
    //======================================
    Node *current, *previous;
    for(int depth = stack.size() - 1; depth > 0; depth--){
        current = stack.top();
        stack.pop();
        previous = stack.top();
        if(current->hasChildren() || current->isTerminal()) break;
        delete(current);
        //sets the pointer to deleted node to null
        previous->children.remove(name[depth]);
    }
}

void Trie::removeFromTerminals(const Node* node) {
    for(auto it = terminals.begin(); it <= terminals.end(); it++) {
        if((*it) == node) {
            terminals.erase(it);
        }
    }
}

std::stack<Trie::Node*> Trie::getPath(const Node* node) const {
    Node* current = root;
    std::stack<Node*> stack;
    std::string prefix = node->getPrefix();
    for(char& ch : prefix) {
        // if(current->children[ch] == nullptr) //error
        current = current->children[ch];
        stack.push(current);
    }
    return stack;
}

Trie::~Trie() {
    clear();
}

bool Trie::empty() const {
    return !root->hasChildren();
}

void Trie::clear() {
    if(terminals.empty()) return;
    for(auto node : terminals) {
        deleteNode(node);
    }
    terminals.clear();
}

Contact* Trie::getContact(const std::string& name) {
    Node* node = getNode(name);
    return node->getContact(name);
}

void Trie::deleteContact(Contact* contact) {
    Node* node = getNode(contact->getName());
    if(node->hasChildren() || node->contactCount() > 1) {
        node->deleteContact(contact);
    }
    else {
        removeFromTerminals(node);
        deleteNode(node);
    }
}

std::list<Contact*> Trie::startsWith(const std::string& prefix) {
    Node* node = getNode(prefix);
    return descendantContacts(node, prefix);
}

std::list<Contact*> Trie::descendantContacts(Node* root, const std::string& prefix) {
    std::stack<Node*> s;
    std::list<Contact*> list;
    if(!root) return list;
    Node* curr;
    s.push(root);
    while(s.size()) {
        curr = s.top();
        s.pop();
        if(curr->isTerminal()) {
            curr->addToList(&list, prefix);
        }
        curr->children.pushToStack(s);
    }
    return list;
}

void Trie::changeContactName(Contact* contact, const std::string& new_name) {
    unlinkContact(contact);
    contact->changeName(new_name);
    insertContact(contact);   
}

void Trie::unlinkContact(const Contact* contact) {
    Node* node = getNode(contact->getName());
    Contact* old_contact = node->unlinkContact(contact);
    deleteContact(old_contact);
}

Contact* Trie::Node::getContact(const std::string& name) {
    std::vector<Contact*> vector;
    for(auto contact : contacts) {
        if(contact->getName() == name)
            vector.push_back(contact);
    }
    if(vector.size() > 1) {
        std::cout << "- these contacts match given name: " << std::endl;
        int count = 1;
        for(auto contact : vector) {
            std::cout << "- " << count << ". " << *contact << std::endl;
            count++;
        }
        std::cout << "- please type in the index of the desired contact: ";
        int index;
        std::cin >> index;
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        return vector[index - 1];
    }
    else if(vector.size() == 0) {
        throw contact_nonexistant();   
    }
    else {
        return vector[0];
    }
}

void Trie::printPrefix(const std::string& prefix) const{
    int cnt = 0;
    std::stack<Node*> s;
    Node* curr;
    s.push(getNode(prefix));
    while(s.size()) {
        curr = s.top();
        s.pop();
        if(curr->isTerminal()) {
            curr->print(cnt, prefix);
        }
        curr->children.pushToStack(s);
    }
    std::cout << "-- Found " << cnt << " matches" << std::endl;
}

//node----------------------------------------------------------------------------------

bool Trie::Node::hasChildren() const{
    return !children.empty();
}

void Trie::Node::insertContact(Contact* contact) {
    if(contacts.empty()) {
        contacts.push_back(contact);
        return;
    }
    for (auto it = contacts.begin(); it !=contacts.end(); it++) {
        if(std::strcmp(contact->getName().c_str(), (*it)->getName().c_str()) < 0) {
            contacts.insert(it, contact);
            return;
        }
    }
    contacts.push_back(contact);
}

void Trie::Node::addToList(std::list<Contact*> *list, const std::string& prefix) const{
    for(Contact* contact : contacts) {
        if(contact->getName().find(prefix) != std::string::npos) {
            list->push_front(contact);
        }
    }
}

void Trie::Node::print(int& cnt, const std::string& prefix) const {
    for(Contact* contact : contacts) {
        if(contact->getName().find(prefix) != std::string::npos) {
            std::cout << "-- " << *contact << std::endl;
            cnt++;
        }
    }
}

void Trie::Node::deleteContact(Contact* contact) {
    contacts.remove(contact);
    delete contact;
    contact = nullptr;
}

std::string Trie::Node::getPrefix() const {
    std::string name = contacts.front()->getName();
    if(name.size() > max_depth) 
        return name.substr(0, max_depth);
    else
        return name;
}

Trie::Node::~Node() {
    if(contacts.empty()) return;
    for(auto contact : contacts) {
        delete contact;
    }
}

Contact* Trie::Node::unlinkContact(const Contact* contact) {
    for(auto it = contacts.begin(); it != contacts.end(); it++) {
        if(*it == contact) {
            *it = new Contact(*contact);
            return *it;
        }
    }
    throw contact_nonexistant();
}

int Trie::Node::contactCount() const{
    return contacts.size();
}

void Trie::Node::clear() {
    contacts.clear();
}
