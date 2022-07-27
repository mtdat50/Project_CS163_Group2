#pragma once

#include <windows.h>
#include <conio.h>
#include <iostream>


void SetBGColor(WORD color);
void clrscr(void); 
void gotoxy(short x, short y);
void SetColor(WORD color);
void set_cursor(bool visible);
void SetWindowSize(SHORT width, SHORT height);
void setBTColor(int x, int y, int color, int background);
void clearLine(int xbegin, int y, int xend, int background);