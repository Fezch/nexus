#pragma once
using namespace System::Drawing;

//Methods
void drawBoard(Graphics^ g);
void initBoard();
void addNew(int freeSpaces);
bool checkForLine();
void deleteLine(int count, int initX, int initY, bool isHorizontal);
bool checkForPath(int currentX, int currentY, int destX, int destY);

//Constants
const int BOARDWIDTH = 9;
const int BOARDHEIGHT = 9;
const int RECTSIZE = 50;

//Int[] for game board
extern int gameBoard[BOARDWIDTH][BOARDHEIGHT];

//Ints for colours
const int FREE = 0;
const int BLUELIGHT = 1;
const int BLUEDARK = 2;
const int GREEN = 3;
const int PURPLE = 4;
const int RED = 5;
const int YELLOW = 6;
const int SELECTED = 7;