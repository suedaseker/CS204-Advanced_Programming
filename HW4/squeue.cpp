#include <iostream>
#include <string>
#include "sQueue.h"
using namespace std;

//taken from lecture notes and changed

//************************************************
// Constructor. Generates an empty queue         *
//************************************************
sQueue::sQueue()
{
	front = NULL;
	rear = NULL;   
	#ifdef _DEBUG
		cout << "An empty queue has been created\n";
	#endif
}

sQueue::~sQueue()
{
	QueueNode *ptr = front;

	while(ptr != rear)
	{
		QueueNode *temp = ptr;
		delete ptr;
		ptr = temp;
	}
	delete ptr;
}

//********************************************
// Function enqueue inserts the value in num *
// at the rear of the queue.                 *
//********************************************
void sQueue::enqueue(string func, string student, int id)
{       
	if (isEmpty())   //if the queue is empty
	{	//make it the first element
		front = new QueueNode(func,  student,  id);
		rear = front;
	}
	else  //if the queue is not empty
	{	//add it after rear
		rear->next = new QueueNode(func,  student,  id);
		rear = rear->next;
	} 
	#ifdef _DEBUG
		//cout << word << " enqueued\n";
	#endif
}

//**********************************************
// Function dequeue removes the value at the   *
// front of the queue, and copies it into num. *
//**********************************************
void sQueue::dequeue(string &func, string &name, int &id)
{
	QueueNode *temp;
	if (isEmpty())
	{
		cout << "The student queue is empty";
	}
	else //if the queue is not empty
	{	//return front's value, advance front and delete old front
		name = front->name;
		func = front->func;
		id = front->id;
		temp = front;
		front = front->next;
		delete temp;      
	}
}

//*********************************************
// Function isEmpty returns true if the queue *
// is empty, and false otherwise.             *
//*********************************************
bool sQueue::isEmpty() const
{
	if (front == NULL)
		return true;
	else 
		return false;
}

//********************************************
// Function clear dequeues all the elements  *
// in the queue.                             *
//********************************************
void sQueue::clear()
{
	string func, name;  
	int id;// Dummy variable for dequeue

	while(!isEmpty())
		dequeue(func, name, id); //delete all elements
	#ifdef _DEBUG
		cout << "queue cleared\n";
	#endif
}