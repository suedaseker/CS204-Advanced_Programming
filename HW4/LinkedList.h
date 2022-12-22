#ifndef _LINKEDLIST_H
#define _LINKEDLIST_H

using namespace std;

//a node structure for commands linked list of the services
struct cnode
{
	string cname;
	cnode *down;

	cnode::cnode(string name, cnode *d = NULL)
		  :cname(name), down(d) {}
};

//a node structure for services' linked list
struct fnode
{
	string funcname;
	fnode *next;
	cnode *commands;

	//constructor
	fnode::fnode(string fname, fnode *n = NULL, cnode *c= NULL)
		  :funcname(fname), next(n), commands(c) {}
};

class LinkedList
{
private:
	fnode *head;

public:
	LinkedList(); //constructor
	~LinkedList(); //destructor 

	void ServiceList(string, string);
	void PrintList();
	fnode* gethead();
};

#endif