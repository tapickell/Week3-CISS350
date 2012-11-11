#include "stdafx.h"
#include "Room.h"


Room::Room(void)
{
}


Room::~Room(void)
{
}

void Room::useRoom(std::string str1, std::string str2)
{
	docName = str1;
	code = str2;
	inUse = true;
}
Queue Room::leaveRoom()
{
	code = " ";
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
void Room::addPtoQ(Patient P)
{
	roomQ.pushQ(P);
}
int getProomNum(std::string str)
{
	bool found = false;
	int temp;
	for (size_t i = 0; i < roomQ.size(); i++)
	{
		if (roomQ[i].getName() == str)
		{
			found = true;
			temp = i;
			//may need break or something to stop search
		}
	}
	if (!found)
	{
		throw InvalidEntryError("Patient name not found."); //will this work from here???
	}
	return temp;
}
void Room::addQtoQ(Queue theQ) // this could allow to dump one Q into another
{
	for (int i = 0; i < theQ.size(); i++)
	{
		roomQ.pushQ(theQ[i]);
	}
}
std::string Room::getDoc()
{
	return docName;
}
std::string Room::getCode()
{
	return code;
}