#include "Functions.h"


void loadNewDataSet(string filepath, vector< pair < string, string > > &data) {
    ifstream fin (filepath);
    bool ok = true;
    
    while (!fin.eof()) {
        string word, def;

        getline(fin, word);

        int cnt = count(word.begin(), word.end(), (char) 9); // count 'tab' character
        if (cnt != 1) continue;

        int tabIndex = word.find((char) 9);
        def = word.substr(tabIndex + 1, word.size() - tabIndex - 1);
        word = word.substr(0, tabIndex);
        data.push_back({word, def});
    }

    fin.close();
}

void buildTrie(vector< pair < string, string > > &data, trie &dataSet, char type = 'A') {
    for(pair< string, string > item : data)
        if (type == 'A')
            dataSet.insert(item.first, item.second);
        else
            dataSet.insert(item.second, item.first);
}