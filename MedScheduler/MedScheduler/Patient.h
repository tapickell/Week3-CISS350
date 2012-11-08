#pragma once
#include "person.h"
class Patient :
	public Person
{
public:
	Patient(void);
	~Patient(void);
	int getAge();
	std::string getEmergc();
	std::string getDoc();
	void setAge(int);
	void setEmergc(std::string);
	void setDoc(std::string);
	std::string toStr();

private:
	int age;
	std::string emergc;
	std::string doc;

};

