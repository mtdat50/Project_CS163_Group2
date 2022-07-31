#include "Functions.h"


bool loadNewDataSet(string filepath, vector< pair < string, string > > &data) {
    // if (!filesystem::exists(filepath))
    //     return false;

    // ifstream fin (filepath);
    // string s;
    // while (!fin.eof())
    // {
    //     getline(fin, s);
    //     stringstream str(s);
    //     string w, def;
    //     getline(str, w, ' ');
    //     getline(str, def);
    //     data.push_back({ w, def });
    // }

    return true; // not done
}

void buildTrie(vector< pair < string, string > > &data, trie &dataSet, char type = 'A') {
    // for(int i = 0; i < data.size(); ++i)
    // {
    //     if (type == 'A')
    //     {
    //         dataSet.insert(data[i].first, data[i].second);
    //     }
    //     else
    //     {
    //         dataSet.insert(data[i].second, data[i].first);
    //     }
    // }
}