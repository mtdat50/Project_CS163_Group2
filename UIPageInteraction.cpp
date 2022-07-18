#include "UIPageInteraction.h"



void mainMenuInteraction(WORD action) {
    // clrscr();

    if (VK_LEFT <= action && action <= VK_DOWN)
        mainMenuPage.move(action);

    drawMainMenu();
}