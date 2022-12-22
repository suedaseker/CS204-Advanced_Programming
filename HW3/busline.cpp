#include <iostream>
#include <string>
#include <vector>
//#include <fstream>
//#include <sstream>
#include "busline.h"
using namespace std;

string all = "all"; //only for PrintBusLines function

LinkedList::LinkedList()
{
	head = NULL;
}

//to create a linked list for the bus lines
void LinkedList::BusLineList(string &line_name, string &stop_name, const int &endorbeginning)
{
	busLine *ptr = head; //loop variable

	busLine *n = NULL;
	busStop *bstops = NULL;
	busStop *L = NULL;
	busStop *R = NULL;

	//if the list is empty, assigning information to head
	if (head == NULL)
	{
		bstops = new busStop(stop_name, L, R);
		head = new busLine(line_name, n, bstops);
	}
	//add to end
	else
	{
		if (endorbeginning == 1)
		{
			while (ptr->next != NULL)
			{
				ptr = ptr->next;
			}
			bstops = new busStop(stop_name, L, R);
			ptr->next = new busLine(line_name, n, bstops);
		}
		//add to beginning
		if (endorbeginning == 0)
		{
			bstops = new busStop(stop_name, L, R);
			head = new busLine(line_name, n, bstops);
			head->next = ptr;
		}
	}
}

//to create a doubly linked list for bus stops
void LinkedList::BusStopList(string &line_name, string &stop_name)
{
	busLine *ptr = head; //loop variable

	//finding the wanted bus line to add the stops
	while (ptr->busLineName != line_name)
	{
		ptr = ptr->next;
	}

	busStop *ptr2 = ptr->busStops; //loop variable

	while (ptr2->right != NULL)
	{
		ptr2 = ptr2->right;
	}

	busStop *L = ptr2;
	busStop	*R = NULL;
	ptr2->right = new busStop(stop_name, L, R); //adding a new bus stop
}

bool LinkedList::consistencyCheck()
{
	busLine* currBL = head;
	while(currBL) 
	{
		busStop* currBS = currBL->busStops;
		while(currBS) 
		{
			busStop* rightBS = currBS->right;
			if(rightBS && rightBS->left != currBS) 
			{
				cout << "Inconsistency for " << currBL->busLineName << " " << currBS->busStopName << endl;
				return false;
			}
			currBS = currBS->right;
		}
		currBL = currBL->next;
	}
	return true;
}

//while adding a bus line with stops, checks if the stop name is already given
bool LinkedList::IsInVector(vector<string> &bus_stops, string &stop_name)
{
	for (int i = 0; i < bus_stops.size(); i++)
	{
		if (bus_stops[i] == stop_name)
		{
			return true;
		}
	}
	return false;
}

//checking the bus line linked list to see if the wanted line is on the list
bool LinkedList::IsInLineList(string &line_name)
{
	busLine *ptr = head; //loop variable

	while (ptr != NULL && ptr->busLineName != line_name)
	{
		ptr = ptr->next;
	}
	if (ptr != NULL && ptr->busLineName == line_name)
	{
		return true;
	}
	
	return false;
}

//to check if the stop name is in a certain line
bool LinkedList::IsInLine(string &line_name, string &stop_name)
{
	busLine *ptr = head; //loop variable
	
	while (ptr != NULL && ptr->busLineName != line_name)
	{
		ptr = ptr->next;
	}
	if (ptr != NULL && ptr->busLineName == line_name)
	{
		busStop *ptr2 = ptr->busStops;
		while (ptr2 != NULL && ptr2->busStopName != stop_name)
		{
			ptr2 = ptr2->right;
		}
		if (ptr2 != NULL && ptr2->busStopName == stop_name)
		{
			return true;
		}
	}
	
	return false;
}

//while finding path, to see if the given stop is on the table
bool LinkedList::IsInTable(string &stop_name)
{
	busLine *ptr = head; //loop variable

	while (ptr != NULL)
	{
		busStop *ptr2 = ptr->busStops;
		while (ptr2 != NULL && ptr2->busStopName != stop_name)
		{
			ptr2 = ptr2->right;
		}
		if (ptr2 != NULL && ptr2->busStopName == stop_name)
		{
			return true;
		}

		ptr = ptr->next;
	}

	return false;
}

