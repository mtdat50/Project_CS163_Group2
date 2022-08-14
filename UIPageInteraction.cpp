#include "UIPageInteraction.h"


/// ==============================================================================================
/// ==============================================================================================

void addNewDataSet() {
    set_cursor(true);
    setBTColor(25, 2, 15, 0);
    cout << "Create a new data set";
    setBTColor(25, 4, 15, 2);
    cout << "File path:";
    setBTColor(25, 5, 15, 0);
    cout << "Enter an empty string to cancel.";

    string filepath;
    while (true) { // input filepath
        clearLine(36, 4, ConsoleWidth, 0);
        setBTColor(36, 4, 15, 0);

        char ch;
        filepath = "";
        while ((ch = cin.get()) != '\n')
            filepath += ch;

        if (filepath == "" || filesystem::exists(filepath))
            break;

        clearLine(25, 5, ConsoleWidth, 0);
        setBTColor(25, 5, 15, 0);
        cout << "File is not found. Please re-enter filepath or enter an empty string to cancel.";
    }

    clearLine(25, 4, ConsoleWidth, 0);
    clearLine(25, 5, ConsoleWidth, 0);
    if (filepath == "") {
        setBTColor(25, 5, 15, 0);
        cout << "Creating cancelled.";

    }
    else { // file exists
        dataSetList.push_back(dataSet());

        vector< pair< string, string > > &wordList = dataSetList.back().wordList;
        loadNewDataSet(filepath, wordList); //load file

        buildTrie(wordList, dataSetList.back().wordTrie, 'A');
        buildTrie(wordList, dataSetList.back().defTrie, 'B');
        
        wordList.clear();
        dataSetList.back().wordTrie.prefixSearch("", wordList);

        setBTColor(25, 4, 15, 2);
        cout << "Data set name:";
        
        string dataSetName;
        do { // input data set name
            clearLine(40, 4, ConsoleWidth, 0);
            setBTColor(40, 4, 15, 0);

            char ch;
            while ((ch = cin.get()) != '\n')
                dataSetName += ch;
        } while (dataSetName == "");
        dataSetList.back().name = dataSetName;
        mainMenuPage.viewList.buttonList.push_back(dataSetName);

        
        clrscr();
        setBTColor(25, 5, 15, 0);
        cout << "New data set created successfully.";

        saveADataSet(dataSetList.back(), dataSetList.size() - 1);
    }

    set_cursor(false);
    drawMainMenu();

}

void mainMenuInteraction(WORD action) {
    clearLine(25, 4, ConsoleWidth, 0);
    clearLine(25, 5, ConsoleWidth, 0);


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
            else if (text == "Create a new data set")
                addNewDataSet();
            else if (text == "Reverse changes") {
                reverseChanges();
                updateUI();

                setBTColor(61, 5, 15, 0);
                cout << "Changes reversed.";
            }
        }

    }
    else if (action == VK_DELETE && mainMenuPage.focusOnViewList) { // erase a data set
        int &curItem = mainMenuPage.viewList.curItem;
        auto buttonIt = mainMenuPage.viewList.buttonList.begin() + curItem;
        auto dataIt = dataSetList.begin() + curItem;

        if (curItem == (int) mainMenuPage.viewList.buttonList.size() - 1)
            --curItem;
        mainMenuPage.viewList.buttonList.erase(buttonIt);


        dataSetList.erase(dataIt);

        deleteSaveFile(curItem);

        if (mainMenuPage.viewList.buttonList.empty())
            mainMenuPage.focusOnViewList = false;
        clrscr();
        drawMainMenu();

    }


}


/// ==============================================================================================
/// ==============================================================================================

void addAWord() {
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

        saveADataSet(dataSetList[curDataSetIndex], curDataSetIndex);

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
    
    displayingMainList = true;
}

void searchByWord() {
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
        
        if (searchResult.size() == 1)
            dataSetList[curDataSetIndex].searchHistory.push_back(searchResult[0]);
        else
            dataSetList[curDataSetIndex].searchHistory.push_back({word, ""});

        saveADataSet(dataSetList[curDataSetIndex], curDataSetIndex);

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

        drawViewDataPage();
        
    }
}

