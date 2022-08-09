#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <filesystem>
#include <direct.h>
#include <algorithm>

#include "Trie.h"
#include "Data.h"


using namespace std;


// return false if data in file is wrong formatted, true otherwise
void loadNewDataSet(string filepath, vector< pair < string, string > > &data);

// type = word - def or def - word
void buildTrie(vector< pair < string, string > > &data, trie &dataSet, char type);


/// =============================================================================

void saveADataSet(dataSet &curDataSet, int index);

void saveData();


void loadData();

/// ==============================================================================
void deleteSaveFile(int index);