#pragma once

#include "Console.h"
#include "UIStruct.h"
#include "Data.h"
using namespace std;


void createMainMenu();
void createDataSetMenu(string dataMenu); // compile error
void createQuizMenu();


void drawMainMenu();
void drawViewDataPage();


void updateUI();