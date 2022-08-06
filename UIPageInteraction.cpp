#include "UIPageInteraction.h"



void mainMenuInteraction(WORD action) {
    clearLine(45, 4, ConsoleWidth, 0);
    clearLine(45, 5, ConsoleWidth, 0);


    if (VK_LEFT <= action && action <= VK_DOWN || action == VK_TAB) {
        if (mainMenuPage.focusOnViewList && (action == VK_LEFT || action == VK_RIGHT))
            for (int i = mainMenuPage.viewList.y; i < ConsoleHeight - 1; ++i)
                clearLine(0, i, ConsoleWidth, 0);
        mainMenuPage.move(action);
        drawMainMenu();

    }
    else if (action == VK_RETURN) { // pressing enter
        if (mainMenuPage.focusOnViewList) { // selecting an data set
            curDataSetIndex = mainMenuPage.viewList.curItem;
            curPage = VIEW_DATA_PAGE;
            updateUI();

        }
        else { // option row
            string text = mainMenuPage.buttonList[mainMenuPage.curButton].text;

            if (text == "Exit")
                exit(0);

            // create new data set
            set_cursor(true);
            setBTColor(45, 2, 15, 0);
            cout << "Create a new data set";
            setBTColor(45, 4, 15, 2);
            cout << "File path:";
            setBTColor(45, 5, 15, 0);
            cout << "Enter an empty string to cancel.";

            string filepath;
            while (true) { // input filepath
                clearLine(56, 4, ConsoleWidth, 0);
                setBTColor(56, 4, 15, 0);

                char ch;
                filepath = "";
                while ((ch = cin.get()) != '\n')
                    filepath += ch;

                if (filepath == "" || filesystem::exists(filepath))
                    break;

                clearLine(45, 5, ConsoleWidth, 0);
                setBTColor(45, 5, 15, 0);
                cout << "File is not found. Please re-enter filepath or enter an empty string to cancel.";
            }

            clearLine(45, 4, ConsoleWidth, 0);
            clearLine(45, 5, ConsoleWidth, 0);
            if (filepath == "") {
                setBTColor(45, 5, 15, 0);
                cout << "Creating cancelled.";

            }
            else { // file exists
                dataSetList.push_back(dataSet()); // init new data set

                vector< pair< string, string > > &wordList = dataSetList.back().wordList;
                loadNewDataSet(filepath, wordList);

                buildTrie(wordList, dataSetList.back().wordTrie, 'A');
                buildTrie(wordList, dataSetList.back().defTrie, 'B');
                

                setBTColor(45, 4, 15, 2);
                cout << "Data set name:";
                
                string dataSetName;
                do { // input data set name
                    clearLine(60, 4, ConsoleWidth, 0);
                    setBTColor(60, 4, 15, 0);

                    char ch;
                    while ((ch = cin.get()) != '\n')
                        dataSetName += ch;
                } while (dataSetName == "");
                dataSetList.back().name = dataSetName;
                mainMenuPage.viewList.buttonList.push_back(dataSetName);

                
                clrscr();
                setBTColor(45, 5, 15, 0);
                cout << "New data set created successfully.";
            }

            set_cursor(false);
            drawMainMenu();
        }

    }
    else if (action == VK_DELETE && mainMenuPage.focusOnViewList) {
        auto buttonIt = mainMenuPage.viewList.buttonList.begin() + mainMenuPage.viewList.curItem;
        auto dataIt = dataSetList.begin() + mainMenuPage.viewList.curItem;

        mainMenuPage.viewList.buttonList.erase(buttonIt);
        dataSetList.erase(dataIt);

        clrscr();
        drawMainMenu();

    }


}



void viewDataInteraction(WORD action) {
    clearLine(0, 5, ConsoleWidth, 0);

    if (VK_LEFT <= action && action <= VK_DOWN || action == VK_TAB) {

        if (viewDataPage.focusOnViewList && (action == VK_LEFT || action == VK_RIGHT))
            for (int i = viewDataPage.viewList.y; i < ConsoleHeight - 1; ++i)
                clearLine(0, i, ConsoleWidth, 0);

        viewDataPage.move(action);
        drawViewDataPage();
        
    }
    else if (action == VK_RETURN) {
        string text = viewDataPage.buttonList[viewDataPage.curButton].text;

        if (text == "Return") {
            curPage = MAIN_MENU_PAGE;
            updateUI();

        }
        else if (text == "Add a word") {
            setBTColor(3, 3, 15, 0);
            cout << "Add a word";
            setBTColor(3, 4, 15, 2);
            cout << "Word:";
            setBTColor(3, 5, 15, 0);
            cout << "Definition:";

            setBTColor(9, 4, 15, 0);
            set_cursor(true);
            string word; // input word
            char ch;
            while ((ch = cin.get()) != '\n')
                word += ch;


            string def;
            if (word != "") { // input definition
                setBTColor(3, 4, 15, 0);
                cout << "Word:";
                setBTColor(3, 5, 15, 2);
                cout << "Definition:";
                
                setBTColor(15, 5, 15, 0);
                char ch;
                while ((ch = cin.get()) != '\n')
                    def += ch;
            }
            set_cursor(false);
            setBTColor(3, 3, 15, 2);
            cout << "Add a word";


            clearLine(0, 4, ConsoleWidth, 0);
            clearLine(0, 5, ConsoleWidth, 0);
            clearLine(0, 6, ConsoleWidth, 0);
            setBTColor(3, 5, 15, 0);
            if (def == "")
                cout << "Adding cancelled.";
            else {
                cout << "Adding successful.";

                dataSetList[curDataSetIndex].wordList.push_back({word, def});
                dataSetList[curDataSetIndex].wordTrie.insert(word, def);
                dataSetList[curDataSetIndex].defTrie.insert(def, word);

                viewDataPage.viewList.buttonList.push_back(word);
                viewDataPage.viewList.labelList.push_back(def);
                viewDataPage.viewList.curItem = viewDataPage.viewList.buttonList.size() - 1;

                
                for (int i = viewDataPage.viewList.y; i < ConsoleHeight - 1; ++i)
                    clearLine(0, i, ConsoleWidth, 0);
                viewDataPage.draw();
            }
        }


    }
}


