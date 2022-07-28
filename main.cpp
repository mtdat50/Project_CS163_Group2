#include "Console.h"
#include "Event.h"
#include "Data.h"
#include "UI.h"
using namespace std;


int main() {
    
    SetWindowSize(ConsoleWidth, ConsoleHeight);
    set_cursor(false);

    curPage = MAIN_MENU_PAGE;
    updateUI();

    Events();
    return 0;
}