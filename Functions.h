#pragma once
#include <iostream>
#include <string>
#include <vector>

#include "Trie.h"


using namespace std;

// not created
// return false if data in file is wrong formated, true othewise
bool loadNewDataSet(string filepath, vector< pair < string, string > > &data);

// not created
void buildTrie(vector< pair < string, string > > &data, trie &dataSet, char type); // type = word - def or def - word