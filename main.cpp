#include "Console.h"
#include "Event.h"
#include "Data.h"
#include "UI.h"
using namespace std;


int main() {
    
    SetWindowSize(ConsoleWidth, ConsoleHeight);
    set_cursor(false);

    createMainMenu();
    drawMainMenu();
    curPage = MAIN_MENU_PAGE;

    Events();
    return 0;
}