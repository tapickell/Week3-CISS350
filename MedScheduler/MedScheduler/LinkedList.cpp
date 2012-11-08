

#include "stdafx.h"
#include "Patient.h"
#include "LinkedList.h"


LinkedList::LinkedList(void)
{
	head = NULL;
	_count = 0;
}


LinkedList::~LinkedList(void)
{
	clear();
	head = NULL;
	tempPtr = NULL;
	visitPtr = NULL;
}

int LinkedList::add(Patient client)
{
	if (head == NULL)
	{
		head = new node;
		head->data = client;
		head->nextLink = NULL;
		head->previousLink = NULL;
	} else
	{
		visitPtr = head;
		while (visitPtr->nextLink != NULL)
		{
			visitPtr = visitPtr->nextLink;
		}

		tempPtr = new node;
		tempPtr->data = client;
		tempPtr->nextLink = NULL;
		tempPtr->previousLink = visitPtr;
		visitPtr->nextLink = tempPtr;
	}
	_count++;
	return _count;
}

void LinkedList::inRange(int index)
{
	if (index < 0)
	{
		index += _count;
	}
	if (head == NULL)
	{
		throw new std::string("List is empty");
	} else if (index >= _count)
	{
		throw new std::string("ERROR: Index is out of range");
	}
}

Patient LinkedList::getAt(int index)
{
	goToNode(index);
	return visitPtr->data; // std::bad_alloc at memory location   ??? WT?
}

void LinkedList::goToNode(int index)
{
	inRange(index);
	visitPtr = head;
	int i = 1;
	if (index != 0)
	{
		while (visitPtr->nextLink != NULL)
		{
			visitPtr = visitPtr->nextLink;
			if (i == index)
			{
				break;
			}
			i++;
		}
	}

	if(visitPtr == NULL)
	{
		throw new std::string("Unable to find index");
	}
}

int LinkedList::count()
{
	return _count;
}

void LinkedList::removeAt(int index)
{
	if (index == 0)
	{
		tempPtr = head->nextLink;
		delete head;
		if (tempPtr != NULL)
		{
			tempPtr->previousLink = NULL;
			head = tempPtr;
		}
	} else
	{
		goToNode(index);
		tempPtr = visitPtr->previousLink;
		tempPtr->nextLink = visitPtr->nextLink;
		tempPtr = visitPtr->nextLink;
		if (tempPtr != NULL)
		{
			tempPtr->previousLink = visitPtr->previousLink;
		}
		delete visitPtr;
	}
	_count--;
}

void LinkedList::clear()
{
	while (_count > 0)
	{
		removeAt(0);
	}
	head = NULL;
}

//std::vector<std::string> LinkedList::to_str()
//{
//	std::vector<std::string> temp;
//	for (int i = 0; i < (*this).count(); i++)
//	{
//		temp.push_back((*this)[i].to_str());
//	}
//	return temp;
//}
//
//std::vector<std::string> LinkedList::to_str_matched()
//{
//	std::vector<std::string> temp;
//	for (int i = 0; i < (*this).count(); i++)
//	{
//		temp.push_back((*this)[i].to_str_matched());
//	}
//	return temp;
//}
//
//std::vector<std::string> LinkedList::to_str_free()
//{
//	std::vector<std::string> temp;
//	for (int i = 0; i < (*this).count(); i++)
//	{
//		temp.push_back((*this)[i].to_str_free());
//	}
//	return temp;
//}
//
//std::vector<std::string> LinkedList::toStack()
//{
//	std::vector<std::string> temp;
//	for (int i = 0; i < (*this).count(); i++)
//	{
//		temp.push_back((*this)[i].to_str());
//	}
//	return temp;
//}

Patient LinkedList::operator[] (int index)
{
	return getAt(index);
}

int LinkedList::operator+= (Patient client)
{
	return add(client);
}


