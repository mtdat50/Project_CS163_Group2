#include "Data.h"


UIPage mainMenuPage,
       favoritePage,
       searchHistoryPage,
       quizPage;

UIDataSetPage datasetPage;

int curPage;


vector< pair< string, trie > > dataset; // < name, data >