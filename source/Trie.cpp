#include "Trie.h"
#include <queue>
using std::queue;

void Trie::insertContact(Contact* contact) {
    Node* curr = root;
    std::string name = contact->getName();
    for(int pos = 0; pos < name.length() && pos < max_depth; pos++) {
        char ch = name[pos];
        char index = Node::charToIndex(ch);
        if(curr->children[index]) {
            curr = curr->children[index];
        }
        else {
            //makes a new node
            curr->children[index] = new Node();
            curr = curr->children[index];
            if(pos == max_depth - 1) terminals.push_back(curr); // ??
        }
    }
    curr->insertContact(contact);
}

Trie::Node* Trie::getNode (const std::string& name) {
    Node* current = root;
    int depth = 0;
    for(auto& ch : name) {   
        if(depth == max_depth) return current; 
        depth++;
        char index = Node::charToIndex(ch);
        if(current->children[index] == nullptr) return nullptr; 
        current = current->children[index];
    }
    return current;
}

void Trie::deleteNode(Node* to_delete) {
    if(!to_delete->isTerminal()) throw node_not_terminal();
    if(to_delete->hasChildren()) return;
    std::string name = to_delete->getPrefix();
    std::stack<Node*> stack = getPath(to_delete);
    Node *current, *previous;
    int depth = stack.size();
    while(1) {
        current = stack.top();
        stack.pop();
        previous = stack.top();
        if(current->hasChildren() || current->isTerminal()) break;
        delete(current);
        //sets the pointer to deleted node to null
        char index = Node::charToIndex(name[depth]);
        previous->children[index] = nullptr;
    }
    // removeFromTerminals(to_delete);
    delete to_delete;

}

void Trie::removeFromTerminals(const Node* node) {
    for(auto it = terminals.begin(); it <= terminals.end(); it++) {
        if((*it) == node) {
            terminals.erase(it);
        }
    }
}

std::stack<Trie::Node*> Trie::getPath(Node* node) {
    Node* current = root;
    std::stack<Node*> stack;
    std::string prefix = node->getPrefix();
    for(char& ch : prefix) {
        // if(current->children[ch] == nullptr) //error
        current = current->children[Node::charToIndex(ch)];
        stack.push(current);
    }
    return stack;
}

Trie::~Trie() {
    clear();
}

bool Trie::empty() {
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
        for(auto node : curr->children) {
            if(node) s.push(node);
        }
    }
    return list;
}

void Trie::changeContactName(Contact* contact, const std::string& new_name) {
    // Contact* new_contact = new Contact(*contact);
    // new_contact->changeName(new_name);
    // insertContact(new_contact);
    // deleteContact(contact);
    // return new_contact;
    unlinkContact(contact);
    contact->changeName(new_name);
    insertContact(contact);
    
}

void Trie::unlinkContact(Contact* contact) {
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

//node----------------------------------------------------------------------------------

bool Trie::Node::hasChildren() const{
    if(children.empty()) return false;
    for(Node* ptr : children) {
        if(ptr != nullptr) return true;
    }
    return false;
}

char Trie::Node::charToIndex(char c){
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

void Trie::Node::insertContact(Contact* contact) {
    if(contacts.empty()) {
        contacts.push_front(contact);
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

void Trie::Node::addToList(std::list<Contact*> *list, const std::string& prefix) {
    for(Contact* contact : contacts) {
        if(contact->getName().find(prefix) != std::string::npos) {
            list->push_back(contact);
        }
    }
}

void Trie::Node::deleteContact(Contact* contact) {
    contacts.remove(contact);
    delete contact;
}

std::string Trie::Node::getPrefix() {
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

Contact* Trie::Node::unlinkContact(Contact* contact) {
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
