#include <iostream>

#include "Console.h"
#include "Event.h"
#include "Data.h"
#include "UI.h"
using namespace std;


int main() {
    
    SetWindowSize(ConsoleWidth, ConsoleHeight);
    set_cursor(false);

    setBTColor(ConsoleWidth / 2 - 7, ConsoleHeight / 2 - 5, 15, 0);
    cout << "Loading...";
    loadData();
    
    curPage = MAIN_MENU_PAGE;
    updateUI();

    Events();
    return 0;
}