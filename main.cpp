#include "Console.h"
#include "Event.h"
#include "Data.h"
using namespace std;


int main() {
    
    SetWindowSize(ConsoleWidth, ConsoleHeight);
    set_cursor(false);

    Events();
    return 0;
}