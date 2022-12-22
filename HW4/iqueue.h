#ifndef IQUEUE_H
#define IQUEUE_H

using namespace std;

//a struct to store the instructor's information
struct instructor
{
	string name, func;
	int id;

	instructor::instructor(string f = "", string n = "", int id = 0)
			   :func(f),name(n), id(id) {}
};

class iQueue
{
private:
	vector<instructor> *queueArray;
	int queueSize;  //capacity of queue
	int front;
	int rear;
	int numItems;  //# of elements currently in the queue
public:
	iQueue(int);  //constructor, parameter is capacity
	~iQueue(); //destructor

  	void enqueue(string, string, int); 
  	void dequeue(instructor &);
  	bool isEmpty() const; 
  	bool isFull() const;
  	void clear();  //removes all elements
};
#endif