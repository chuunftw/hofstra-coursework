#ifndef LINKEDSTACK_H
#define LINKEDSTACK_H

#include "Link.h"
class LinkedStack
{
public:
	LinkedStack();
	bool isEmpty() { return topPtr ==0; }
	void push(DataType data);
	void pop();
	DataType top();
	~LinkedStack();

private:
	Link *topPtr;
};

#endif //LINKEDSTACK_H
