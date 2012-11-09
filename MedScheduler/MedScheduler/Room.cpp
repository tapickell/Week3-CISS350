#include "stdafx.h"
#include "Room.h"


Room::Room(void)
{
}


Room::~Room(void)
{
}

void Room::useRoom()
{
	inUse = true;
}
Queue Room::leaveRoom()
{
	inUse = false;
	Queue temp;
	if (!roomQ.isEmpty())
	{
		//move remaining patients in Q to other doctors Q
		temp = roomQ;
		roomQ.clearQ();
	}
	return temp;
}
bool Room::roomInUse()
{
	return inUse;
}
void Room::addToQ(Queue theQ) // this could allow to dump one Q into another
{
	for (int i = 0; i < theQ.size(); i++)
	{
		roomQ.pushQ(theQ[i]);
	}
}