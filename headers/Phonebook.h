

#include "Trie.h"


class Phonebook {
public:
    static Phonebook& getInstance();


private:
    Phonebook();
    Trie tree;
    
};