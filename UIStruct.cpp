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
    nItemsPerPage = x = y = labelx = 0;
    highlightedBGColor = 2;
    curItem = -1;
}

void rollList::clear() {
    buttonList.clear();
    labelList.clear();
    rollList();
}


void rollList::move(WORD step) {
        
    int n = buttonList.size(),
        curPage = curItem / nItemsPerPage,
        indexInCurPage = curItem % nItemsPerPage;

    switch (step) {
    case VK_DOWN:
        if (indexInCurPage == nItemsPerPage - 1 || curItem == n - 1)
            curItem -= indexInCurPage;
        else
            ++curItem;
        break;

    case VK_UP:
        if (indexInCurPage == 0)
            curItem = min(curItem + nItemsPerPage - 1, n - 1);
        else
            --curItem;
        break;

    case VK_RIGHT:
        if (curPage == (n - 1) / nItemsPerPage)
            curItem = 0;
        else
            curItem += -indexInCurPage + nItemsPerPage;
        break;

    case VK_LEFT:
        if (curPage == 0)
            curItem = n - 1 - n % nItemsPerPage;
        else
            curItem += -indexInCurPage - nItemsPerPage;
        break;
    }

}


void rollList::draw() {
    int n = buttonList.size(),
        curPage = curItem / nItemsPerPage,
        indexInCurPage = curItem % nItemsPerPage;

    int begin = curItem - indexInCurPage;
    int end = min(begin + nItemsPerPage, n);

    for (int i = begin; i < end; ++i) {
        int item_y = y + (i - begin) * 3;
        int color = 15, bgcolor = 0;

        if (i == curItem) bgcolor = highlightedBGColor;

        setBTColor(x, item_y, color, bgcolor);
        cout << buttonList[i];

        if (!labelList.empty()) {
            if (labelList[i].size() <= 100) {
                setBTColor(x, item_y, color, bgcolor);
                cout << labelList[i];
            }
            else {
                string s = labelList[i].substr(0, 100);

                setBTColor(x, item_y, color, bgcolor);
                cout << s;

                s = labelList[i].substr(100, labelList[i].size() - 100);
                setBTColor(x, item_y + 1, color, bgcolor);
                cout << s;
            }
        }
    }
}


// ==========================================================================

UIPage::UIPage() {
    focusOnViewList = false;
    curButton = nullptr;
    highlightedBGColor = 2;
}


void UIPage::draw() {
    for (label x : buttonList)
        x.draw();
        
    for (label x : labelList)
        x.draw();

    viewList.draw();

    SetBGColor(0);
    //preventing wrong color bug on the console screen after using clrsr
}


void UIPage::move(WORD step) {
    if (step == VK_TAB) { // switching between main page and viewList
        if (!curButton || viewList.curItem == -1)
            return;

        if (focusOnViewList) {
            curButton->bgcolor = highlightedBGColor;
            focusOnViewList = false;
        }
        else {
            curButton->bgcolor = 0;
            focusOnViewList = true;
        }
    }
    else if (focusOnViewList) { // moving in viewList
        if (viewList.buttonList.empty() && viewList.labelList.empty())
            return;

        viewList.move(step);
    }
    else { // moving in main page
        if (buttonList.empty())
            return;

        curButton->bgcolor = 0;

        int n = buttonList.size(),
            curIndex = curButton - &buttonList[0],
            newIndex;
        if (step == VK_DOWN && step == VK_RIGHT)
            newIndex = (curIndex + 1) % n;
        else if (step == VK_UP && step == VK_LEFT)
            newIndex = (curIndex - 1 + n) % n;

        curButton = &buttonList[newIndex];
        curButton->bgcolor = highlightedBGColor;
    }


    draw();
}


void UIPage::clear() {
    buttonList.clear();
    labelList.clear();
    viewList.clear();
    UIPage();
}
