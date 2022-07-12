#pragma once

#include <iostream>
#include <string>
#include <vector>

#include "Console.h"

using namespace std;


struct label {
    int x, y;
    int color, bgcolor;
    string text;

    label();

    label(string _text, int _x, int _y, int _color, int _bgcolor);

    void draw();
};


struct rollList {
    int x, y, width, height;
    int origin;
    vector< label > buttonList;
    vector< label > labelList;
    label *curButton;

    rollList();

    // void move();
    // void draw(int highlightedBGColor);
};


struct GUIPage {
    vector< label > buttonList;
    vector< label > labelList;
    rollList viewList;

    label *curButton;
    int highlightedBGColor;

    GUIPage();

    void draw();
    void move(WORD step);
    void clear();
};
