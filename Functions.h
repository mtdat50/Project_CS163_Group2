#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <filesystem>
#include <algorithm>
#include "Trie.h"


using namespace std;

// not created
// return false if data in file is wrong formatted, true otherwise
void loadNewDataSet(string filepath, vector< pair < string, string > > &data);

// not created
void buildTrie(vector< pair < string, string > > &data, trie &dataSet, char type); // type = word - def or def - word
