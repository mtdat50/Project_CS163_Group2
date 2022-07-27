#pragma once
#include <iostream>
#include <string>
#include <vector>

#include "Trie.h"


using namespace std;


bool loadNewDataSet(string filepath, vector< pair < string, string > > &data);

void buildTrie(vector< pair < string, string > > &data, trie &dataSet, char type); // type = word - def or def - word