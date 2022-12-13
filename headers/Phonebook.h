#include <string>
using std::string;

#include "Trie.h"
#include "Contact.h"

class Phonebook {
public:
    
    static Phonebook& getInstance();
    //official requirements
    void Phonebook::openTerminal();
    void Phonebook::loadPhonebook(const string& filepath);


private:
    Phonebook();
    Trie tree;

    //empties phonebook (deletes all data)
    void empty();
    
};