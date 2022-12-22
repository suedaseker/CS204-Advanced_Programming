#include <iostream>
#include <string>
#include <vector>
#include "strStack.h"
using namespace std;

//taken from lecture notes and changed

//*******************
// Constructor      *
//*******************

strStack::strStack()
{
	stackVector = new vector<string>; 
	top = -1;
}

//*************************************************
// Member function push pushes the argument onto  *
// the stack.                                     *
//*************************************************
void strStack::makeEmpty()
{
	top=-1;
}
strStack::~strStack()
{
	top=-1;
	delete stackVector; //?
}

void strStack::push(string word)
{
	
	top++;
	(*stackVector).push_back(word);
	
}

//****************************************************
// Member function pop pops the value at the top     *
// of the stack off, and copies it into the variable *
// passed as an argument.                            *
//****************************************************

void strStack::pop(string &word)
{
	if (isEmpty())
	{
		cout << "The stack is empty.\n";
	}
	else
	{
		word = (*stackVector)[top];
		(*stackVector).pop_back();
		top--;
	}
}

//****************************************************
// Member funciton isEmpty returns true if the stack *
// is empty, or false otherwise.                     *
//****************************************************
bool strStack::isEmpty(void)
{
	bool status;

	if (top == -1)
		status = true;
	else 
		status = false;

	return status;
}
