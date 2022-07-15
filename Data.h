#include "UIStruct.h"

const int ConsoleWidth = 200,
          ConsoleHeight = 100;

UIPage mainMenuPage,
       datasetPage,
       favouritePage,
       searchHistoryPage;

UIPage *curPage = nullptr;