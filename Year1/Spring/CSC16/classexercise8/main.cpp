#include <iostream>
using namespace std;

#include "LinkedList.h"

int main()
{
	LinkedList manuelL;
	//add N elements to list
	const int N = 10;
	for(int i =0;i<N;i++)
	{
		manuelL.insertAtEnd(i);

	}
	manuelL.display();

	manuelL.insert(999,3);

	manuelL.display();

	manuelL.deleteByPos(3);

	manuelL.display();

	return 0;
}
