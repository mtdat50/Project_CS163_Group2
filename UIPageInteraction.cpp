#include "UIPageInteraction.h"



void mainMenuInteraction(WORD action) {
    clearLine(45, 4, ConsoleWidth, 0);
    clearLine(45, 5, ConsoleWidth, 0);


    if (VK_LEFT <= action && action <= VK_DOWN || action == VK_TAB) {
        mainMenuPage.move(action);
        drawMainMenu();

    }
    else if (action == VK_RETURN) { // pressing enter
        if (mainMenuPage.focusOnViewList) { // selecting an data set
            curDataSet = mainMenuPage.viewList.curItem;
            curPage = VIEW_DATA_PAGE;
            updateUI();

        }
        else { // option row
            string text = mainMenuPage.buttonList[mainMenuPage.curButton].text;

            if (text == "Exit")
                exit(0);

            // create new data set
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
                mainMenuPage.viewList.buttonList.push_back(dataSetName);
                mainMenuPage.viewList.curItem = mainMenuPage.viewList.buttonList.size() - 1;

                
                clrscr();
                setBTColor(45, 5, 15, 0);
                cout << "New data set created successfully.";
            }

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