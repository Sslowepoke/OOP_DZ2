#include "Node.h"
#include <stack>

std::ostream& operator<<(std::ostream& os, const Node& node){
    os << (*node.contact);
    return os;
}

std::ostream& operator<<(std::ostream& os, Node* start) {
    if(start == nullptr) return os;
    if(start->is_terminal) os << (*start);
    for(char c = 0; c < 256; c++) {
        if(start->children[c]!=nullptr) os << start->children[c];
    }
}

bool Node::hasChildren() {
    for(Node* ptr : children) {
        if(ptr != nullptr) return true;
    }
    return false;
}