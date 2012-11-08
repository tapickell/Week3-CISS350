#pragma once
#include "person.h"
class Patient :
	public Person
{
public:
	Patient(void);
	~Patient(void);
	int getAge();
	void setAge(int);
	std::string getEmergc();
	void setEmergc(std::string);
	std::string toStr();

private:
	int age;
	std::string emergc;

};

