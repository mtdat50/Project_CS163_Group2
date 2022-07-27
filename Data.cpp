#include "Data.h"


UIPage mainMenuPage,
       favoritePage,
       searchHistoryPage,
       quizPage;

UIDataSetPage datasetPage;

int curPage;


vector< pair< string, trie > > dataSetListA, dataSetListB; // < name, data >