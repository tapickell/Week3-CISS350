#pragma once
#include "person.h"
class Doctor :
	public Person
{
public:
	Doctor(void);
	~Doctor(void);
	int getRoom();
	void setRoom(int);
	std::string toStr();

private:
	int room;
	//not sure if i should stick a queue in here or just create in in the program and associate it with the doctor.
};

