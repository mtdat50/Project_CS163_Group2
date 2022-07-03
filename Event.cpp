#include "Event.h"


void Controller(KEY_EVENT_RECORD key) {

    // if(key.bKeyDown)//if the keys is pressed
    // {
    //     switch (key.wVirtualKeyCode) // which key is pressed
    //     {
    //         case VK_UP://when pressed arrow up
    //         break;


    //         case VK_DOWN:
    //         break;
            
    //         case VK_RETURN:
    //         break;

    //         case VK_ESCAPE:
    //         break;
    //     }
    // }
}

void Events() {
    while(true) {
        DWORD eventsNumber = 0;
        DWORD readEventsNumber = 0;

        HANDLE ConsoleInput=GetStdHandle(STD_INPUT_HANDLE);
        GetNumberOfConsoleInputEvents(ConsoleInput, &eventsNumber);

        if(eventsNumber) {
            INPUT_RECORD *IREventBuffer = new INPUT_RECORD[eventsNumber];
            ReadConsoleInput(ConsoleInput, IREventBuffer, eventsNumber, &readEventsNumber);

            for(DWORD i = 0; i < eventsNumber; ++i)
                if (IREventBuffer[i].EventType == KEY_EVENT)
                    Controller(IREventBuffer[i].Event.KeyEvent);
        }
    }
}

