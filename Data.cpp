#include "Data.h"


UIPage mainMenuPage,
       favoritePage,
       searchHistoryPage,
       quizPage;

// UIDataSetPage datasetPage;

int curPage;
int curDataSet;


vector< pair< string, trie > > dataSetListA, dataSetListB; // < name, data >