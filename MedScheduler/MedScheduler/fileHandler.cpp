/* ***************************************************************************

Programmer: Todd Pickell

Filename: fileHandler.cpp

Requirements: None

Includes: 
#include "StdAfx.h"
#include "fileHandler.h"

Course: CISS-350A

Date: 11-1-12

Assignment: Week 2

Description: this is the file handler class that opens, read from, writes to and closes the files.

************************************************************************* */


#include "stdafx.h"
#include "fileHandler.h"

using namespace std;

/*constructor that takes in a string for 
the file name the object will have a handle to */
fileHandler::fileHandler(string name)
{
	theFileName = name;
}


fileHandler::~fileHandler(void)
{
}

/* this method returns a vector<string> that
contains one string for each line in the file */
vector<string> fileHandler::getFile()
{
	ifstream inFile;
	string fileLine;
	vector<string> document;

	inFile.open(theFileName);
	if (inFile.is_open())
	{
		//cout << "Getting file..." << endl;
		//cout << endl;
		//cout << "From File: " << theFileName << endl;
		while(!inFile.eof())
		{
			getline(inFile, fileLine);
			document.push_back(fileLine);
			//cout << fileLine << endl;
		}
	} else {
		//TODO
		//may be nice to ask if user wants to exit and check file for corruption
		//or to just create new file.
		ofstream newFile;
		newFile.open(theFileName);
		newFile.close();
		//cout << "Creating new file..." << endl;
		//cout << endl;
		inFile.open(theFileName);
	}
	inFile.close();
	return document;
}


/* this method outputs strings from a file
	directly to cout. like cat in Unix/Linux	*/
void fileHandler::catFile()
{
	vector<string> stringsOut = (*this).getFile();
	for (size_t i = 0; i < stringsOut.size(); i++)
	{
		cout << stringsOut[i] << endl;
	}
}


/* this method takes a vector<string> and then writes
each string on a separate line out to the file*/
void fileHandler::putFile(vector<string> &fileStrings)
{
	ofstream outFile;
	outFile.open(theFileName); 
	for (size_t i = 0; i < fileStrings.size()-1; i++) //to keep from adding extra \n to end of file -1 from fileStrings.size()
	{
		outFile << fileStrings[i] << "\n";
		//cout << fileStrings[i] << endl;s
	}
	//to prevent from adding extra \n every time program runs
	outFile << fileStrings[fileStrings.size()-1];
	outFile.close();
}

/* this method takes a vector<string> and then appends
each string on a separate line to the end of the file*/
void fileHandler::appendFile(vector<string> &fileStrings)
{
	ofstream outFile;
	outFile.open(theFileName, ofstream::app); //add opening in append mode
	for (size_t i = 0; i < fileStrings.size(); i++) //removed -1 from fileStrings.size()
	{
		outFile << fileStrings[i] << "\n";
		//cout << fileStrings[i] << endl;s
	}
	//to prevent from adding extra \n every time program runs
	//outFile << fileStrings[fileStrings.size()-1];
	outFile.close();
}