//to print the bus lines
void LinkedList::printBusLines(string &line_name)
{
	busLine *ptr = head; //loop variable

	//printing all the bus lines
	if (line_name == "all")
	{
		while (ptr != NULL)
		{
			cout << ptr->busLineName << ": ";
			busStop *ptr2 = ptr->busStops;
			while (ptr2->right != NULL)
			{
				cout << ptr2->busStopName << " <-> ";
				ptr2 = ptr2->right;
			}
			cout << ptr2->busStopName << endl;
			ptr = ptr->next;
		}
	}
	//printing only the wanted bus line
	else
	{
		while (ptr != NULL && ptr->busLineName != line_name)
		{
			ptr = ptr->next;
		}
		busStop *ptr2 = ptr->busStops;
		if (ptr != NULL && ptr->busLineName == line_name)
		{
			cout << ptr->busLineName << ": ";
	
			while (ptr2->right != NULL)
			{
				cout << ptr2->busStopName << " <-> ";
				ptr2 = ptr2->right;
			}
			cout << ptr2->busStopName << endl;
		}
	}
}

//to add a bus line to the linked list
void LinkedList::addBusLine()
{
	string busline, busstop;
	vector<string> bstop_names; //a vector to store the bus stop names
	cout << "Enter the name of the new bus line (0 for exit to main menu)." << endl;
	cin >> busline;
	while (IsInLineList(busline)) //if the given bus line name already exists, ask for a valid one
	{
		cout << "Bus line already exists: enter a new one (0 for exit)" << endl;
		cin >> busline;
	}

	cout << "Enter the name of the next bus stop (enter 0 to complete)" << endl;
	cin >> busstop;
	while (busstop != "0") //getting bus stop names untill the user enters 0 to stop
	{
		if (!IsInVector(bstop_names, busstop))
		{
			bstop_names.push_back(busstop);
			cout << "Enter the name of the next bus stop (enter 0 to complete)" << endl;
			cin >> busstop;
		}
		else
		{
			cout << "Bus stop already exists in the line" << endl;
			cout << "Enter the name of the next bus stop (enter 0 to complete)" << endl;
			cin >> busstop;
		}
	}
	if (bstop_names.size() == 0) //if no stop name is given, print an error message
	{
		cout << "You are not allowed to add an empty bus line" << endl;
		return;
	}

	cout << "The bus line information is shown below" << endl;
	cout << busline << ": ";
	int i = 0;
	while (i < bstop_names.size()-1)
	{
		cout << bstop_names[i] << " <-> ";
		i++;
	}
	cout << bstop_names[i] << endl;
	string answer;
	cout << "Are you sure? Enter (y/Y) for yes (n/N) for no?" << endl;
	cin >> answer;
	cout << endl;
	
	if (answer == "Y" || answer == "y") //if user decides to add the bus line, now adding them to the linked list
	{
		BusLineList(busline, bstop_names[0], 0);
		for (int i = 1; i < bstop_names.size(); i++)
		{
			BusStopList(busline, bstop_names[i]);
		}
	
		printBusLines(all);
	}
} 

//to add a bus stop to an existing bus line
void LinkedList::addBusStop()
{
	string busline;
	cout << "Enter the name of the bus line to insert a new bus stop (0 for main menu)" << endl;
	cin >> busline;
	if (busline == "0")
	{
		return;
	}
	if (IsInLineList(busline) == false) //if there is no bus line with given name, go to menu
	{
		cout << "Bus line cannot be found. Going back to previous menu." << endl;
		return;
	}
	cout << "The bus line information is shown below" << endl;
	printBusLines(busline);

	string busstop; 
	cout << "Enter the name of the new bus stop" << endl;
	cin >> busstop;
	if (IsInLine(busline, busstop))
	{
		cout << "Bus stop already exists. Going back to previous menu." << endl;
		return;
	}
	string pre_stop;
	cout << "Enter the name of the previous bus stop to put the new one after it"
		 << "(0 to put the new one as the first bus stop)" << endl;
	cin >> pre_stop;

	string pre_stop2;
	//if the stop is not in the line, wanting the correct name untill user enters 0 to stop
	while (!IsInLine(busline, pre_stop) && pre_stop != "0" && pre_stop2 != "0")
	{
		cout << "Bus stop does not exist. Typo? Enter again (0 for main menu)" << endl;
		cin >> pre_stop2;
		pre_stop = pre_stop2;
	}
	if (pre_stop2 == "0")
	{
		return;
	}
	
	busLine *ptr = head; //loop variable

	while (ptr != NULL && ptr->busLineName != busline)
	{
		ptr = ptr->next;
	}
	//adding the bus stop to given bus line
	if (ptr != NULL && ptr->busLineName == busline)
	{
		busStop *ptr2 = ptr->busStops;

		
		if (pre_stop == "0") //if 0 is given for the previous stop, adding the bus stop to the beginning
		{
			ptr2->left= new busStop(busstop, NULL, ptr2);
			ptr->busStops = ptr2->left;
		}
		else //finding the previous bus stop to insert the new bus stop after it
		{
			while (ptr2 != NULL && ptr2->busStopName != pre_stop)
			{
				ptr2 = ptr2->right;
			}
			if (ptr2 != NULL && ptr2->right != NULL && ptr2->busStopName == pre_stop)
			{
				busStop *new_stop = new busStop(busstop, ptr2, ptr2->right);
				ptr2->right = new_stop;
				new_stop->right->left = new_stop;
			}
			else if (ptr2 != NULL && ptr2->busStopName == pre_stop)
			{
				ptr2->right = new busStop(busstop, ptr2, NULL);
			}
		}
	}
	cout << endl;
	printBusLines(all);
}

