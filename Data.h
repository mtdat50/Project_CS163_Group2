#pragma once
#include <vector>
#include <string>

#include "UIStruct.h"
#include "Trie.h"

using namespace std;

struct dataSet {
    string name;
    trie wordTrie, defTrie;
    vector< pair< string, string > > wordList, searchHistory, favoriteList;

    dataSet() = default;
};



const int ConsoleWidth = 130,
          ConsoleHeight = 40;

const int MAIN_MENU_PAGE = 1,
          VIEW_DATA_PAGE = 2;

extern UIPage mainMenuPage,
              viewDataPage,
              quizPage;

extern bool displayingMainList,// used for VIEW_DATA_PAGE
            displayingSearchHistory,
            displayingFavoriteList;


extern int curPage;
extern int curDataSetIndex;


extern vector< dataSet > dataSetList;
extern vector< dataSet > archivedData;