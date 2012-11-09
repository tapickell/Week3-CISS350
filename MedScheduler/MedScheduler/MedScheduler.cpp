// MedScheduler.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "Patient.h"
#include "Doctor.h"
#include "Queue.h"
#include "Room.h"
#include "fileHandler.h"
#include "InvalidEntryError.h"


using namespace std;

void tout(string);
void errout(string);
vector<string> split_by_whitespace(string);

int _tmain(int argc, _TCHAR* argv[])
{
	//array of 100 exam rooms
	Room rooms[100];
	//list to hold doctors
	LinkedList DocsIn;

	//transaction file handle
	fileHandler tfile("trans.out");
	tfile.getFile();

	//error file handle
	fileHandler erfile("error.pkl");
	erfile.getFile();

	//display welcome screen
	fileHandler welcome("welcome.pkl");
	welcome.catFile();

	// **** main loop ****
	bool done = false;
	while (!done)
	{
		string dctr = "D";
		string pat = "P";
		string in = "I";
		string out = "O";

		vector<string> entry;

		cout << endl;
		try
		{
			//prompt for input "D" or "P"
			tout("Enter D for doctor or P for patient: ");
			string dorp;
			getline(cin, dorp);
			vector<string> dorpstore = split_by_whitespace(dorp);
			if (dorpstore[0] == dctr || dorpstore[0] == pat)
			{
				entry.push_back(dorpstore[0]);

				//prompt for "I" or "O"
				tout("Enter I for check-in or O for check-out: ");
				string ioro;
				getline(cin, ioro);
				vector<string> iorostore = split_by_whitespace(ioro);
				if (iorostore[0] == in || iorostore[0] == out)
				{
					entry.push_back(iorostore[0]);

					//if "D"
					if (entry[0] == dctr)
					{
						//if "I"
						if (entry[1] == in)
						{
							//prompt for name, room, code.
							string docInfo;
							vector<string> docInfoStack;
							tout("Enter Doctor information:");
							tout("doctor_name room_number medical_code");
							getline(cin, docInfo);
							docInfoStack = split_by_whitespace(docInfo);
							//input validation
							//if room in use kickout msg
						} else if (entry[1] == out) //if "O"
						{
		
							//prompt for name.
							string docName;
							vector<string> docNameStack;
							tout("Enter Doctor name: ");
							getline(cin, docName);
							docNameStack = split_by_whitespace(docName);
							//input validation
							//free room
							//if patients in Q assign to other docs
						} else {
							throw InvalidEntryError();
						}

					} else if (entry[0] == pat) //if "P"
					{
						//if "I"
						if (entry[1] == in)
						{
							//prompt for name, age, code, emergency.
							//find doc
							//set doc
							//assign to doc Q

						} else if (entry[1] == out) //if "O"
						{
		
							//prompt for name
							//remove from doc Q
						} else {
							throw InvalidEntryError();
						}
					}

				} else {
					stringstream errormsg;
					errormsg << "ERROR: " << iorostore[0] << " is not a valid input.";
					throw InvalidEntryError(errormsg.str());
				}

			} else {
				stringstream errormsg;
				errormsg << "ERROR: " << dorpstore[0] << " is not a valid input.";
				throw InvalidEntryError(errormsg.str());
			}
		}
		catch (InvalidEntryError e)
		{
			errout(e.what());
			break;
		}		
	}


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
	tout(strIN);
	fileHandler errFile("error.pkl");
	vector<string> output;
	output.push_back(strIN);
	errFile.appendFile(output);
}

vector<string> split_by_whitespace(string myStr)
{
	size_t i, j;
	vector<string> result;

	for (i = j = 0; i < myStr.size(); )
	{

		while ( i < myStr.size() && ::isspace( myStr[i] ) ) i++;
		j = i;

		while ( i < myStr.size() && ! ::isspace( myStr[i]) ) i++;
				
		if (j < i)
		{
			result.push_back( myStr.substr( j, i - j ));

			while ( i < myStr.size() && ::isspace( myStr[i])) i++;
			j = i;
		}
	}
	if (j < myStr.size())
	{
		result.push_back( myStr.substr( j, myStr.size() - j ));
	}
	return result;
}