//to only delete a line (separate function to also use in deleteBusStop function)
void LinkedList::deleteline(string &line_name)
{
	busLine *ptr = head; //loop variable

	//if head is the wanted bus line, deleting it
	if (ptr->busLineName == line_name)
	{
		busStop *ptr2 = ptr->busStops;

		while(ptr2->right != NULL)
		{
			busStop *temp = ptr2;
			ptr2 = ptr2->right;
			ptr2->left = NULL;
			ptr->busStops = ptr2;
			delete temp;
		}
		delete ptr2;

		head = ptr->next;
		delete ptr;
	}
	else
	{
		while (ptr->next != NULL && ptr->next->busLineName != line_name)
		{
			ptr = ptr->next;
		}
		if (ptr->next != NULL && ptr->next->busLineName == line_name)
		{
			busStop *ptr2 = ptr->next->busStops;

			while(ptr2->right != NULL)
			{
				busStop *temp = ptr2;
				ptr2 = ptr2->right;
				ptr2->left = NULL;
				ptr->next->busStops = ptr2;
				delete temp;
			}
			delete ptr2;

			busLine *temp = ptr->next;
			ptr->next = ptr->next->next;
			delete temp;
		}
		else if (ptr->next == NULL && ptr->next->busLineName == line_name)
		{
			busStop *ptr2 = ptr->next->busStops;

			while(ptr2->right != NULL)
			{
				busStop *temp = ptr2;
				ptr2 = ptr2->right;
				ptr2->left = NULL;
				ptr->next->busStops = ptr2;
				delete temp;
			}
			delete ptr2;

			delete ptr->next;
			ptr->next = NULL;
		}
	}
}

//to delete a wanted bus line
void LinkedList::deleteBusLine()
{
	string busline;
	cout << "Enter the name of the bus line to delete" << endl;
	cin >> busline;
	if (IsInLineList(busline) == false)
	{
		cout << "Bus line cannot be found. Going back to the previous (main) menu." << endl;
		return;
	}

	deleteline(busline);

	cout << endl;
	printBusLines(all);
}

//to delete a bus stop
void LinkedList::deleteBusStop()
{
	string busline;
	cout << "Enter the name of the bus line to delete a new bus stop (0 for main menu)" << endl;
	cin >> busline;
	if (IsInLineList(busline) == false)
	{
		cout << "Bus line cannot be found. Going back to the previous (main) menu." << endl;
		return;
	}

	busLine *ptr = head; //loop variable

	while (ptr != NULL && ptr->busLineName != busline)
	{
		ptr = ptr->next;
	}
	if (ptr != NULL && ptr->busLineName == busline)
	{
		cout << "The bus line information is shown below" << endl;
		printBusLines(busline);
		string busstop;
		cout << "Enter the name of the bus stop to delete (0 for main menu)" << endl;
		cin >> busstop;
		while (!IsInLine(busline, busstop) && busstop != "0")
		{
			cout << "Bus stop cannot be found. Enter the name of the bus stop to delete (0 for main menu)" << endl;
			cin >> busstop;
		}
		if (busstop == "0")
		{
			return;
		}

		busStop *ptr2 = ptr->busStops; //loop variable for doubly linked list

		while(ptr2 != NULL && ptr2->busStopName != busstop)
		{
			ptr2 = ptr2->right;
		}
		if (ptr2 != NULL && ptr2->busStopName == busstop && ptr2->left != NULL && ptr2->right != NULL)
		{
			busStop *temp = ptr2;
			ptr2 = ptr2->right;
			temp->left->right = ptr2;
			ptr2->left = temp->left;
			delete temp;
		}
		//if we're deleting the last stop on the bus line, deleting the bus line
		else if (ptr2->busStopName == busstop && ptr2->left == NULL && ptr2->right == NULL)
		{
			deleteline(ptr->busLineName);
		}
		else if (ptr2->busStopName == busstop && ptr2->left == NULL)
		{
			busStop *temp = ptr2;
			ptr2 = ptr2->right;
			ptr->busStops = ptr2;
			ptr2->left = NULL;
			delete temp;
		}
		else if (ptr2->busStopName == busstop && ptr2->right == NULL)
		{
			ptr2->left->right = NULL;
			delete ptr2;
		}
	}

	cout << endl;
	printBusLines(all);
}

