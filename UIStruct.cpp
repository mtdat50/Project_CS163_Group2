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
    nItemsPerPage = x = y = width = labelx = 0;
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
            curItem = n - (n % nItemsPerPage);
        else
            curItem += -indexInCurPage - nItemsPerPage;
        break;
    }

}


void rollList::draw(bool focusOn) {
    int n = buttonList.size(),
        curPage = curItem / nItemsPerPage,
        indexInCurPage = curItem % nItemsPerPage;

    int begin = curItem - indexInCurPage;
    int end = min(begin + nItemsPerPage, n);

    for (int i = begin; i < end; ++i) {
        int item_y = y + (i - begin) * 3;
        int color = textColor, bgcolor = 0;

        if (i == curItem && focusOn) bgcolor = highlightedBGColor;

        setBTColor(x, item_y, color, bgcolor);
        cout << buttonList[i];

        if (!labelList.empty()) {
            size_t labelwidth = width - labelx;

            for (int j = 0; j * labelwidth < labelList[i].size(); ++j) {
                setBTColor(x + labelx, item_y + j, color, bgcolor);
                cout << labelList[i].substr(j * labelwidth, min(labelwidth, labelList[i].size() - j * labelwidth));
            }
        }

    }
}


// ==========================================================================

UIPage::UIPage() {
    focusOnViewList = false;
    curButton = -1;
    highlightedBGColor = 2;
}

/*
UIDataSetPage::UIDataSetPage() {
    focusOnViewList = false;
    curButton = -1;
    highlightedBGColor = 2;
}
*/

void UIPage::draw() {
    for (int i = 0; i < (int) buttonList.size(); ++i) {
        label x = buttonList[i];
        if (!focusOnViewList && i == curButton)
            x.bgcolor = highlightedBGColor;
        else
            x.bgcolor = 0;
        
        x.draw();
    }
        
    for (label x : labelList)
        x.draw();

    viewList.draw(focusOnViewList);

    SetBGColor(0);
    //preventing wrong color bug on the console screen after using clrsr
}


void UIPage::move(WORD step) {
    if (step == VK_TAB) { // switching between main page and viewList
        if (buttonList.empty() || (viewList.buttonList.empty() && viewList.labelList.empty()))
            return;
        
        if (curButton == -1) curButton = 0;
        if (viewList.curItem == -1) viewList.curItem = 0;

        if (focusOnViewList) {
            buttonList[curButton].bgcolor = highlightedBGColor;
            focusOnViewList = false;
        }
        else {
            buttonList[curButton].bgcolor = 0;
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

        buttonList[curButton].bgcolor = 0;

        int n = buttonList.size(), newIndex;
        if (step == VK_DOWN || step == VK_RIGHT)
            newIndex = (curButton + 1) % n;
        else if (step == VK_UP || step == VK_LEFT)
            newIndex = (curButton - 1 + n) % n;

        curButton = newIndex;
        buttonList[curButton].bgcolor = highlightedBGColor;
    }
}


void UIPage::clear() {
    buttonList.clear();
    labelList.clear();
    viewList.clear();
    UIPage();
}
