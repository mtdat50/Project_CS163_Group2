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
    int x, y, labelx;
    int nItemsPerPage;
    int highlightedBGColor;
    vector< string > buttonList;
    vector< string > labelList;
    int curItem;

    rollList();

    void move(WORD step);
    void draw();
    void clear();
};


struct UIPage {
    vector< label > buttonList;
    vector< label > labelList;
    rollList viewList;

    bool focusOnViewList;
    label *curButton;
    int highlightedBGColor;

    UIPage();

    void draw();
    void move(WORD step);
    void clear();
};
