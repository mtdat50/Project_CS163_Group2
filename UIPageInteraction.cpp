#include "UIPageInteraction.h"



void mainMenuInteraction(WORD action) {
    clearLine(45, 4, ConsoleWidth, 0);
    clearLine(45, 5, ConsoleWidth, 0);


    if (VK_LEFT <= action && action <= VK_DOWN || action == VK_TAB) {
        mainMenuPage.move(action);
        if (mainMenuPage.focusOnViewList && (action == VK_LEFT || action == VK_RIGHT))
            for (int i = mainMenuPage.viewList.y; i < ConsoleHeight - 1; ++i)
                clearLine(0, i, ConsoleWidth, 0);
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
                dataSetList.push_back(dataSet());

                vector< pair< string, string > > &wordList = dataSetList.back().wordList;
                loadNewDataSet(filepath, wordList); //load file

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
    if (!viewDataPage.focusOnViewList)
        clearLine(0, 4, ConsoleWidth, 0);

    if (VK_LEFT <= action && action <= VK_DOWN || action == VK_TAB) {
        viewDataPage.move(action);

        if (viewDataPage.focusOnViewList && (action == VK_LEFT || action == VK_RIGHT))
            for (int i = viewDataPage.viewList.y; i < ConsoleHeight - 1; ++i)
                clearLine(0, i, ConsoleWidth, 0);

        drawViewDataPage();
        
    }
    else if (action == VK_RETURN && !viewDataPage.focusOnViewList) {
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
                viewDataPage.focusOnViewList = true;
                
                for (int i = viewDataPage.viewList.y; i < ConsoleHeight - 1; ++i)
                    clearLine(0, i, ConsoleWidth, 0);
                viewDataPage.draw();
            }

            setBTColor(3, 3, 15, 2);
            cout << "Add a word";
        }
        else if (text == "Search by word") {
            setBTColor(20, 4, 15, 0);
            set_cursor(true);

            string word; // input word
            char ch;
            while ((ch = cin.get()) != '\n')
                word += ch;

            set_cursor(false);

            if (word == "") {
                clearLine(0, 4, ConsoleWidth, 0);
                setBTColor(20, 5, 15, 0);
                cout << "Searching cancelled";
            }
            else {
                vector< pair< string, string > > searchResult;
                dataSetList[curDataSetIndex].wordTrie.prefixSearch(word, searchResult);

                viewDataPage.viewList.buttonList.clear();
                viewDataPage.viewList.labelList.clear();
                for (pair< string, string > w : searchResult) {
                    viewDataPage.viewList.buttonList.push_back(w.first);
                    viewDataPage.viewList.labelList.push_back(w.second);
                }

                if (viewDataPage.viewList.buttonList.empty())
                    viewDataPage.viewList.curItem = -1;
                else {
                    viewDataPage.focusOnViewList = true;
                    viewDataPage.viewList.curItem = 0;
                }
                

                for (int i = viewDataPage.viewList.y; i < ConsoleHeight - 1; ++i)
                    clearLine(0, i, ConsoleWidth, 0);

                displayingMainList = false;
                drawViewDataPage();
                
            }

        }
        else if (text == "Search by definition") {
            setBTColor(41, 4, 15, 0);
            set_cursor(true);

            string def; // input word
            char ch;
            while ((ch = cin.get()) != '\n')
                def += ch;

            set_cursor(false);

            if (def == "") {
                clearLine(0, 4, ConsoleWidth, 0);
                setBTColor(41, 5, 15, 0);
                cout << "Searching cancelled";
            }
            else {
                vector< pair< string, string > > searchResult;
                dataSetList[curDataSetIndex].defTrie.prefixSearch(def, searchResult);

                viewDataPage.viewList.buttonList.clear();
                viewDataPage.viewList.labelList.clear();
                for (pair< string, string > w : searchResult) {
                    viewDataPage.viewList.buttonList.push_back(w.second);
                    viewDataPage.viewList.labelList.push_back(w.first);
                }

                if (viewDataPage.viewList.buttonList.empty())
                    viewDataPage.viewList.curItem = -1;
                else {
                    viewDataPage.focusOnViewList = true;
                    viewDataPage.viewList.curItem = 0;
                }
                

                for (int i = viewDataPage.viewList.y; i < ConsoleHeight - 1; ++i)
                    clearLine(0, i, ConsoleWidth, 0);

                displayingMainList = false;
                drawViewDataPage();
                
            }

        }


    }
    else if (action == VK_RETURN && viewDataPage.focusOnViewList) {
        //edit a definition
            //not done
    }
    else if (action == VK_ESCAPE && !displayingMainList) { // return back to the main words list
        viewDataPage.viewList.buttonList.clear();
        viewDataPage.viewList.labelList.clear();
        
        for (pair< string, string > word : dataSetList[curDataSetIndex].wordList) {
            viewDataPage.viewList.buttonList.push_back(word.first);
            viewDataPage.viewList.labelList.push_back(word.second);
        }

        if (viewDataPage.viewList.buttonList.empty())
            viewDataPage.viewList.curItem = -1;
        else 
            viewDataPage.viewList.curItem = 0;

        displayingMainList = true;

        clearLine(0, 4, ConsoleWidth, 0);
        for (int i = viewDataPage.viewList.y; i < ConsoleHeight - 1; ++i)
            clearLine(0, i, ConsoleWidth, 0);
        drawViewDataPage();
    }
}


