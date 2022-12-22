#ifndef SQUEUE_H
#define SQUEUE_H

using namespace std;

//a node structure to store the student's information
struct QueueNode
{
	string name, func;
	int id;
	QueueNode *next;

	QueueNode::QueueNode(string f, string s, int id, QueueNode *ptr = NULL)
			  :func(f), name(s), id(id), next(ptr) {}
};

class sQueue
{
private:
	//These track the front and rear of the queue.
	QueueNode *front;
	QueueNode *rear;	
public:
	sQueue(); //constructor
	~sQueue(); //destructor
	
	void enqueue(string f, string s, int id);
	void dequeue(string &, string &, int &);
	bool isEmpty() const;     
	void clear();
};
#endif