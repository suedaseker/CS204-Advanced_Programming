#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include "strutils.h"

using namespace std;

//constructing a course node struct
struct cnode
{
	string Code, Name;
	vector<int> ID;
	cnode * next;

	//constructor
	 cnode::cnode(const string &code, const string &name, cnode *n = nullptr)
		  :Code(code), Name(name), next(n) {}
};

//checks if the given student ID is already in the vector of student ID's or not
bool IsInVector(const vector<int> &ID, int id)
{
	for (int i = 0; i < ID.size(); i++)
	{
		if (id == ID[i])
		{
			return true;
		}
	}
	return false;
}

//taken from 2020-21 CS201 Lecture Notes
//removes the student id that wants to drop the course from the sorted vector
void remove(vector<int> &a, int pos)
{
//pre: a is sorted
//post: original a[pos] removed, a is still sorted
   int k, lastIndex = a.size()-1;
   for (k=pos; k < lastIndex; k++)
       a[k] = a[k+1];

	a.pop_back(); //remove the last element of the array
}

//firstly creates a head for linked list then adds nodes to the linked list in order
//print parameter indicates if the function should display a message or not
cnode *AddCourseInOrder(cnode *head, const string &code, const string &name, const int &id, int print)
{
	cnode *ptr = head; //loop variable

	if ((head == NULL) || (name < head-> Name))        
    {
		head = new cnode(code, name, head);
		head->ID.push_back(id);
		return head;
	}

	while (ptr->next != NULL && ptr->next->Name <= name)
    {   
		ptr = ptr->next;
    }

	if (ptr->Name == name)
	{
		//if the ID vector is empty, directly push_back
		if (ptr->ID.size() == 0)
		{
			ptr->ID.push_back(id);
			if (print == 1)
			{
				cout << "Student with id " << id << " is enrolled to " << code << "." << endl;
			}
		}
		else
		{
			//if the student ID is already in the node's vector, gives an error message
			if (IsInVector(ptr->ID, id) && print == 1)
			{
				cout << "Student with id " << id << " already is enrolled to " << code << ". No action taken." << endl;
			}
			else
			{
				//inserting ID into the sorted vector
				int count = ptr->ID.size();
				ptr->ID.push_back(id);

				int i = count;
				while (i > 0 && ptr->ID[i-1] > id)
				{
					ptr->ID[i] = ptr->ID[i-1]; //shifting terms right until the correct insertion index
					i --; 
				}
				ptr->ID[i] = id;
				if (print == 1)
				{
					cout << "Student with id " << id << " is enrolled to " << code << "." << endl;
				}
			}
		}
	}
	else
	{
		//if the given course has no node, creating one and directly pushing back the first ID
		if (print == 1)
		{
			cout << code << " does not exist in the list of Courses. It is added up." << endl;
			cout << "Student with id " << id << " is enrolled to " << code << "." << endl;
		}
		ptr->next = new cnode(code, name, ptr->next);
		ptr->next->ID.push_back(id);
	}

	return head;
}

//deleting given ID's in an order from the vector
cnode *DropIdInOrder(cnode *head, const string &code, const string &name, const int &id)
{
	cnode *ptr = head; //loop variable

	//finding the wanted course from the linked list
	if (head != NULL && head->Name == name)
	{
		ptr = head;
	}
	else
	{
		while (ptr->next != NULL && ptr->next->Name != name)
		{   
			ptr = ptr->next;
		}
		ptr = ptr->next;
	}

	if (ptr == NULL)
	{
		cout << "The " << code << " course is not in the list, thus student with id " << id << " can't be dropped." << endl;
	}
	else
	{
		//finding the ID from the vector
		int pos = 0;
		for (int i = 0; i < ptr->ID.size()-1; i++)
		{
			if (ptr->ID[i] == id)
			{
				pos = i;
			}
		}
		//checking if the ID is in the vector
		if (IsInVector(ptr->ID, id) == false)
		{
			cout << "Student with id " << id << " is not enrolled to " << code << ", thus he can't drop that course." << endl;
		}
		//deleting ID in order with the "remove" function
		else
		{
			remove(ptr->ID, pos);
			cout << "Student with id " << id << " has dropped " << code << "." << endl;
		}
	}
	return head;
}

//before ending the program, the course nodes with less than 3 students will be deleted in order
cnode *DeleteCourse(cnode *head)
{
	//if head is deleted, checking the new head
	while (head->ID.size() < 3)
	{
		cnode *temp = head->next;
		delete head;
		head = temp;
	}

	cnode *ptr = head; //loop variable

	while (ptr->next != NULL)
	{
		if(ptr->next->ID.size() < 3)
		{
			cnode *temp = ptr->next;
			ptr->next = ptr->next->next;
			delete temp;
		}
		else
		{
			ptr = ptr->next; //to continue the loop
		}
	}
	return head;
}

