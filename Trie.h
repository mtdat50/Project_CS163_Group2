#pragma once

#include <string>
#include <functional>
#include <vector>
using namespace std;

struct node
{
    node *child[128];
    string definition;

    node();
    ~node();
};

struct trie
{
    node *root;

    trie();

    node *travel(string word);
    void insert(string word, string definition);
    void erase(string word);
    string search(string word);
    void prefixSearch(string prefix, vector< pair< string, string > > &result);
    void cleanMemory();
};
