#include <string>
#include <functional>
using namespace std;

struct node
{

    node *child[256];
    string definition;

    node();
};

struct trie
{
    node *root;

    trie();
    
    node *travel(string word);
    void insert(string word, string definition);
    void erase(string word);
    string search(string word);


    ~trie();
};
