#pragma once
#include "LinkedList.h"

class Queue
{
public:
	Queue(void);
	~Queue(void);
	bool isEmpty();
	int size();
	int pushQ(Patient);
	Patient popQ();
	void clearQ();
	Patient operator[] (int);


private:
	LinkedList myQ;
};

