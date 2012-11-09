#pragma once

#include "Queue.h"

class Room
{
public:
	Room(void);
	~Room(void);
	void useRoom();
	Queue leaveRoom();
	bool roomInUse();
	void addToQ(Queue);

private:
	Queue roomQ;
	bool inUse;
};

