#include "Data.h"


UIPage mainMenuPage,
       datasetPage,
       favouritePage,
       searchHistoryPage;

int curPage;


vector< pair< string, trie > > dataset; // < name, data >