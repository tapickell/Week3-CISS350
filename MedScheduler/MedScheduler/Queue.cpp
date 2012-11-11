

#include "stdafx.h"
#include "Patient.h"
#include "Queue.h"


Queue::Queue(void)
{
}


Queue::~Queue(void)
{
}

bool Queue::isEmpty()
{
	return myQ.count() == 0 ? true : false;
}
int Queue::size()
{
	return myQ.count();
}
int Queue::pushQ(Patient person)
{
	return myQ += person;
}
Patient Queue::popQ()
{
	if(size() > 0)
	{
		Patient nextInLine = myQ[0];
		myQ.removeAt(0);
		return nextInLine;
	} else {
		throw new std::string("The Queue is empty!");
	}
}
Patient Queue::peek()
{
	return myQ[0];
}
void Queue::clearQ()
{
	myQ.clear();
}
Patient Queue::operator[] (int index)
{
	return myQ[index];
}