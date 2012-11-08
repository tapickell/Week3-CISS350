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
void Patient::setAge(int intIN)
{
	age = intIN;
}
std::string Patient::getEmergc()
{
	return emergc;
}
void Patient::setEmergc(std::string stringIn)
{
	emergc = stringIn;
}
std::string Patient::toStr()
{
	std::string out;
	return out;
}