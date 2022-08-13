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

 
/// =============================================================================
void saveTrie(ofstream &fout, node *root) {
    if (!root) return;

    fout << root->definition << '\n';
    for (int i = 0; i < 128; ++i)
        fout << int (root->child[i] != nullptr) << " \n"[i == 127];

    for (int i = 0; i < 128; ++i)
        saveTrie(fout, root->child[i]);
}

void saveADataSet(dataSet &curDataSet, int index) {
    string filepath = "Data/data" + to_string(index);
    filepath += ".temp";
    // string filepath = "data0.temp";

    mkdir("Data");
    ofstream fout(filepath);

    fout << curDataSet.name << '\n';
    saveTrie(fout, curDataSet.wordTrie.root);
    saveTrie(fout, curDataSet.defTrie.root);

    fout << curDataSet.searchHistory.size() << '\n';
    for (pair< string, string > p : curDataSet.searchHistory)
        fout << p.first << '\n' << p.second << '\n';

    fout << curDataSet.favoriteList.size() << '\n';
    for (pair< string, string > p : curDataSet.favoriteList)
        fout << p.first << '\n' << p.second << '\n';

    fout.close();
}

// void saveData() {
//     for (size_t i = 0; i < dataSetList.size(); ++i)
//         saveADataSet(dataSetList[curDataSetIndex], i);
// }



void loadTrie(ifstream & fin, node *root) {
    if (!root) return;

    getline(fin, root->definition);
    for (int i = 0; i < 128; ++i) {
        bool exist;
        fin >> exist;

        if (exist) root->child[i] = new node;
    }
    fin.ignore();

    for (int i = 0; i < 128; ++i)
        loadTrie(fin, root->child[i]);
}


void loadData() {
    dataSetList.clear();

    for (size_t i = 0; ; ++i) {
        string filename = "Data/data" + to_string(i);
        string filepath = filename + ".txt",
            filepath_temp = filename + ".temp";


        if (filesystem::exists(filepath_temp)) {
            filesystem::remove(filepath);
            filesystem::rename(filepath_temp, filepath);
        }
        if (!filesystem::exists(filepath)) break; // check stopping
        

        dataSetList.push_back(dataSet());
        dataSet &curDataSet = dataSetList.back();

        ifstream fin(filepath);

        fin >> curDataSet.name; fin.ignore();
        loadTrie(fin, curDataSet.wordTrie.root);
        loadTrie(fin, curDataSet.defTrie.root);

        curDataSet.wordTrie.prefixSearch("", curDataSet.wordList);

        int n;
        fin >> n; fin.ignore();
        for (size_t i = 0; i < n; ++i) {
            pair< string, string > p;
            
            getline(fin, p.first);
            getline(fin, p.second);
            curDataSet.searchHistory.push_back(p);
        }

        fin >> n; fin.ignore();
        for (size_t i = 0; i < n; ++i) {
            pair< string, string > p;
            
            getline(fin, p.first);
            getline(fin, p.second);
            curDataSet.favoriteList.push_back(p);
        }

        fin.close();
    }

    archivedData = dataSetList;
}

/// ==============================================================================
void deleteSaveFile(int index) {
    string filename = "Data/data" + to_string(index);
    string filepath = filename + ".txt",
        filepath_temp = filename + ".temp";

    filesystem::remove(filepath);
    filesystem::remove(filepath_temp);

    for (int i = index + 1; ; ++i) {
        string curName = "Data/data" + to_string(i);
        string curPath = curName + ".txt";
        string curPath_temp = curName + ".temp";

        if (!filesystem::exists(curPath) && !filesystem::exists(curPath_temp)) //stop
            break;
        
        string OldP = curPath,
            OldP_temp = curPath_temp;

        if (filesystem::exists(curPath))
            filesystem::rename(curPath, filepath);
        if (filesystem::exists(curPath_temp))
            filesystem::rename(curPath_temp, filepath_temp);

        filepath = OldP;
        filepath_temp = OldP_temp;
    }
}


void reverseChanges() {
    for (int i = dataSetList.size() - 1; i >= 0; --i)
        deleteSaveFile(i);
    
    dataSetList = archivedData;

    for (size_t i = 0; i < dataSetList.size(); ++i)
        saveADataSet(dataSetList[i], i);
}