#include "UIPageInteraction.h"



void mainMenuInteraction(WORD action) {
    // clrscr();
    clearLine(45, 4, ConsoleWidth, 0);
    clearLine(45, 5, ConsoleWidth, 0);


    if (VK_LEFT <= action && action <= VK_DOWN || action == VK_TAB)
        mainMenuPage.move(action);


    if (action == VK_RETURN) {
        if (!mainMenuPage.focusOnViewList) {
            string text = mainMenuPage.buttonList[mainMenuPage.curButton].text;

            if (text == "Exit")
                exit(0);


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
                vector< pair< string, string > > data;
                bool validData = loadNewDataSet(filepath, data);
                
                if (!validData) {
                    setBTColor(45, 5, 15, 0);
                    cout << "Data is invalid.";
                }
                else { // data is valid
                    clearLine(45, 4, ConsoleWidth, 0);
                    setBTColor(45, 4, 15, 2);
                    cout << "Data set name:";
                    
                    string dataSetName;
                    do { // input data set name
                        clearLine(56, 4, ConsoleWidth, 0);
                        setBTColor(56, 4, 15, 0);

                        char ch;
                        while ((ch = cin.get()) != '\n')
                            dataSetName += ch;
                    } while (dataSetName == "");

                    dataSetListA.push_back({dataSetName, trie()});
                    buildTrie(data, dataSetListA.back().second, 'A');

                    dataSetListB.push_back({dataSetName, trie()});
                    buildTrie(data, dataSetListB.back().second, 'B');

                    
                    setBTColor(45, 5, 15, 0);
                    cout << "New data set created successfully.";
                }
            }


        }
    }
    

    drawMainMenu();
}