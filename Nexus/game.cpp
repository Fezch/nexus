#include "StdAfx.h"
#include "game.h"
#using <system.drawing.dll>

using namespace System;
using namespace System::Drawing;

//Constants
const int BOARDWIDTH = 9;
const int BOARDHEIGHT = 9;
const int RECTSIZE = 50;

//Int[] for drawing board
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

//Boolean for gameOver
bool gameOver = false;



//Draws Board inside a picturebox
void drawBoard(Graphics^ g)
{
	Pen^ redPen = gcnew Pen(Color::Red);
	redPen->Width = 1;
	for (int x = 0; x < BOARDWIDTH; x++)
	{
		for (int y = 0; y < BOARDHEIGHT; y++)
		{
			g->DrawRectangle(redPen, x * RECTSIZE, y * RECTSIZE, RECTSIZE, RECTSIZE);
		}
	}
	
	
}
