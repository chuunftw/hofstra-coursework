#include"LinkedList.h"
#include <iostream>
using namespace std;


LinkedList::LinkedList()
{
	first =0;
}


void LinkedList::insert(DataType data)
{
	Link *newLink = new Link(data,first);
	this ->first = newLink;
}

void LinkedList::deleteByPos(int pos)
{
	if(pos<0)
	{
		cerr<<"Invalid Position" << endl;
		return;
	}

	if(pos==0)
	{
		Link *temp;
		temp = first->getNext();
		delete first;
		first = temp;
		return;
	}

	Link *temp = first;
	for (int i=0;i<pos-1;i++)
	{
		temp = temp->getNext();
		if(temp ==0)
		{
			cerr << "Invalid"<<pos<<endl;
			return;
		}
	}
	Link *ptr2Del = temp ->getNext();
	temp ->setNext(ptr2Del->getNext());
	delete ptr2Del;
        return;
}

void LinkedList :: insert(DataType data, int pos)
{
	//sanity check on pos
	//Find pred pos
	// Create new node / link
	// Connect things

	//cout << "Test1"<<endl;

	Link *temp =first;
	if(pos<0)
	{
		cerr<<"Position not valid"<<endl;
		return;
	}

        else if (pos == 0) {
           insert(data);
           return;
        }

	//cout << "Test2" << endl;

	for (int i =0;i<pos-1;i++)
	{

		//cout<< "Test3 " << i<<endl;

		temp = temp->getNext();
		if(temp==0)
		{
			cerr<<"Invalid!"<<pos<<endl;
			return;
		}
	}

	Link *newLink = new Link(data,temp->getNext());
        temp->setNext(newLink);
}
void LinkedList::insertAtEnd(DataType data) {
	//first check if list is empty and if so insert at beginning 

	if(isEmpty())
	{
		insert(data);
		return;
	}

	//traverse list and find the end
	Link *temp = first;
	while(temp!=0 && temp->getNext()!=0)
	{
		temp = temp ->getNext();
	}
	//we are pointing to the last element in the list
	//creat a new elemetn and make it point to null
	Link *newLink = new Link(data,0);
	//make the provious last element point to new last element
	temp-> setNext(newLink);

}


void LinkedList::display()
{

	Link *temp=first;
	while(temp!=0)
	{
		cout << temp ->getData()<<" ";
		temp = temp->getNext();
	}
	cout << endl;
}

LinkedList::~LinkedList()
{
	Link *temp = first;
	while(temp!=0)
	{
		Link *ptr2Del = temp;
		temp = temp->getNext();
		delete ptr2Del;
	}
}

