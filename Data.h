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
          VIEW_DATA_PAGE = 2,
          QUIZZ_PAGE = 3;

extern UIPage mainMenuPage,
              viewDataPage,
              quizzPage;

extern bool displayingMainList,// used for VIEW_DATA_PAGE
            displayingSearchHistory,
            displayingFavoriteList;


extern int curPage;
extern int curDataSetIndex;


extern vector< dataSet > dataSetList;
extern vector< dataSet > archivedData;

extern int quizzChoices[4];
extern int quizzAnswer;