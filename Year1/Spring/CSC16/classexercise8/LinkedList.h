#ifndef LINKED_LIST_H
#define LINKED_LIST_H
#include "link.h"

class LinkedList
{
	public:
	LinkedList();
	~LinkedList();
	bool isEmpty() { return first == 0; }
	void insert(DataType data);
	void deleteByPos(int pos);
	void insertAtEnd(DataType data);
	void insert(DataType data, int pos);
	void display();
private:
	Link *first;
};
#endif //LINKED_LIST_H
