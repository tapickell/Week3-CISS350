

#include "stdafx.h"
#include "Doctor.h"


Doctor::Doctor(void)
{
}

Doctor::Doctor(std::string str1, int num, std::string str2)
{
	Person::setName(str1);
	Person::setCode(str2);
	setRoom(num);
}

Doctor::~Doctor(void)
{
}

int Doctor::getRoom()
{
	return room;
}
void Doctor::setRoom(int intIN)
{
	room = intIN;
}
std::string Doctor::toStr()
{
	std::string out;
	return out;
}

