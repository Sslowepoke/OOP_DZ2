#include <list>
using std::list;

template <typename T> class List {
private:
    class Node {
    public:
        Node(char key, T value) : key(charToIndex(key)), value(value) {}
        Node(char key) : key(charToIndex(key)) {} 

        char key;
        T value;
    };

    list<Node> nodes;

    static char charToIndex(char c){
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

public:

    T& operator[](const char key){
        char index = charToIndex(key);
        for(auto& temp: nodes) {
            if(temp.key == index) {
                return temp.value;
            }
        }
        throw std::out_of_range("List index out of range");
    }

    void insert(const char key, const T& value) {
        insert(key).value = value;
    }

    Node& insert(const char key) {
        char index = charToIndex(key);
        for(auto it = nodes.begin(); it != nodes.end(); it++) {
            if((*it).key <= index) {
                return *nodes.emplace(it, key);
            }
        }
        return nodes.emplace_back(key);
    }

    void remove(const char key) {
        char index = charToIndex(key);
        for(auto it = nodes.begin(); it != nodes.end(); it++) {
            if((*it).key == index) {
                it = nodes.erase(it);
                it--;
            }
        }
    }

    bool has(const char key) const{
        char index = charToIndex(key);
        if(nodes.empty()) return false;
        for(auto temp : nodes) {
            if(temp.key == index) {
                return true;
            }
        }
        return false;
    }

    void pushToStack(std::stack<T>& s) const{
        if(nodes.empty()) return;
        for(auto node : nodes) {
            s.push(node.value);
        }
    }

    bool empty() const{
        return nodes.empty();
    }
};