//only finds a path if there is no interchange along the way
void LinkedList::pathfinder()
{
	string from, to;
	cout << "Where are you now?" << endl;
	cin >> from;
	if (!IsInTable(from))
	{
		cout << "Bus stop does not exist in the table. Going back to previous menu." << endl;
		return;
	}
	cout << "Where do you want to go?" << endl;
	cin >> to;
	if (!IsInTable(to))
	{
		cout << "Bus stop does not exist in the table. Going back to previous menu." << endl;
		return;
	}
	busLine *ptr = head; //loop variable

	while (ptr != NULL)
	{
		busStop *ptr2 = ptr->busStops; //loop variable to find current bus stop
		int ptr2count = 0;
		while (ptr2 != NULL && ptr2->busStopName != from)
		{
			ptr2 = ptr2->right;
			ptr2count ++;
		}
		if (ptr2 != NULL && ptr2->busStopName == from)
		{
			busStop *ptr3  = ptr->busStops; //loop variable to find the bus stop user wants to go
			int ptr3count = 0;
			while (ptr3 != NULL && ptr3->busStopName != to)
			{
				ptr3 = ptr3->right;
				ptr3count ++;
			}
			if (ptr3 != NULL && ptr3->busStopName == to)
			{
				cout << "You can go there by " << ptr->busLineName << ": ";
				while (ptr2->busStopName != ptr3->busStopName)
				{
					cout << ptr2->busStopName << "->";
					//if the current bus stop is before the destination on the table, moving to right on the linked list
					if (ptr2count < ptr3count)
					{
						ptr2 = ptr2->right;
					}
					//if the current bus stop is after the destination on the table, moving to left on the linked list
					else
					{
						ptr2 = ptr2->left;
					}
				}
				cout << ptr3->busStopName << endl;
				return;
			}
		}
		ptr = ptr->next;
	}
	//if there is no path found, prints a message in the end
	cout << "Sorry no path from " << from << " to " << to << " could be found." << endl;
}

//to get input with appropriate messages and to call the recursive function
void LinkedList::pathfinder2()
{
	string from, to;
	cout << "Where are you now?" << endl;
	cin >> from; //start position
	if (!IsInTable(from)) //checking if the bus stop is valid
	{
		cout << "Bus stop does not exist in the table. Going back to previous menu." << endl;
		return;
	}

	cout << "Where do you want to go?" << endl;
	cin >> to; //end position
	if (!IsInTable(to)) //checking if the bus stop is valid
	{
		cout << "Bus stop does not exist in the table. Going back to previous menu." << endl;
		return;
	}

	vector<LineStop> myvector; //a vector to store found bus stops and their bus lines

	int counter = 0; //counts the number of paths just to see if there is any
	pathFinder(from, to, myvector, counter); //main recursive function

	if (counter == 0) //if no paths counted, print an appropriate message
	{ 
		cout << "Sorry no path from " << from << " to " << to << " could be found." << endl;
	}
}

//checks whether the given stop name is in the vector to prevent the repetetion of paths
bool find(LineStop stopName, vector<LineStop> myvector )
{
	for (int i = 0; i < myvector.size(); i++)
	{
		if (myvector[i].busStopName == stopName.busStopName)
		{
			return true;
		}
	}
	return false;
}

