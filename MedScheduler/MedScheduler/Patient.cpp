

#include "stdafx.h"
#include "Patient.h"


Patient::Patient(void)
{
}

Patient::Patient(std::string str1, int y, std::string str2, std::string str3)
{
	Person::setName(str1);
	setAge(y);
	Person::setCode(str2);
	setEmergc(str3);
}

Patient::~Patient(void)
{
}

int Patient::getAge()
{
	return age;
}
std::string Patient::getEmergc()
{
	return emergc;
}
std::string Patient::getDoc()
{
	return doc;
}
int Patient::getRoomNum()
{
	return roomNum;
}
void Patient::setAge(int intIN)
{
	age = intIN;
}
void Patient::setEmergc(std::string stringIn)
{
	emergc = stringIn;
}
void Patient::setDoc(std::string stringIn)
{
	doc = stringIn;
}
void Patient::setRoomNum(int intIN)
{
	roomNum = intIN;
}
std::string Patient::toStr()
{
	std::string out;
	return out;
}

