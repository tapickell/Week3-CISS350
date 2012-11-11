#pragma once

#include "Queue.h"

class Room
{
public:
	Room(void);
	~Room(void);
	void useRoom(std::string, std::string);
	Queue leaveRoom();
	bool roomInUse();
	void addPtoQ(Patient);
	int getProomNum(std::string);
	void addQtoQ(Queue);
	std::string getDoc();
	std::string getCode();

private:
	Queue roomQ;
	bool inUse;
	std::string docName;
	std::string code;
};

