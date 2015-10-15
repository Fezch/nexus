#include "StdAfx.h"
#include <stdlib.h>
#include <stdio.h>
#include "Node.h"

//Global Variables
int nodeID, arrayX, arrayY, northID, eastID, southID, westID, parentID;

//Constructor
void Node(int passedNodeID, int passedArrayX, int passedArrayY)
{
	//Saving passed in variables
	nodeID = passedNodeID;
	parentID = passedNodeID;
	arrayX = passedArrayX;
	arrayY = passedArrayY;

	//Working out neighboring nodes
	//North Node
	if ((nodeID - 9) <= 0)
		northID = nodeID;
	else
		northID = nodeID - 9;
	//East Node
	if ((nodeID % 9) == 0)
		eastID = nodeID;
	else
		eastID = nodeID + 1;
	//South Node
	if ((nodeID + 9) >= 82)
		southID = nodeID;
	else
		southID = nodeID + 9;
	//West Node
	if ((nodeID % 9) == 1)
		westID = nodeID;
	else
		westID = nodeID - 1;
}

//Getters
int getX() { return arrayX; }
int getY() { return arrayY; }
int getNorth() { return northID; }
int getEast() { return eastID; }
int getSouth() { return southID; }
int getWest() { return westID; }
int getParent() { return parentID; }

//Setters
void setParent(int passedParentID)
{
	parentID = passedParentID;
}