#pragma once
#include "person.h"
class Patient :
	public Person
{
public:
	Patient(void);
	Patient(std::string, int, std::string, std::string);
	~Patient(void);
	int getAge();
	std::string getEmergc();
	std::string getDoc();
	int getRoomNum();
	void setAge(int);
	void setEmergc(std::string);
	void setDoc(std::string);
	void setRoomNum(int);
	std::string toStr();

private:
	int age;
	std::string emergc;
	std::string doc;
	int roomNum;

};

