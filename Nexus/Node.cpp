#include "StdAfx.h"
#include <stdlib.h>
#include <stdio.h>

//Global Variables
int nodeID, arrayX, arrayY, northID, eastID, southID, westID;

void Node(int passedNodeID, int passedArrayX, int passedArrayY)
{
	//Saving passed in variables
	nodeID = passedNodeID;
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