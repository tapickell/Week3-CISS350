#include "node.h"

#pragma once
class LinkedList
{
public:
	LinkedList(void);
	~LinkedList(void);

	int add(Patient);
    void removeAt(int);
    int count();
    Patient getAt(int);
    void clear();
    Patient operator [] (int);
	int operator += (Patient);
	//std::vector<std::string> to_str();
	//std::vector<std::string> to_str_matched();
	//std::vector<std::string> to_str_free();
	//std::vector<std::string> toStack();

private:
    int _count;
    void inRange(int);
	void goToNode(int);
  
    node *head;
    node *tempPtr;
    node *visitPtr;
};