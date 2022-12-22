#include <iostream>
#include <vector>
#include <string>
#include "iqueue.h"
using namespace std;

//taken from lecture notes and changed

//*****************************************
// Constructor - creates an empty queue   *
// with given number of elements          *
//*****************************************

iQueue::iQueue(int s)
{
	queueArray = new vector<instructor>(s);
	queueSize = s;
	front = -1;
	rear = -1;
	numItems = 0;
}

iQueue::~iQueue()
{
	delete queueArray;
}

//********************************************
// Function enqueue inserts the value in num *
// at the rear of the queue.                 *
//********************************************
void iQueue::enqueue(string func, string name, int id)
{
	instructor inst = instructor(func, name,id);

	if (isFull())
    { 
         //cout << "The queue is full. " << word << " not enqueued\n";
    }
	else
	{
		// Calculate the new rear position circularly.
		rear = (rear + 1) % queueSize;
		// Insert new item.
		(*queueArray)[rear] = inst;
		// Update item count.
		numItems++;
	}
}

//**********************************************
// Function dequeue removes the value at the   *
// front of the queue, and copies it into num. *
//**********************************************
void iQueue::dequeue(instructor &inst)
{
	if (isEmpty())
	{
       cout << "Attempting to dequeue on empty queue, exiting program...\n";
       exit(1);
    }
	else
	{
		// Move front.
		front = (front + 1) % queueSize;
		// Retrieve the front item.
		inst = (*queueArray)[front];
		// Update item count.
		numItems--;
	}
}

//*********************************************
// Function isEmpty returns true if the queue *
// is empty, and false otherwise.             *
//*********************************************
bool iQueue::isEmpty() const
{
	if (numItems > 0)
		return false;
	else
		return true;	
}

//********************************************
// Function isFull returns true if the queue *
// is full, and false otherwise.             *
//********************************************
bool iQueue::isFull() const
{
	if (numItems < queueSize)
		return false;
	else
		return true;
}

//*******************************************
// Function clear resets the front and rear *
// indices, and sets numItems to 0.         *
//*******************************************
void iQueue::clear()
{
	front =  - 1;
	rear =  - 1;
	numItems = 0;
}

