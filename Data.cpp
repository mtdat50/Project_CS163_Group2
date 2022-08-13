#include "Data.h"


UIPage mainMenuPage,
       viewDataPage,
       quizzPage;

bool displayingMainList,
    displayingSearchHistory,
    displayingFavoriteList;

int curPage;
int curDataSetIndex;


vector< dataSet > dataSetList;
vector< dataSet > archivedData;

int quizzChoices[4];
int quizzAnswer;