// MedScheduler.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "Patient.h"
#include "Doctor.h"
#include "Queue.h"
#include "fileHandler.h"


using namespace std;

void tout(string);
void errout(string);

int _tmain(int argc, _TCHAR* argv[])
{
	//array of 100 exam rooms (Q's)
	Queue Rooms[100];
	//transaction file handle
	fileHandler tfile("trans.out");
	tfile.getFile();

	//error file handle
	fileHandler erfile("error.pkl");
	erfile.getFile();

	//prompt for input "D" or "P"

	//prompt for "I" or "O"

	//if "D"
	 
		//if "I"
			
			//prompt for name, room, code.
			//if room in use kickout msg

		//if "O"
		
			//prompt for name.
			//free room
			//if patients in Q assign to other docs

	//if "P"
		
		//if "I"

			//prompt for name, age, code, emergency.
			//find doc
			//set doc
			//assign to doc Q

		//if "O"
		
			//prompt for name
			//remove from doc Q




	system("pause");
	return 0;
}

void tout(string strIN)
{
	cout << strIN << endl;
	fileHandler tFile("trans.out");
	vector<string> output;
	output.push_back(strIN);
	tFile.appendFile(output);
}

void errout(string strIN)
{
	cerr << strIN << endl;
	fileHandler errFile("error.pkl");
	vector<string> output;
	output.push_back(strIN);
	errFile.appendFile(output);
}