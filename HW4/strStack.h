#ifndef STRSTACK_H
#define STRSTACK_H

using namespace std;

//a string stack to store define commands
class strStack
{
private:
	vector<string> *stackVector;
	int stackSize;
	int top;

public:
	strStack(); //constructor
	~strStack(); //destructor

	void push(string);
	void pop(string &);
	bool isFull(void);
	bool isEmpty(void);
	void makeEmpty();
};
	
#endif