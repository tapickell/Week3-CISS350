#include "stdafx.h"
#include "Room.h"


Room::Room(void)
{
	inUse = false;
	patName = " ";
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
		for (size_t i = 0; i < roomQ.size(); i++)
		{
			temp.pushQ(roomQ[0]);
			roomQ.popQ();
		}
	}
	return temp;
}
bool Room::roomInUse()
{
	//std::cout << "var inUse == "<< inUse << std::endl;
	return inUse;
}
bool Room::QisEmpty()
{
	return roomQ.isEmpty();
}
void Room::addPtoQ(Patient P)
{
	patName = P.getName();
	roomQ.pushQ(P);
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
std::string Room::getPatName()
{
	return patName;
}
void Room::setPatName(std::string str)
{
	patName = str;
}
Patient Room::peek()
{
	return roomQ.peek();
}

void Room::popfromQ()
{
	roomQ.popQ();
	if (!roomQ.isEmpty())
	{
		patName = roomQ[0].getName();
	}
}