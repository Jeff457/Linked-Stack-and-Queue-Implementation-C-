/*****************************************
	Jeff Stanton
	CS M20 Topic B Project
	
	TopicB.cpp
	Status: Extra Credit
*****************************************/

#pragma warning( disable: 4290 )
#include "LinkedQueue.h"
#include "LinkedStack.h"
#include <fstream>
#include <iostream>
using namespace std;

/** Opens the requested file for input
@return  true if the file can be opened, or false if not */
bool openFileIn(ifstream& inputFile, const string& fileName);

int main()
{
	ifstream inputFile;
	string fileName;  // Holds the user-inputted file name
	string fileLine;  // Holds the line extracted from the file
	bool ableToOpen;  // Flag to see if file exists

	cout << "Create queue object lq\n\n";
	LinkedQueue<string> lq;

	cout << "Get the fle input\n\n";
	do
	{	// Ask user for file name and attempt to open
		cout << "Enter input file name: ";
		cin >> fileName;
		ableToOpen = openFileIn(inputFile, fileName);
		if (!ableToOpen)
			cout << fileName << " cannot be opened." << endl;
	} while (!ableToOpen);

	// Read lines from the file and put into queue object
	getline(inputFile, fileLine);
	while (inputFile)
	{
		lq.enqueue(fileLine);
		getline(inputFile, fileLine);
	}
	inputFile.close();

	cout << "\n\n\nAfter getting the file input, test other functions*******\n";
	cout << "Create lq1, a copy of the queue\n\n";
	LinkedQueue<string> lq1(lq);
	cout << "Display the contents of the copy queue lq1:\n";
	cout << lq1 << endl;

	cout << "\nAttempt to peek the now empty queue lq1:\n";
	try
	{
		lq1.peekFront();
	}
	catch (PrecondViolatedExcep e)
	{
		cout << e.what();
	}

	cout << "\nAssign lq to lq1 and then display lq1:\n";
	lq1 = lq;
	cout << lq1;

	cout << "\nPut the first string in lq into a stack of chars, ls1\n\n";
	LinkedStack<char> ls1;
	string firstLine = lq.peekFront();
	for (int i = 0; i < firstLine.length(); i++)
	{
		ls1.push(firstLine[i]);
	}

	cout << "Create a copy, ls2, of the stack and display the copy:\n";
	LinkedStack<char> ls2(ls1);
	cout << ls2;

	cout << "\n\nAssign the first stack, ls1, to the second stack, ls2, and then display the second stack:\n";
	ls2 = ls1;
	cout << ls2;

	cout << "\n\n\nDo the expression checking:\n\n";
	//Need to create function to pass queue items into so stack can process them


	// Program Over
	cout << "Program Over\n\n";
	cin.ignore();
	cout << "Press Enter to end --> ";
	cin.ignore();
	cout << endl;
	return 0;
}

bool openFileIn(ifstream& inputFile, const string& fileName)
{
	bool status;
	
	inputFile.open(fileName);
	if (inputFile.fail())
		status = false;
	else
		status = true;

	return status;
} // end openFileIn