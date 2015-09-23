#include "StdAfx.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "game.h"
#using <system.drawing.dll>

using namespace System;
using namespace System::Drawing;

//Constants
const int BOARDWIDTH = 9;
const int BOARDHEIGHT = 9;
const int RECTSIZE = 50;

//Int[] for drawing board
int gameBoard[BOARDWIDTH][BOARDHEIGHT];

//Ints for colours
const int FREE = 0;
const int BLUELIGHT = 1;
const int BLUEDARK = 2;
const int GREEN = 3;
const int PURPLE = 4;
const int RED = 5;
const int YELLOW = 6;
const int SELECTED = 7;

//Images for colours
ref class Images{
public:
	static Bitmap^ IMGFREE = (Bitmap^)Image::FromFile("FREE.png");
	static Bitmap^ IMGBLUELIGHT = (Bitmap^)Image::FromFile("BLUELIGHT.png");
	static Bitmap^ IMGBLUEDARK = (Bitmap^)Image::FromFile("BLUEDARK.png");
	static Bitmap^ IMGGREEN = (Bitmap^)Image::FromFile("GREEN.png");
	static Bitmap^ IMGPURPLE = (Bitmap^)Image::FromFile("PURPLE.png");
	static Bitmap^ IMGRED = (Bitmap^)Image::FromFile("RED.png");
	static Bitmap^ IMGYELLOW = (Bitmap^)Image::FromFile("YELLOW.png");
	static Bitmap^ IMGSELECTED = (Bitmap^)Image::FromFile("SELECTED.png");
};

//Boolean for gameOver
bool gameOver = false;

//Initialises Board
void initBoard()
{
	for (int x = 0; x < BOARDWIDTH; x++)
	{
		for (int y = 0; y < BOARDHEIGHT; y++)
		{
			gameBoard[x][y] = FREE;
		}
	}
}

//Chooses three random positions on board and randomises picture ofr those positions
void addNew()
{
	//Ints for colour, X, Y
	int randomColour;
	int X;
	int Y;

	//Generate Random Seed
	srand(time(NULL));

	//Randomise three times
	for (int i = 0; i < 3; i++)
	{
		//Randomise Colour (Choose between 1 and 6)
		randomColour = rand() % 6 + 1;

		//Randomise Space, Check if free
		do
		{
			X = rand() % 9;
			Y = rand() % 9;
		} while (gameBoard[X][Y] != FREE);
		
		//Update Gameboard
		gameBoard[X][Y] = randomColour;
	}
}

//Draws Board inside a picturebox
void drawBoard(Graphics^ g)
{
	for (int x = 0; x < BOARDWIDTH; x++)
	{
		for (int y = 0; y < BOARDHEIGHT; y++)
		{
			//Create Rectangle object
			Rectangle bounds(x * RECTSIZE, y * RECTSIZE, RECTSIZE, RECTSIZE);

			//Decide what image to draw
			switch (gameBoard[x][y])
			{
			case 0:
				//Draw Free Cell
				g->DrawImage(Images::IMGFREE, bounds);
				break;
			case 1:
				//Draw Light Blue Cell
				g->DrawImage(Images::IMGBLUELIGHT, bounds);
				break;
			case 2:
				//Draw Dark Blue Cell
				g->DrawImage(Images::IMGBLUEDARK, bounds);
				break;
			case 3:
				//Draw Green Cell
				g->DrawImage(Images::IMGGREEN, bounds);
				break;
			case 4:
				//Draw Purple Cell
				g->DrawImage(Images::IMGPURPLE, bounds);
				break;
			case 5:
				//Draw Red Cell
				g->DrawImage(Images::IMGRED, bounds);
				break;
			case 6:
				//Draw Yellow Cell
				g->DrawImage(Images::IMGYELLOW, bounds);
				break;
			case 7:
				//Draw Selected Cell
				g->DrawImage(Images::IMGSELECTED, bounds);
				break;
			}
		}
	}
	
	
}
