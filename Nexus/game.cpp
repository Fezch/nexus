#include "StdAfx.h"
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "game.h"
#include "Node.h"
#using <system.drawing.dll>

using namespace System;
using namespace System::Drawing;

int gameBoard[BOARDWIDTH][BOARDHEIGHT];

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

//Initialises Board and Nodes
void initBoard()
{
	//Initialising Board
	for (int x = 0; x < BOARDWIDTH; x++)
	{
		for (int y = 0; y < BOARDHEIGHT; y++)
		{
			gameBoard[x][y] = FREE;
		}
	}

	//Initialising Nodes

}

//Chooses three random positions on board and randomises picture of those positions
void addNew(int freeSpaces)
{
	//Ints for colour, X, Y
	int randomColour;
	int X;
	int Y;

	//Generate Random Seed
	srand(time(NULL));

	//If there are more than 3 spaces
	if (freeSpaces > 3)
	{
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
	//Else if there is less than three free spaces
	else
	{
		//Randomise for the number of free spaces
		for (int i = 0; i < freeSpaces; i++)
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
}

//Checks for lines
bool checkForLine()
{
	//Bool for returning
	bool lineFound = false;

	//Int for colour
	int colour = 0;

	//int for counting
	int count = 0;

	//Check for Horizontal
	for (int y = 0; y < BOARDHEIGHT; y++)
	{
		for (int x = 0; x < 5; x++)
		{
			//Save colour
			colour = gameBoard[x][y];

			//Check for a line of five of colours that are not free
			if ((gameBoard[x][y] == colour && gameBoard[x + 1][y] == colour && gameBoard[x + 2][y] == colour && gameBoard[x + 3][y] == colour && gameBoard[x + 4][y] == colour) && (colour != FREE))
			{
				//A line has been found
				lineFound = true;

				//See if there are more colours in the line
				count = 5;
				while (gameBoard[x + count][y] == colour)
				{
					count++;
				}

				//Delete line
				deleteLine(count, x, y, true);
			}
		}
	}

	//Check for Vertical
	for (int x = 0; x < BOARDHEIGHT; x++)
	{
		for (int y = 0; y < 5; y++)
		{
			//Save colour
			colour = gameBoard[x][y];

			//Check for a line of five of colours that are not free
			if ((gameBoard[x][y] == colour && gameBoard[x][y + 1] == colour && gameBoard[x][y + 2] == colour && gameBoard[x][y + 3] == colour && gameBoard[x][y + 4] == colour) && (colour != FREE))
			{
				//A line has been found
				lineFound = true;

				//See if there are more (use count)
				count = 5;
				while (gameBoard[x][y + count] == colour)
				{
					count++;
				}

				//Delete line
				deleteLine(count, x, y, false);
			}
		}
	}

	//State wether a line was found
	return lineFound;
}

//Deletes a line of specified length
void deleteLine(int count, int initX, int initY, bool isHorizontal)
{
	//If horizontal
	if (isHorizontal)
	{
		for (int i = 0; i < count; i++)
		{
			gameBoard[initX + i][initY] = FREE;
		}
	}
	//Else vertical
	else
	{
		for (int i = 0; i < count; i++)
		{
			gameBoard[initX][initY + i] = FREE;
		}
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
