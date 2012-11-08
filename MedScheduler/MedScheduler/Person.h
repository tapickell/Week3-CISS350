#pragma once
class Person
{
public:
	Person(void);
	~Person(void);
	std::string getName();
	std::string getCode();
	void setName(std::string);
	void setCode(std::string);
	std::string toStr();

private:
	std::string name;
	std::string code;
};

