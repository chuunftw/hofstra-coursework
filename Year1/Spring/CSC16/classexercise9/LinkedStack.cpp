#include "LinkedStack.h"

LinkedStack :: LinkedStack()
{
	topPtr = 0;
}

void LinkedStack :: push(DataType data)
{
	Link *newLink = new Link(data, topPtr);
	topPtr = newLink;
}

void LinkedStack::pop()
{
	//save top next pointer
	Link *temp = topPtr ->getNext();
	delete topPtr;
	//make top point to old next
	topPtr = temp;
}

DataType LinkedStack::top()
{
	return topPtr ->getData();
}

LinkedStack :: ~LinkedStack()
{
	while(!isEmpty())
	{
		pop();
	}
}
