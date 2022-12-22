#include <iostream>
#include <string>
#include <vector>
#include "LinkedList.h"

using namespace std;

LinkedList::LinkedList()
{
	head = NULL;
}

LinkedList::~LinkedList()
{
	fnode *ptr = head;

	while(ptr != NULL)
	{
		cnode *ptr2 = ptr->commands;
		while(ptr2 != NULL)
		{
			cnode *temp2 = ptr2->down;
			delete ptr2;
			ptr2 = temp2;
		}
		fnode *temp = ptr->next;
		delete ptr;
		ptr = temp;
	}

}

void LinkedList::ServiceList(string funcname, string command)
{
	fnode *ptr = head;
	
	fnode *next = NULL;
	cnode *down = NULL;
	cnode *commands = NULL;

	if (head == NULL)
	{
		commands = new cnode(command, down);
		head = new fnode(funcname, next, commands);
	}
	else
	{
		while(ptr->next != NULL && ptr->funcname != funcname) //add new function list to the end
		{
			ptr = ptr->next;
		}
		if (ptr->funcname == funcname)
		{
			cnode *ptr2 = ptr->commands;
			if (ptr2 == NULL)
			{
				ptr2 = new cnode(command, down);
			}
			while( ptr2->down != NULL)
			{
				ptr2 = ptr2->down;
			}
			ptr2->down = new cnode(command, down);
		}
		else if (ptr->next == NULL)
		{
			commands = new cnode(command, down);
			ptr->next = new fnode(funcname, next, commands);
		}
	}
}

void LinkedList::PrintList()
{
	fnode *ptr = head;

	while(ptr != NULL)
	{
		cout << endl << ptr->funcname << ":" << endl;
		cnode *ptr2 = ptr->commands;
		while(ptr2->down != NULL)
		{
			cout << ptr2->cname << ", " ;
			ptr2 = ptr2->down;
		}
		if (ptr2->down == NULL)
		{
			cout << ptr2->cname << "." << endl;
		}
		ptr = ptr->next;
	}

}

fnode* LinkedList::gethead()
{
	return head;
}