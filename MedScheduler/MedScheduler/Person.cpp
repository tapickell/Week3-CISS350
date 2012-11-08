#include "stdafx.h"
#include "Person.h"


Person::Person(void)
{
}


Person::~Person(void)
{
}

std::string Person::getName()
{
	return name;
}
std::string Person::getCode()
{
	return code;
}
void Person::setName(std::string stringIn)
{
	name = stringIn;
}
void Person::setCode(std::string stringIn)
{
	code = stringIn;
}
std::string Person::toStr()
{
	std::string out;
	return out;
}