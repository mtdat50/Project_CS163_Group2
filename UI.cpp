#include "UI.h"

void createMainMenu() {
    mainMenuPage.clear();

    vector< label > &bList = mainMenuPage.buttonList;
    rollList &viewList = mainMenuPage.viewList;

    bList.push_back(label("Create a new data set", 45, 2, 15, 2));
    mainMenuPage.curButton = 0;

    bList.push_back(label("Exit", 85, 2, 15, 0));


    viewList.x = 50;
    viewList.y = 9;
    viewList.nItemsPerPage = 10;
    viewList.highlightedBGColor = 2;
    viewList.textColor = 11;

    for (pair< string, trie > s : dataset)
        viewList.buttonList.push_back(s.first);
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



void updateUI() {
    clrscr();

    switch (curPage)
    {
    case MAIN_MENU_PAGE:
        createMainMenu();
        drawMainMenu();
        break;
    
    }
}