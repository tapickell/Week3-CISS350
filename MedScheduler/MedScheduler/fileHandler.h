/* ***************************************************************************

Programmer: Todd Pickell

Filename: fileHandler.h

Requirements: None

Includes: 

Course: CISS-350A

Date: 11-1-12

Assignment: Week 2

Description: this is the file handler class that opens, read from, writes to and closes the files.

************************************************************************* */


#pragma once
class fileHandler
{
public:
	/*constructor that takes in a string for 
	the file name the object will have a handle to */
	fileHandler(std::string);

	~fileHandler(void);

	/* this method returns a vector<string> that
	contains one string for each line in the file */
	std::vector<std::string> getFile();

	/* this method outputs strings from a file
	   directly to cout. like cat in Unix/Linux	*/
	void catFile();

	/* this method takes a vector<string> and then writes
	each string on a separate line out to the file*/
	void putFile(std::vector<std::string> &);

	/* this method takes a vector<string> and then appends
	each string on a separate line to the end of the file*/
	void appendFile(std::vector<std::string> &fileStrings);

private:
	std::string theFileName;
};