void searchByDef() {
    int &curItem = viewDataPage.viewList.curItem;
    dataSet &curDataSet = dataSetList[curDataSetIndex];

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
        curDataSet.defTrie.prefixSearch(def, searchResult);

        if (searchResult.size() == 1)
            curDataSet.searchHistory.push_back({searchResult[0].second, searchResult[0].first});
        else
            curDataSet.searchHistory.push_back({"", def});

        saveADataSet(dataSetList[curDataSetIndex], curDataSetIndex);


        viewDataPage.viewList.buttonList.clear();
        viewDataPage.viewList.labelList.clear();
        for (pair< string, string > w : searchResult) {
            viewDataPage.viewList.buttonList.push_back(w.second);
            viewDataPage.viewList.labelList.push_back(w.first);
        }

        if (viewDataPage.viewList.buttonList.empty())
            curItem = -1;
        else {
            viewDataPage.focusOnViewList = true;
            curItem = 0;
        }
        

        for (int i = viewDataPage.viewList.y; i < ConsoleHeight - 1; ++i)
            clearLine(0, i, ConsoleWidth, 0);

        drawViewDataPage();
        
    }

}

void viewSearchHistory() {
    viewDataPage.viewList.buttonList.clear();
    viewDataPage.viewList.labelList.clear();
    for (pair< string, string > w : dataSetList[curDataSetIndex].searchHistory) {
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
    
    drawViewDataPage();

    displayingSearchHistory = true;
}

void viewFavoriteList() {
    int &curItem = viewDataPage.viewList.curItem;
    dataSet &curDataSet = dataSetList[curDataSetIndex];

    viewDataPage.viewList.buttonList.clear();
    viewDataPage.viewList.labelList.clear();
    for (pair< string, string > w : dataSetList[curDataSetIndex].favoriteList) {
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
    
    drawViewDataPage();

    displayingFavoriteList = true;
}

void deleteAWord() {
    int &curItem = viewDataPage.viewList.curItem;
    dataSet &curDataSet = dataSetList[curDataSetIndex];

    string word = curDataSet.wordList[curItem].first,
            def = curDataSet.wordList[curItem].second;
    pair< string, string > p = {word, def};

    curDataSet.wordList.erase(curDataSet.wordList.begin() + curItem);
    curDataSet.wordTrie.erase(word);
    curDataSet.defTrie.erase(def);
    
    for (size_t i = 0; i < curDataSet.favoriteList.size(); ++i)
        if (curDataSet.favoriteList[i] == p) {
            curDataSet.favoriteList.erase(curDataSet.favoriteList.begin() + i);
            break;
        }

    saveADataSet(dataSetList[curDataSetIndex], curDataSetIndex);


    viewDataPage.viewList.buttonList.erase(viewDataPage.viewList.buttonList.begin() + curItem);
    viewDataPage.viewList.labelList.erase(viewDataPage.viewList.labelList.begin() + curItem);

    if (curItem == viewDataPage.viewList.buttonList.size())
        --curItem;
    
    for (int i = viewDataPage.viewList.y; i < ConsoleHeight - 1; ++i)
        clearLine(0, i, ConsoleWidth, 0);
    drawViewDataPage();
}

void deleteFromFavoriteList() {
    int &curItem = viewDataPage.viewList.curItem;
    dataSet &curDataSet = dataSetList[curDataSetIndex];


    curDataSet.favoriteList.erase(curDataSet.favoriteList.begin() + curItem);
    
    viewDataPage.viewList.buttonList.erase(viewDataPage.viewList.buttonList.begin() + curItem);
    viewDataPage.viewList.labelList.erase(viewDataPage.viewList.labelList.begin() + curItem);

    saveADataSet(dataSetList[curDataSetIndex], curDataSetIndex);

    
    if (curItem == viewDataPage.viewList.buttonList.size())
        --curItem;

    for (int i = viewDataPage.viewList.y; i < ConsoleHeight - 1; ++i)
        clearLine(0, i, ConsoleWidth, 0);
    drawViewDataPage();
}

void viewDataInteraction(WORD action) {

    int &curItem = viewDataPage.viewList.curItem;
    dataSet &curDataSet = dataSetList[curDataSetIndex];


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
        displayingMainList = false;
        displayingSearchHistory = false;
        displayingFavoriteList = false;
        string text = viewDataPage.buttonList[viewDataPage.curButton].text;

        if (text == "Return") {
            curPage = MAIN_MENU_PAGE;
            updateUI();

        }
        else if (text == "Add a word")
            addAWord();
        else if (text == "Search by word")
            searchByWord();
        else if (text == "Search by definition")
            searchByDef();
        else if (text == "Search history")
            viewSearchHistory();
        else if (text == "Favorite list")
            viewFavoriteList();
        else if (text == "Quizz") {
            curPage = QUIZZ_PAGE;
            updateUI();
        }


    }
    else if (action == VK_RETURN && viewDataPage.focusOnViewList) { // edit a definition
        if (!displayingMainList && !displayingFavoriteList) return;

        rollList &viewList = viewDataPage.viewList;

        int x = viewList.x + viewList.labelx;
        int y = viewList.y + (viewList.curItem % viewList.nItemsPerPage) * 3;

        clearLine(x, y, ConsoleWidth - 1, 0);
        clearLine(x, y + 1, ConsoleWidth - 1, 0);
        clearLine(x, y + 2, ConsoleWidth - 1, 0);

        setBTColor(x, y, 15, 0);
        set_cursor(true);
        
        string def;
        char ch;
        while ((ch = cin.get()) != '\n')
            def += ch;
        
        set_cursor(false);

        setBTColor(3, 5, 15, 0);
        if (def == "") 
            cout << "Editting cancelled.";
        else {
            cout << "Editting successful.";

            string word = viewList.buttonList[curItem];
            string oldDef = viewList.labelList[curItem];
            pair< string, string > p = {word, oldDef};

            auto it = find(curDataSet.wordList.begin(), curDataSet.wordList.end(), p);
            if (it != curDataSet.wordList.end())
                it->second = def;

            it = find(curDataSet.searchHistory.begin(), curDataSet.searchHistory.end(), p);
            if (it != curDataSet.searchHistory.end())
                it->second = def;

            it = find(curDataSet.favoriteList.begin(), curDataSet.favoriteList.end(), p);
            if (it != curDataSet.favoriteList.end())
                it->second = def;

            curDataSet.wordTrie.erase(word);
            curDataSet.wordTrie.insert(word, def);

            curDataSet.defTrie.erase(oldDef);
            curDataSet.defTrie.insert(def, word);

            saveADataSet(curDataSet, curDataSetIndex);

            viewList.labelList[curItem] = def;

            clearLine(0, y, ConsoleWidth - 1, 0);
            clearLine(0, y + 1, ConsoleWidth - 1, 0);
            clearLine(0, y + 2, ConsoleWidth - 1, 0);

        }
        drawViewDataPage();

    }
    else if (action == VK_ESCAPE && !displayingMainList) { // return back to the main words list
        viewDataPage.viewList.buttonList.clear();
        viewDataPage.viewList.labelList.clear();
        
        for (pair< string, string > word : curDataSet.wordList) {
            viewDataPage.viewList.buttonList.push_back(word.first);
            viewDataPage.viewList.labelList.push_back(word.second);
        }

        if (viewDataPage.viewList.buttonList.empty())
            curItem = -1;
        else 
            curItem = 0;

        displayingMainList = true;
        displayingSearchHistory = false;
        displayingFavoriteList = false;

        clearLine(0, 4, ConsoleWidth, 0);
        for (int i = viewDataPage.viewList.y; i < ConsoleHeight - 1; ++i)
            clearLine(0, i, ConsoleWidth, 0);
        drawViewDataPage();
    }
    else if (action == 'F' && viewDataPage.focusOnViewList
    && !displayingSearchHistory && !displayingFavoriteList) {
        string word = viewDataPage.viewList.buttonList[curItem],
                def = viewDataPage.viewList.labelList[curItem];
        pair< string, string > p = {word, def};

        if (find(curDataSet.favoriteList.begin(), curDataSet.favoriteList.end(), p) ==
                                                    curDataSet.favoriteList.end()) {
            curDataSet.favoriteList.push_back(p);
            saveADataSet(dataSetList[curDataSetIndex], curDataSetIndex);
        }
    }
    else if (action == VK_DELETE && viewDataPage.focusOnViewList) {
        if (displayingMainList)
            deleteAWord();
        else if (displayingFavoriteList)
            deleteFromFavoriteList();
        
        if (viewDataPage.viewList.buttonList.empty())
            viewDataPage.focusOnViewList = false;
    }
}


/// ==============================================================================================
/// ==============================================================================================

void generateQuizz() {

    srand(time(NULL));

    for (int i = 0; i < 4; ++i) {
        size_t index;
        bool ok;

        do {
            ok = true;
            index = size_t (rand() * rand()) % dataSetList[curDataSetIndex].wordList.size();
            
            for (int j = 0; j < i; ++j)
                if (index == quizzChoices[j])
                    ok = false;

        } while (!ok);

        quizzChoices[i] = index;
    }

    quizzAnswer = rand() % 4;
}

void quizzPageInteraction(WORD action) {
    dataSet &curDataSet = dataSetList[curDataSetIndex];
    vector< pair< string, string > > &wordList = curDataSet.wordList;
    rollList &viewList = quizzPage.viewList;
    
    if (VK_LEFT <= action && action <= VK_DOWN || action == VK_TAB) {
        quizzPage.move(action);
        drawQuizzPage();

    }
    else if (action == VK_RETURN && !quizzPage.focusOnViewList) {
        string text = quizzPage.buttonList[quizzPage.curButton].text;

        if (text == "Return") {
            curPage = VIEW_DATA_PAGE;
            updateUI();
        }
        else if (wordList.size() >= 4) {

            generateQuizz();

            if (text == "Word quizz") {
                quizzPage.labelList.push_back(label("Word:", 50, 9, 9, 0));
                quizzPage.labelList.push_back(label(wordList[ quizzChoices[quizzAnswer] ].first, 40, 10, 10, 0));

                quizzPage.labelList.push_back(label("Definition:", 50, 14, 9, 0));
                for (int i = 0; i < 4; ++i) {
                    string choice;
                    // cout << '\n' << char ('A' + i) << '\n';
                    choice += char ('A' + i);
                    choice += ":  " + curDataSet.wordList[ quizzChoices[i] ].second;

                    viewList.buttonList.push_back(choice);
                }
            }
            else if (text == "Definition quizz") {
                quizzPage.labelList.push_back(label("Definition:", 50, 9, 9, 0));
                quizzPage.labelList.push_back(label(wordList[ quizzChoices[quizzAnswer] ].second, 45, 10, 10, 0));

                quizzPage.labelList.push_back(label("Word:", 50, 14, 9, 0));
                for (int i = 0; i < 4; ++i){
                    string choice;
                    choice += char ('A' + i);
                    choice += ":  " + curDataSet.wordList[ quizzChoices[i] ].first;

                    viewList.buttonList.push_back(choice);
                }
            }

            
            for (int i = 9; i < ConsoleHeight - 1; ++i)
                clearLine(0, i, ConsoleWidth, 0);
            drawQuizzPage();
        }
    }
    else if (action == VK_RETURN && quizzPage.focusOnViewList) {
        quizzPage.labelList.clear();
        viewList.buttonList.clear();

        if (viewList.curItem == quizzAnswer) {// correct answer
            setBTColor(50, 28, 10, 0);
            cout << "Correct answer.";
        }
        else {// wrong answer
            setBTColor(50, 28, 12, 0);
            cout << "Wrong answer.";
            setBTColor(50, 29, 12, 0);
            string s = "The correct answer is ";
            s += char('A' + quizzAnswer);
            cout << s + ".";
        }
    }


}
