

#include "stdafx.h"
#include "Patient.h"


Patient::Patient(void)
{
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
std::string Patient::toStr()
{
	std::string out;
	return out;
}

