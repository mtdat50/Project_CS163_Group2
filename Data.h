#pragma once
#include <vector>
#include <string>

#include "UIStruct.h"
#include "Trie.h"

const int ConsoleWidth = 130,
          ConsoleHeight = 40;

const int MAIN_MENU_PAGE = 1,
          DATA_SET_PAGE = 2,
          FAVOURITE_LIST_PAGE = 3,
          SEARCH_HISTORY_PAGE = 4;

extern UIPage mainMenuPage,
       datasetPage,
       favouriteListPage,
       searchHistoryPage;

extern int curPage;


extern vector< pair< string, trie > > dataSetListA, dataSetListB; // A = word - def/ B = def - word