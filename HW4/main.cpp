#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include "LinkedList.h"
#include "iqueue.h"
#include "squeue.h"
#include "strStack.h"

using namespace std;

vector<string> services;//a global variable to keep track of all services (functions)

//to check if the input file is openning successfully
bool fileFail(string filename)
{
	ifstream input;

	input.open(filename.c_str());

	if (input.fail())
	{
		return false;
	}
	input.close();
	return true;
}

//to get file input from the user and form the linked list of services
void getFile(LinkedList &linkedlist)
{
	string option, filename;
	cout << "If you want to open a service (function) defining file, " << endl
		<< "then press (Y/y) for 'yes', ortherwise press any single key" << endl;
	cin >> option;
	
	while (option == "Y" || option == "y") //loop for getting input file until user wants to stop
	{
		cout << "Enter the input file name: ";
		cin >> filename;
		if (fileFail(filename) == false)
		{
			cout << "Cannot open the file" << endl;
		}
		else
		{
			ifstream file(filename.c_str());
			string line, funcname, command;

			getline(file, line);
			funcname = line;
			funcname.pop_back();
			getline(file, line);
			command = line;
			command.pop_back();
			linkedlist.ServiceList(funcname, command);
			services.push_back(funcname);
		
			while(getline(file, line))
			{
				command = line;
				command.pop_back();
				linkedlist.ServiceList(funcname, command);
			}
			file.close();
		}
		cout << "If you want to open a service (function) defining file, " << endl
		<< "then press (Y/y) for 'yes', ortherwise press any single key" << endl;
		cin >> option;
	}
}

//to check if the wanted service is available (is in the linked list)
bool isInServices(string funcname)
{
	for (int i = 0; i < services.size(); i++)
	{
		if (services[i] == funcname)
		{
			return true;
		}
	}
	return false;
}

//adding an instructor's request to the instructor's queue
void addInstructorRequest(iQueue &iqueue)
{
	string funcname;
	cout << "Add a service (function) that the instructor wants to use:" << endl;
	cin >> funcname;
	if (!isInServices(funcname)) //if the service is not avilable, going back to menu
	{
		cout << "The requested service (function) does not exist." << endl;
		cout << "GOING BACK TO MAIN MENU" << endl;
	}
	else
	{
		string name;
		int id;
		cout << "Give the instructor's name: ";
		cin >> name;
		cout << "Give the instructor's ID (an int): ";
		cin >> id;

		iqueue.enqueue(funcname, name, id); //adding instructor's information to the queue

		cout << "Prof. " << name << "'s service request of " << funcname
			<< "has been put in the instructor's queue." << endl 
			<< "Waiting to be served..." << endl;
	}
}

//adding s student's request to the student's queue
void addStudentRequest(sQueue &squeue)
{
	string funcname;
	cout << "Add a service (function) that the instructor wants to use:" << endl;
	cin >> funcname;
	if (!isInServices(funcname)) //if the service is not avilable, going back to menu
	{
		cout << "The requested service (function) does not exist." << endl;
		cout << "GOING BACK TO MAIN MENU" << endl;
	}
	else
	{
		string name;
		int id;
		cout << "Give the student's name: ";
		cin >> name;
		cout << "Give the sudent's ID (an int): ";
		cin >> id;

		squeue.enqueue(funcname, name, id); //adding student's information to the queue

		cout << name << "'s service request of " << funcname 
			<< "has been put in the student's queue." << endl 
			<< "Waiting to be served..." << endl;
	}

}

