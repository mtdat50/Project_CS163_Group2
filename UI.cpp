#include "UI.h"

void createMainMenu() {
    mainMenuPage.clear();

    vector< label > &bList = mainMenuPage.buttonList;
    rollList &viewList = mainMenuPage.viewList;

    bList.push_back(label("Create a new data set", 25, 2, 15, 0));
    mainMenuPage.curButton = 0;

    bList.push_back(label("Reverse changes", 61, 2, 15, 0));
    bList.push_back(label("Exit", 92, 2, 15, 0));


    viewList.x = 55;
    viewList.y = 9;
    viewList.width = ConsoleWidth - viewList.x + 1;
    viewList.nItemsPerPage = 10;
    viewList.highlightedBGColor = 2;
    viewList.textColor = 15;

    for (dataSet s : dataSetList)
        viewList.buttonList.push_back(s.name);
}


void createViewDataPage() {
    viewDataPage.clear();
    dataSet &curDataSet = dataSetList[curDataSetIndex];

    vector< label > &bList = viewDataPage.buttonList;
    vector< label > &lList = viewDataPage.labelList;
    rollList &viewList = viewDataPage.viewList;
    viewDataPage.highlightedBGColor = 2;

    lList.push_back(label(curDataSet.name, (ConsoleWidth - curDataSet.name.size()) / 2 - 5, 1, 15, 11));

    bList.push_back(label("Add a word", 3, 3, 15, 0));
    viewDataPage.curButton = 0;
    bList.push_back(label("Search by word", 20, 3, 15, 0));
    bList.push_back(label("Search by definition", 41, 3, 15, 0));
    bList.push_back(label("Search history", 68, 3, 15, 0));
    bList.push_back(label("Favorite list", 89, 3, 15, 0));
    bList.push_back(label("Quizz", 109, 3, 15, 0));
    bList.push_back(label("Return", 120, 3, 15, 0));


    viewList.x = 6;
    viewList.labelx = 25;
    viewList.y = 9;
    viewList.width = ConsoleWidth - viewList.x;
    viewList.nItemsPerPage = 10;
    viewList.highlightedBGColor = 2;
    viewList.textColor = 15;

    for (pair< string, string > word : curDataSet.wordList) {
        viewList.buttonList.push_back(word.first);
        viewList.labelList.push_back(word.second);
    }
    displayingMainList = true;
    displayingSearchHistory = false;
    displayingFavoriteList = false;
}


void createQuizzPage() {
    quizzPage.clear();

    vector< label > &bList = quizzPage.buttonList;

    bList.push_back(label("Word quizz", 25, 2, 15, 0));
    quizzPage.curButton = 0;

    bList.push_back(label("Definition quizz", 61, 2, 15, 0));
    bList.push_back(label("Return", 92, 2, 15, 0));

    rollList &viewList = quizzPage.viewList;

    viewList.x = 40;
    viewList.y = 15;
    viewList.width = ConsoleWidth - viewList.x;
    viewList.nItemsPerPage = 4;
    viewList.highlightedBGColor = 2;
    viewList.textColor = 15;
}




void drawMainMenu() {
    setBTColor(1, 7, 15, 0);
    for (int i = 1; i < ConsoleWidth - 1; ++i)
        cout << '_';
    
    if (mainMenuPage.viewList.buttonList.empty()) {
        setBTColor(50, 9, 11, 0);
        cout << "There is no data.";
    }
    mainMenuPage.draw();
}

void drawViewDataPage() {
    setBTColor(1, 7, 15, 0);
    for (int i = 1; i < ConsoleWidth - 1; ++i)
        cout << '_';

    if (viewDataPage.viewList.buttonList.empty()) {
        setBTColor(50, 9, 11, 0);
        cout << "There is no data.";
    }
    else {
        for (int i = viewDataPage.viewList.y; i < ConsoleHeight - 1; ++i) {
            setBTColor(viewDataPage.viewList.x + viewDataPage.viewList.labelx - 2, i, 9, 0);
            cout << '|';
        }
    }
    viewDataPage.draw();
}

void drawQuizzPage() {
    setBTColor(1, 7, 15, 0);
    for (int i = 1; i < ConsoleWidth - 1; ++i)
        cout << '_';
    

    if (dataSetList[curDataSetIndex].wordList.size() < 4) {
        setBTColor(50, 9, 11, 0);
        cout << "There is not enough data.";
    }
    quizzPage.draw();
}



void updateUI() {
    clrscr();

    switch (curPage)
    {
    case MAIN_MENU_PAGE:
        createMainMenu();
        drawMainMenu();
        break;
    
    case VIEW_DATA_PAGE:
        createViewDataPage();
        drawViewDataPage();
        break;

    case QUIZZ_PAGE:
        createQuizzPage();
        drawQuizzPage();
        break;
    }
}
