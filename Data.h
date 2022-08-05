#pragma once
#include <vector>
#include <string>

#include "UIStruct.h"
#include "Trie.h"

struct dataSet {
    string name;
    trie wordTrie, defTrie;
    vector< pair< string, string > > wordList;

    dataSet() = default;
};



const int ConsoleWidth = 130,
          ConsoleHeight = 40;

const int MAIN_MENU_PAGE = 1,
          VIEW_DATA_PAGE = 2,
          FAVORITE_LIST_PAGE = 3,
          SEARCH_HISTORY_PAGE = 4;

extern UIPage mainMenuPage,
              viewDataPage,
              favoriteListPage,
              searchHistoryPage,
              quizPage;


extern int curPage;
extern int curDataSetIndex;


extern vector< dataSet > dataSetList;