//improved path finder function which find all the possible paths for given current stop and a destination
void LinkedList::pathFinder(string start, string stop, vector<LineStop> myvector, int &counter)
{
	busLine *ptrLine = head; //loop variable

	if (start == stop) //means we found a possible path
	{
		counter++; //update counter in each path, we do not care about the count as long as it is bigger than 0

		//this part is for printing an existing path with line names
		string prevStop, prevLine;
		if (myvector.size() > 1)
		{
			string temp = myvector[1].busLineName;
			prevLine = myvector[0].busLineName; //set a prevline name to hold busline between busstops
			prevStop = myvector[0].busStopName;

			cout << "You can go there by " ;
			if (temp == prevLine)
			{
				cout << prevLine << ": " << prevStop;
			}
		}

		for (int k = 1; k < myvector.size(); k++)
		{
			string currLine = myvector[k].busLineName;
			if (prevLine == currLine)
			{
				prevStop = myvector[k].busStopName;
				cout << "->" << prevStop;
			}
			else
			{
				prevLine = currLine;
				cout << endl;
				cout << "                    " << prevLine << ": " << prevStop << "->" << myvector[k].busStopName;
				prevStop = myvector[k].busStopName; 
			}
		}
		cout << endl << endl;
		return; //end of function
	}
	else
	{
		while (ptrLine != nullptr) //search all the lines for a given start bus stop
		{ 
			busStop *ptrStop = ptrLine->busStops;
			while (ptrStop != nullptr) //search all the stops in a given bus line for the given start bus stop
			{ 
				if (ptrStop->busStopName == start)
				{ 
					if (ptrStop->right != nullptr)
					{
						LineStop tmp1(ptrLine->busLineName, ptrStop->right->busStopName); //create lineStop object for the start->right
						if (!find(tmp1, myvector)) //check whether the name of the object already in the vector
						{ 
							LineStop temp(ptrLine->busLineName, ptrStop->busStopName); 
							if (!find(temp, myvector))
							{
								myvector.push_back(temp); //push the start into vector if it is not already in it
							}
							myvector.push_back(tmp1); //push the start->right after pushing start
							
							pathFinder(ptrStop->right->busStopName, stop, myvector, counter); //recursive manner
							myvector.pop_back(); //pop_back the start->right (end point) to find different paths
						}
					}
					if (ptrStop->left != nullptr)
					{
						LineStop tmp2(ptrLine->busLineName, ptrStop->left->busStopName);
						if (!find(tmp2, myvector))
						{ 
							LineStop temp(ptrLine->busLineName, ptrStop->busStopName); 
							if (!find(temp, myvector)) //push the start into vector if it is not already in it
							{ 
								myvector.push_back(temp);
							}
							myvector.push_back(tmp2);

							pathFinder(ptrStop->left->busStopName, stop, myvector, counter); //recursive manner
							myvector.pop_back(); //pop_back the start->left (end point) to find different paths
						}
					}
				}
				ptrStop = ptrStop->right;
			}
			ptrLine = ptrLine->next;
		}
	}
}

void LinkedList::printMainMenu()
{
	cout << endl;
	cout <<"I***********************************************I"<<endl 
	<<"I 0 - EXIT PROGRAM                              I"<<endl
	<<"I 1 - PRINT LINES                               I"<<endl
	<<"I 2 - ADD BUS LINE                              I"<<endl
	<<"I 3 - ADD BUS STOP                              I"<<endl
	<<"I 4 - DELETE BUS LINE                           I"<<endl
	<<"I 5 - DELETE BUS STOP                           I"<<endl
	<<"I 6 - PATH FINDER                               I"<<endl 
	<<"I***********************************************I"<<endl 
	<<">>";
	cout << endl;
}

void LinkedList::processMainMenu()
{
	char input;
	do
	{
		if(!consistencyCheck()) 
		{
			cout << "There are inconsistencies. Exit." << endl; 
			return;
		}
		printMainMenu();
		cout << "Please enter your option" << endl; 
		cin >> input;
		switch (input) 
		{
			case '0':
				cout << "Thanks for using our program" << endl; 
				return;
			case '1': 
				printBusLines(all);
				break; 
			case '2':
				addBusLine(); 
				break;
			case '3': 
				addBusStop();
				break;
			case '4':
				deleteBusLine();
				break;
			case '5':
				deleteBusStop();
				break; 
			case '6':
				pathfinder2();
				break;
			default:
				cout << "Invalid option: please enter again" << endl; 
		}
	} while(true);
}