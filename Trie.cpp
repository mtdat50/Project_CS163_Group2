#include "Trie.h"

node::node() {
    fill(child, child + 256, nullptr);
    definition = "";
}

node::~node() {
    for (int i = 0; i < 256; ++i) 
        delete child[i];
}

// ==========================================================================

trie::trie() {
    root = new node;
}

node *trie::travel(string word) {
    node *cur = root;
    
    for (char c : word) {
        cur = cur->child[c];

        if (!cur) break;
    }

    return cur;
}


void trie::insert(string word, string definition) {
    node *cur = root;
    
    for (char c : word) {
        node *&nxt = cur->child[c];

        if (!nxt)
            nxt = new node;
        
        cur = nxt;
    }

    cur->definition = definition;
}

string trie::search(string word) {
    node *cur = travel(word);

    if (cur) return cur->definition;
    return "";
}


void trie::erase(string word) {
    node *cur = travel(word);

    if (cur) cur->definition = "";
}


void trie::cleanMemory() {
    function< int(node *) > clean = [&](node *cur) -> int {
        if (!cur) return 0;

        int words = root->definition != "";
        for (int i = 0; i < 256; ++i)
            words += clean(cur->child[i]);
        
        if (words == 0) delete cur;
        return words;
    };

    clean(root);
}