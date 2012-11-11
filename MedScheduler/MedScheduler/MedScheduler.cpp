// MedScheduler.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "Patient.h"
#include "Doctor.h"
#include "Queue.h"
#include "Room.h"
#include "fileHandler.h"
#include "InvalidEntryError.h"
#include "UnavailableRoomError.h"


using namespace std;

void tout(string);
void errout(string);
vector<string> split_by_whitespace(string);
bool checkForAlpha(string);
bool checkForNum(string);
bool checkForCode(string);
int findDocByName(string, vector<Doctor>);

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
		try   //**********************    get input from user and process   **************************//
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
										rooms[x+1].useRoom(docInfoStack[0], docInfoStack[2]);//add doc name and code to room
										//check doc in / add to list
										DocsIn.push_back(Doctor(docInfoStack[0], x, docInfoStack[2]));
										stringstream assign;
										assign << "Doctor " << docInfoStack[0] << " has been assigned to room number " << docInfoStack[1];
										tout(assign.str());
		//doc has been added *********************************  DO   MORE  FROM HERE  ONCE DOC  IS  ASSIGNED  !!!!   **************************************//

									} else {
										//if room in use kickout msg
										throw UnavailableRoomError();
									}
								} else {
									//else throw error
									throw InvalidEntryError("Room number out of range");
								}
							} else {
								//else throw error
								throw InvalidEntryError("Please enter valid data");
							}
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
							if (checkForAlpha(docNameStack[0]))
							{
								//find doc in list
								int docIndex;
								bool docFound = false;
								for (size_t i = 0; i < DocsIn.size(); i++)
								{
									if (DocsIn[i].getName() == docNameStack[0])
									{
										docIndex = i;
										docFound = true;
									}
								}
								if (docFound)
								{
									//remove doc from list
									Doctor temp = DocsIn[docIndex];
									DocsIn.erase(DocsIn.begin() + docIndex);
									//free room [index is room number - 1]
									Queue tempQ = rooms[temp.getRoom() - 1].leaveRoom();
									//if patients in Q assign to other docs
									if (!tempQ.isEmpty())
									{
										tout("relocating remaining patients to other waiting rooms...");
										//reassign patients to other rooms Q according to rules
										while (!tempQ.isEmpty())
										{
											bool roomFound = false;
											//check all rooms
											for each (Room r in rooms)
											{
												//check for room with doc assigned
												if (r.roomInUse())
												{
													//check doc code for match or doc code for general practitioner
													if (r.getCode() == tempQ[0].getCode() || r.getCode() == "GEN")
													{
														r.addPtoQ(tempQ.popQ());
														roomFound = true;
													}
												}
											}
											if (!roomFound)
											{
												//if room wasn't found matching patients needed code
												for each (Room r in rooms)
												{
													//check for room with doc assigned
													if (r.roomInUse())
													{
														//add to any available docs Q
														r.addPtoQ(tempQ.popQ());
													}
												}
											}
										}
										tout("All patients have been reassigned to other rooms");
									}//end if Q not empty
									stringstream outs;
									outs << "Doctor " << temp.getName() << " has been checked out and room " << temp.getRoom();
									tout(outs.str());
								} else {
									throw InvalidEntryError("Doctor name not found");
								}
							}
						} else {
							throw InvalidEntryError();
						}

					} else if (entry[0] == pat) //if "P"
					{
						//if "I"
						if (entry[1] == in) //check in patient **************************************
						{
							//prompt for name, age, code, emergency.
							//set doc
							//assign to doc Q
							//prompt for name, room, code.
							string patInfo;
							vector<string> patInfoStack;
							tout("Enter Patient information:");
							tout("patient_name age medical_code emergency");
							getline(cin, patInfo);
							patInfoStack = split_by_whitespace(patInfo);
							stringstream greet;
							greet << "Attempting to login Patient " << patInfoStack[0];
							//input validation
							if (checkForAlpha(patInfoStack[0]) && checkForNum(patInfoStack[1]) && checkForCode(patInfoStack[2]))
							{			
								int y = atoi(patInfoStack[1].c_str());
								Patient patIn;
								if (y >= 0)
								{
									//find doc
									if (y < 16)
									{
										//if patient is under 16 code is set to pediatric
										patInfoStack[2] = "PED";
									}
									bool roomFound = false;
									//check all rooms
									for (size_t i = 0; i < sizeof(rooms); i++)
									{
										//check for room with doc assigned
										if (rooms[i].roomInUse())
										{
											//check doc code for match or doc code for general practitioner
											if (rooms[i].getCode() == patInfoStack[2])
											{
												patIn = Patient(patInfoStack[0], y, patInfoStack[2], patInfoStack[3]);
												patIn.setDoc(rooms[i].getDoc());
												patIn.setRoomNum(findDocByName(rooms[i].getDoc(), DocsIn));///get room number ?!?!?!
												rooms[i].addPtoQ(patIn);
												roomFound = true;
											}
										}
									}
									if (!roomFound)
									{
										//if room wasn't found matching patients needed code
										for (size_t i = 0; i < sizeof(rooms); i++)
										{
											//check for room with doc assigned
											if (rooms[i].roomInUse())
											{
												if (rooms[i].getCode() == "GEN")
												{
													//add to gen pract Q
												patIn = Patient(patInfoStack[0], y, patInfoStack[2], patInfoStack[3]);
												patIn.setDoc(rooms[i].getDoc());
												patIn.setRoomNum(findDocByName(rooms[i].getDoc(), DocsIn));///get room number ?!?!?!
												rooms[i].addPtoQ(patIn);
												roomFound = true;
												}												
											}
										}
									}
									if (!roomFound)
									{
										//if room wasn't found matching patients needed code
										for (size_t i = 0; i < sizeof(rooms); i++)
										{
											//check for room with doc assigned
											if (rooms[i].roomInUse())
											{
												//add to any room with assigned doctor
												patIn = Patient(patInfoStack[0], y, patInfoStack[2], patInfoStack[3]);
												patIn.setDoc(rooms[i].getDoc());
												patIn.setRoomNum(findDocByName(rooms[i].getDoc(), DocsIn));///get room number ?!?!?!
												rooms[i].addPtoQ(patIn);
												roomFound = true;
											}
										}
									}
									if (roomFound)
									{
										stringstream pats;
										pats << "Patient " << patIn.getName() << " has been assigned to Doctor " << patIn.getDoc() << " in room " << patIn.getRoomNum();
										tout(pats.str());
									} else {
										tout("I'm sorry no doctor is available at the moment. Please try again later.");
									}

								} else {
									//else throw error
									throw InvalidEntryError("Age cannot be negative!");
								}
							} else {
								//else throw error
								throw InvalidEntryError("Please enter valid data");
							}

						} else if (entry[1] == out) //if "O"    check out patient *************************************
						{
							//prompt for name
							string patInfo;
							vector<string> patInfoStack;
							tout("Enter Patient Name:");
							getline(cin, patInfo);
							patInfoStack = split_by_whitespace(patInfo);
							stringstream goodbye;
							goodbye << "Attempting to logout Patient " << patInfoStack[0];
							tout(goodbye.str());
							//verify input
							if (checkForAlpha(patInfoStack[0]))
							{
								//find patient
								try
								{
									bool found = false;
									int temp;
									//search all rooms for next patient in each Q
									for (size_t i = 0; i < sizeof(rooms); i++)
									{
										//if next in Q is same name as input
										if (rooms[i].peek().getName() == patInfoStack[0])
										{
											found = true;
											temp = i;
											//may need break or something to stop search
										}
									}
									if (found)
									{
										//remove from doc Q
										rooms[temp].popfromQ();
										stringstream chkdout;
										chkdout << "Patient " << patInfoStack[0] << " successfully checked out of room " << temp;
										tout(chkdout.str());

									} else {

										throw InvalidEntryError("Patient name not found."); //will this work from here???
									}
								}
								catch (InvalidEntryError e)
								{
									errout(e.what());
								}
							}
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
		catch (runtime_error e)
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
	vector<string> codes = split_by_whitespace("PED GEN INT CAR SUR OBS PSY NEU ORT DET OPT ENT");
	for (int i = 0; i < codes.size(); i++)
	{
		if (str == codes[i])
			isMatch = true;
	}
	return isMatch;
}

int findDocByName(string str, vector<Doctor> DocsIn)
{
	bool isFound = false;
	int doc = -1;
	for (size_t i = 0; i < DocsIn.size(); i++)
	{
		if (DocsIn[i].getName() == str)
		{
			doc = i;
		}
	}
	if (!isFound) //if not found kickout error
	{
		errout("ERROR: Doctor Not Found!");
	}
	return doc;
}

int findPatientByName(string str, vector<Doctor> DocsIn)
{
	bool isFound = false;
	int doc = -1;
	for (size_t i = 0; i < DocsIn.size(); i++)
	{
		if (DocsIn[i].getName() == str)
		{
			doc = i;
		}
	}
	if (!isFound) //if not found kickout error
	{
		errout("ERROR: Doctor Not Found!");
	}
	return doc;
}