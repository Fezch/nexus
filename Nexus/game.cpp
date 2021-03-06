/*
	Program name:				Nexus 2015
	Project file name:			Nexus.sln
	Author:						Andrew Thomas Fletcher
	Date:						21/10/2015
	File Description:			This is the cpp file for the game. This file includes:
									+Definition of methods and variables.
									+2D Array of ints for the GameBoard.
									+Score controls.
*/

#include "StdAfx.h"
#include <stdlib.h>
#include <time.h>
#include <queue>
#include "game.h"
#using <system.drawing.dll>

using namespace System;
using namespace System::Drawing;

//Gameboard
int gameBoard[BOARDWIDTH][BOARDHEIGHT];

//Boolean for gameOver
bool gameOver = false;

//Integers for scoring
int score = 0;
int scoreMultiplier = 20;

//Images class for colours
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

//Nodes class for nodes
class Node{
public:
	//Public variables
	int nodeID, arrayX, arrayY, northID, eastID, southID, westID, parentID;
	bool visited, isWall;

	//Default Constructor
	Node()
	{
		nodeID = 0;
		arrayX = 0;
		arrayY = 0;
		visited = false;
		isWall = false;
		northID = 0;
		eastID = 0;
		southID = 0;
		westID = 0;
		parentID = 0;
	}

	//Initialises from passed in variables
	void initNode(int passedNodeID, int passedArrayX, int passedArrayY, bool passedIsWall)
	{
		//Saving passed in variables
		nodeID = passedNodeID;
		arrayX = passedArrayX;
		arrayY = passedArrayY;
		visited = false;
		isWall = passedIsWall;

		//Working out neighboring nodes
		//North Node
		if ((nodeID - BOARDWIDTH) <= 0)
			northID = nodeID;
		else
			northID = nodeID - BOARDWIDTH;
		//East Node
		if ((nodeID % BOARDWIDTH) == 0)
			eastID = nodeID;
		else
			eastID = nodeID + 1;
		//South Node
		if ((nodeID + BOARDWIDTH) >= BOARDWIDTH * BOARDHEIGHT)
			southID = nodeID;
		else
			southID = nodeID + BOARDWIDTH;
		//West Node
		if ((nodeID % BOARDWIDTH) == 1)
			westID = nodeID;
		else
			westID = nodeID - 1;
	}
};

//Array of nodes (1 index)
Node nodes[BOARDHEIGHT * BOARDWIDTH + 1];

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
				X = rand() % BOARDWIDTH;
				Y = rand() % BOARDHEIGHT;
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
			//Randomise Colour
			randomColour = rand() % 6 + 1;

			//Randomise Space, Check if free
			do
			{
				X = rand() % BOARDWIDTH;
				Y = rand() % BOARDHEIGHT;
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

	//Int for counting length of line
	int lineLength = 0;

	//Check for Horizontal
	for (int y = 0; y < BOARDHEIGHT; y++)
	{
		//Check for a line of at least 5
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
				lineLength = 5;
				while (gameBoard[x + lineLength][y] == colour)
				{
					lineLength++;
				}

				//Delete line
				deleteLine(lineLength, x, y, true);

				//Update Score
				score = score + (lineLength * scoreMultiplier);
			}
		}
	}

	//Check for Vertical
	for (int x = 0; x < BOARDHEIGHT; x++)
	{
		//Check for a line of at least 5
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
				lineLength = 5;
				while (gameBoard[x][y + lineLength] == colour)
				{
					lineLength++;
				}

				//Delete line
				deleteLine(lineLength, x, y, false);

				//Update Score
				score = score + (lineLength * scoreMultiplier);
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

//Checks for a path and returns true if a path is found
bool checkForPath(int startX, int startY, int destX, int destY)
{
	//Declare variables
	int startNode = 0;
	int destNode = 0;

	//Fill nodes array
	int tempNodeID = 1;
	for (int x = 0; x < BOARDWIDTH; x++)
	{
		for (int y = 0; y < BOARDHEIGHT; y++)
		{
			//Initialise and check if node is a ball
			nodes[tempNodeID].initNode(tempNodeID, x, y, gameBoard[x][y] != FREE);

			//Check if node is the start node
			if ((x == startX) && (y == startY))
			{
				startNode = tempNodeID;
			}

			//Check if node is the destination node
			if ((x == destX) && (y == destY))
			{
				destNode = tempNodeID;
			}

			//Increment tempNodeID
			tempNodeID++;
		}
	}

	//Queue for pathfinding
	std::queue<int> myQueue;

	//Add beginning node to queue
	myQueue.push(startNode);

	//Set startNode to visited
	nodes[startNode].visited = true;

	//Set startNode's parent to -1
	nodes[startNode].parentID = -1;

	//Start pathfinding
	while (myQueue.empty() == false)
	{
		//Save oldest value in queue
		int curNode = myQueue.front();

		//Remove value from queue
		myQueue.pop();

		//Check if destination node has been found
		if (curNode == destNode)
		{
			return true;
		}
		else
		{
			//Create array of current neighbors
			int neighbors[4] = { nodes[curNode].northID, nodes[curNode].eastID, nodes[curNode].southID, nodes[curNode].westID };

			//Loop through neighbors
			for each (int neighbor in neighbors)
			{
				//Check if neighbor has not been visited and is not a wall
				if (!nodes[neighbor].visited && !nodes[neighbor].isWall)
				{
					//Add neighbor to queue
					myQueue.push(neighbor);

					//Set neighbor as visted
					nodes[neighbor].visited = true;

					//Set parent of neighbor to current node
					nodes[neighbor].parentID = curNode;
				}
			}
		}
	}

	//If no path was found
	return false;
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

//Returns current score
int getScore()
{
	return score;
}