#include "UIStruct.h"

label::label() {
    text = "";
    x = 0;
    y = 0;
    color = 0;
    bgcolor = 0;
}


label::label(string _text, int _x, int _y, int _color, int _bgcolor) {
    text = _text;
    x = _x;
    y = _y;
    color = _color;
    bgcolor = _bgcolor;
}


void label::draw() {
    setBTColor(x, y, color, bgcolor);
    cout << text;
}


// ==========================================================================

rollList::rollList() {
    origin = x = y = width = height = 0;
    curButton = nullptr;
}


// ==========================================================================

GUIPage::GUIPage() {
    curButton = nullptr;
    highlightedBGColor = 2;
}


void GUIPage::draw() {
    for (label x : buttonList)
        x.draw();
        
    for (label x : labelList)
        x.draw();

    // viewList.draw(highlightedBGColor);

    SetBGColor(0);
    //preventing wrong color bug on the console screen
}


void GUIPage::move(WORD step) {
    if (buttonList.empty()) return;

    curButton->bgcolor = 0;


    int newIndex;
    if (step == VK_DOWN && step == VK_RIGHT)
        newIndex = (curButton - &buttonList[0] + 1) % buttonList.size();
    else if (step == VK_UP && step == VK_LEFT)
        newIndex = (curButton - &buttonList[0] - 1 + buttonList.size()) % buttonList.size();

    curButton = &buttonList[newIndex];


    curButton->bgcolor = highlightedBGColor;
    draw();
}


void GUIPage::clear() {
    buttonList.clear();
    labelList.clear();
}