//just before ending the program, we delete all of the linked list
void DeleteLinkedList(cnode *&head)
{
	cnode *ptr = head; //loop variable

	//deleting all the nodes one by one
	while (ptr->next != NULL)
	{
		cnode* temp = ptr->next;
		ptr->next = ptr->next->next;
		delete temp;
	}
	//lastly deleting the head
	delete head;
	head = NULL;
}

//displays the linked list with it's parameters
//print parameter indicates if the function should display a message or not
void DisplayList (cnode *head, int print)
{
	cnode * ptr = head; //loop variable

    while (ptr != NULL) 
	{
		//in the end of the program, displaying the courses that is going to be closed
		if (ptr->ID.size() < 3 && print == 1)
		{
			cout << ptr->Code << " " << ptr->Name << " ";
			for (int i = 0; i < ptr->ID.size(); i ++)
			{
					cout << ptr->ID[i] << " ";
			}
			ptr = ptr->next;
			cout << "-> This course will be closed" << endl;
		}
		else
		{
			cout << ptr->Code << " " << ptr->Name << ": ";
			for (int i = 0; i < ptr->ID.size(); i ++)
			{
					cout << ptr->ID[i] << " ";
			}
			ptr = ptr->next;
			cout << endl;
		}
	}
}

//takes input from the user
int GetChoice()
{
	int choice;
	cout << endl;
	cout << "Please select one of the choices:" << endl
		 << "1. Add to List" << endl
		 << "2. Drop from List" << endl
		 << "3. Display List" << endl
		 << "4. Finish Add/Drop and Exit" << endl;
	cin >> choice;
	return choice;
}

//calls the necessary function in order to chosen choices
void Choice(cnode *head)
{
	int choice = GetChoice();
	//if the choice is not 4, the loop continues and asks for a new choice
	while(true)
	{
		//choice 1, adds given ID's to the courses
		if (choice == 1)
		{
			int id;
			string word, code, name;
			cout << "Give the student ID and the course names and course codes that he/she wants to add:" << endl;    
			
			//getting the input according to their entities
			cin.get(); 
			getline(cin, word); 
			istringstream line(word);    
			while(!line.eof())
			{
				line >> word;
				if (word[0] >= '0' && word[0] <= '9')
				{
					int num = atoi(word);
					AddCourseInOrder(head, code, name, num, 1);
				}
				else
				{
					code = word;
					line >> name >> id;
					AddCourseInOrder(head, code, name, id, 1);
				}
			}
		}
		//choice 2, drops given ID's from the courses
		else if (choice == 2)
		{
			int id;
			string word, code, name;
			cout << "Give the student ID and the course names and course codes that he/she wants to drop:" << endl;  

			//getting the input according to their entities
			cin.get(); 
			getline(cin, word); 
			istringstream line(word);    
			while(!line.eof())
			{
				line >> word;
				if (word[0] >= '0' && word[0] <= '9')
				{
					int num = atoi(word);
					DropIdInOrder(head, code, name, num);
				}
				else
				{
					code = word;
					line >> name >> id;
					DropIdInOrder(head, code, name, id);
				}
			}

		}
		//choice 3, displays the linked list
		else if (choice == 3)
		{
			cout << "The current list of course and the students attending them:" << endl;
			DisplayList(head, 0);
		}
		//lastly choice 4, calls the function to delete the courses that has less than 3 students and ends the loop
		else
		{
			cout << "The add/drop period is finished. Printing the final list of courses and students attending them." << endl
				 << "NOTE: Courses with less than 3 students will be closed this semester." << endl;
			DisplayList(head, 1);
			DeleteCourse(head);
			return;
		}
		choice = GetChoice();
	}
}

int main()
{
	string textfile;
	cout << "Please enter file name: ";
	cin >> textfile;
	ifstream input;
	input.open(textfile.c_str());
	cout << "Successfully opened file " << textfile << endl;

	string code, name;
	int id;
	cnode *head = NULL;

	//reading the file and taking the inputs
	//creating the course nodes in order for the first time
	while (!input.eof())
	{
		input >> code >> name >> id;
		head = AddCourseInOrder(head, code, name, id, 0);
	}
	input.close();

	cout << "The linked list is created." << endl << "The initial list is:" << endl;
	DisplayList(head, 0);

	//gets choices from the user and does the necessary functions until the given choice is 4
	Choice(head);

	//delete all the linked list before the program ends
	DeleteLinkedList(head);

	system("pause");
	return 0;
}