void processARequest(string functionName, LinkedList &linkedlist, strStack &stack)
{
	fnode *ptr = linkedlist.gethead(); //loop variable

	while (ptr != NULL && ptr->funcname != functionName ) //finding the wanted servies from the linked list
	{
		ptr = ptr->next;
	}

	cnode *ptr2 = ptr->commands;
	while ( ptr2 != NULL) //processing all commands
	{
		string currcommand = ptr2->cname;
		istringstream word(currcommand);
		string command, variable;
		word >> command >> variable;

		if(command == "define") 
		{
			stack.push(functionName +": " +command+" "+variable); //process the define command
			
		}
		else if (command == "call")
		{
			stack.push("Hello, World"); //to keep track of which function is being used currently
									    //(will help while clearing the stack after a function is finished)

			cout << "Calling " << variable << " from " << functionName << endl;
			
			processARequest(variable, linkedlist, stack); //the recursion goes here
		}
		else
		{
			string words="";
			if (stack.isEmpty())
			{
				cout << "The stack is empty" << endl;
			}
			else
			{
				cout << "PRINTING THE STACK TRACE:" << endl;
				strStack tempStack;
				
				while(!stack.isEmpty()) //to keep the stack intact, creating a temporary one
				{
					stack.pop(words);
					tempStack.push(words);
				}
				
				while(!tempStack.isEmpty())
				{
					tempStack.pop(words);
					stack.push(words);
					if (words!="Hello, World" )
						cout << words << endl; 
 				}
			}
		}
		ptr2 = ptr2->down;
	}

	string word="";
	while(!stack.isEmpty() && word!="Hello, World") //deleting the finished function's data from the stack
	{
		stack.pop(word);
	}
	cout << functionName << " is finished. Clearing the stack from it's data... " << endl;
    system("pause");
}

//to get a process request and its information, then to call the other process funciton to process wanted service
void processARequest(LinkedList &linkedlist, iQueue &iqueue, sQueue &squeue, strStack &stack)
{
	if (!iqueue.isEmpty()) 
	{
		instructor inst;
		cout << "Processing instructor's queue..." << endl;
		iqueue.dequeue(inst);
		string name = inst.name;
		string funcname = inst.func;
		int id = inst.id;

		cout << "Processing prof. " << name << "'s request (with id " << id 
			 << ") of service (function): " << endl << funcname << endl
			 << "----------------------------------------------------------------" << endl;

		//if instructors queue is not empty, process the next request
		processARequest(funcname, linkedlist, stack); 
		cout << "GOING BACK TO MAIN MENU" << endl;
	}
	else if (!squeue.isEmpty())
    {
		//if instructors queue is empty and student’s not, then process the next student request
		cout << "Instructors queue is empty. Proceeding with student's queue..." << endl;
		
		string funcname, name;
		int id;
		squeue.dequeue(funcname, name, id);
		cout << "Processing " << name << "'s request (with id " << id 
			 << ") of service (function): " << endl << funcname << endl
			 << "----------------------------------------------------------------" << endl;

		processARequest(funcname, linkedlist, stack);
		cout << "GOING BACK TO MAIN MENU" << endl;
	}
	else
	{
		//if both instructors students queue is empty, go to back to main menu
		cout << "Both instructor's and student's queue is empty." << endl << "No request is processed." << endl
			 << "GOING BACK TO MAIN MENU" << endl;
	} 
}

int main()
{
	LinkedList linkedlist; //linked list for the services
	iQueue iqueue(5); //instructors queue
	sQueue squeue; //students queue
	strStack stack; // stack for keep track of the called service's commands

	getFile(linkedlist); //getting input from the user and processing it

	cout << "------------------------------------------------------------------" << endl;
	cout << "PRINTING AVAILABLE SERVICES (FUNCTIONS) TO BE CHOSEN FROM THE USER" << endl;
	cout << "------------------------------------------------------------------" << endl;
	
	linkedlist.PrintList();

	while (true)
	{
		cout << endl;
		cout <<"**********************************************************************" << endl
			 <<"**************** 0 - EXIT PROGRAM                        *************" << endl
			 <<"**************** 1 - ADD AN INSTRUCTOR SERVICE REQUEST   *************" << endl
			 <<"**************** 2 - ADD A STUDENT SERVICE REQUEST       *************" << endl
			 <<"**************** 3 - SERVE (PROCESS) A REQUEST           *************" << endl
			 <<"**********************************************************************" << endl;
		cout << endl;
		int option;
		cout << "Pick an option from above (int number from 0 to 3): ";
		cin >> option;
		switch (option)
		{
			case 0:
				cout << "PROGRAM EXITING ... " << endl; 
				system("pause");
				exit(0);
			case 1:
				addInstructorRequest(iqueue);
				break;
            case 2:
				addStudentRequest(squeue);
				break;
			case 3:
				processARequest(linkedlist, iqueue, squeue, stack);
				break;
			default:
				cout << "INVALID OPTION!!! Try again" << endl;
		}//switch
	}//while (true)

	return 0;
}
