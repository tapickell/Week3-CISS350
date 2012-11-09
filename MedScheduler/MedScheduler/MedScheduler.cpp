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
bool checkForAlpha(string);
bool checkForNum(string);
bool checkForCode(string);

int _tmain(int argc, _TCHAR* argv[])
{
	//array of 100 exam rooms
	Room rooms[100];
	//list to hold doctors
	vector<Doctor> DocsIn;

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
							stringstream greet;
							greet << "Attempting to login Doctor " << docInfoStack[0] << " " << docInfoStack[2];
							//input validation
							if (checkForAlpha(docInfoStack[0]) && checkForNum(docInfoStack[1]) && checkForCode(docInfoStack[2]))
							{
								if (atoi(docInfoStack[1].c_str()) > 0 && atoi(docInfoStack[1].c_str()) < 101)
								{
									//room number is array index +1
									int x = atoi(docInfoStack[1].c_str());
									//check if room is free
									if (!rooms[x+1].roomInUse())
									{
										//assign room to doctor
										DocsIn.push_back(Doctor(docInfoStack[0], x, docInfoStack[2]));
										stringstream assign;
										assign << "Doctor " << docInfoStack[0] << " has been assignd to room number " << docInfoStack[1];
										tout(assign.str());

									} else {
										//if room in use kickout msg
									}
									}//else throw error
							} //else throw error
						} else if (entry[1] == out) //if "O"
						{
		
							//prompt for name.
							string docName;
							vector<string> docNameStack;
							tout("Enter Doctor name: ");
							getline(cin, docName);
							docNameStack = split_by_whitespace(docName);
							stringstream goodbye;
							goodbye << "Attempting to logout Doctor " << docNameStack[0];
							//input validation
							if (checkForAlpha(docNameStack[0]))							{
								//free room
								//if patients in Q assign to other docs
							}
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

bool checkForAlpha(string str)
{
	locale loc;
	int gCount = 0;
	bool isGood = false;
	for (string::iterator it=str.begin(); it!=str.end(); ++it)
	{
		if (isalpha(*it,loc))
			gCount++;
	}
	if (gCount == str.size())
		isGood = true;
	
	return isGood;
}

bool checkForNum(string str)
{
	locale loc;
	int gCount = 0;
	bool isGood = false;
	for (string::iterator it=str.begin(); it!=str.end(); ++it)
	{
		if (isdigit(*it,loc))
			gCount++;
	}
	if (gCount == str.size())
		isGood = true;
	
	return isGood;
}

bool checkForCode(string str)
{
	bool isMatch = false;
	vector<string> codes = split_by_whitespace("PED GEN INT CAR SUR OBS PSY NEU ORT DET OPT ENT");	for (int i = 0; i < codes.size(); i++)	{		if (str == codes[i])			isMatch = true;	}	return isMatch;
}