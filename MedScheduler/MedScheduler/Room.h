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
	void popfromQ();
	Patient peek();
	void addQtoQ(Queue);
	std::string getDoc();
	std::string getCode();
	std::string getPatName();
	void setPatName(std::string);

private:
	Queue roomQ;
	bool inUse;
	std::string docName;
	std::string code;
	std::string patName;
};

