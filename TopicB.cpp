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

/** Checks to see if string is parenthetically correct
@param expression	The string to test for parenthetical correctness
@return  true if the string is parenthetically correct, or false if not */
bool checkExpression(const string& expression);


int main()
{
	ifstream inputFile;
	string fileName;  // Holds the user-inputted file name
	string fileLine;  // Holds the line extracted from the file
	string expression; // Holds the expression to be tested
	bool ableToOpen;  // Flag to see if file exists
	bool isBalanced;  // Flag for balanced expression

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
	} // end while
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
	for (unsigned int i = 0; i < firstLine.length(); i++)
	{
		ls1.push(firstLine[i]);
	} // end for

	cout << "Create a copy, ls2, of the stack and display the copy:\n";
	LinkedStack<char> ls2(ls1);
	cout << ls2;

	cout << "\n\nAssign the first stack, ls1, to the second stack, ls2, and then display the second stack:\n";
	ls2 = ls1;
	cout << ls2;

	cout << "\n\n\n\nDo the expression checking:\n\n\n";
	while (!lq.isEmpty())
	{
		expression = lq.peekFront();
		lq.dequeue();
		cout << "The next string is:\t" << expression;
		isBalanced = checkExpression(expression);
		if (isBalanced)
			cout << "\tis a correct expression\n\n\n";
		else
			cout << "\tis NOT a correct expression\n\n\n";
	} // end while

	// Program Over
	cout << "Program Over\n\n";
	cin.ignore();
	cout << "Press Enter to end --> ";
	cin.ignore();
	cout << endl;
	return 0;
} // end main

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

bool checkExpression(const string& expression)
{
	LinkedStack<char> balancedStack;
	bool balancedSoFar = true;
	unsigned int i = 0;  // Used to keep track of position in expression
	int singleQuote = 0, doubleQuote = 0;  // Used to keep track of delimiters ' and "
	char ch;  // Holds character at position i in expression

	while ( balancedSoFar && (i < expression.length()) )
	{
		// Get first character in expression, then increment position
		ch = expression[i];
		i++;

		switch (ch)
		{	
			// Skip next character if escape character is found
			case '\\':
				i++;
				break;

			// Push an open token
			case '{':
			case '[':
			case '(':
				balancedStack.push(ch);
				break;
			case '\'':
			{
				singleQuote++;
				if (singleQuote % 2 == 0)
					balancedStack.pop();  // Pop matching delimiter
				else
					balancedStack.push(ch);
				break;
			} // end ' case
			case '"':
			{
				doubleQuote++;
				if (doubleQuote % 2 == 0)
					balancedStack.pop();  // Pop matching delimiter
				else
					balancedStack.push(ch);
				break;
			} // end " case
			
			// Close tokens
			case '}':
			case ']':
			case ')':
			{
				// Make sure stack is not empty and the close token matches the open
				if (!balancedStack.isEmpty() && 
					(  (balancedStack.peek() == '(') 
					|| (balancedStack.peek() == '{')
					|| (balancedStack.peek() == '[') ) )
					balancedStack.pop();  // Pop a matching closed token
				else                      // No matching closed token
					balancedSoFar = false;
				break;
			}
		} // end switch
	} // end while

	if ( !(balancedSoFar && balancedStack.isEmpty()) )
		balancedSoFar = false;

	return balancedSoFar;
} // end checkExpression