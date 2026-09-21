#include <iostream>
using namespace std;

#include "LinkedStack.h"

int main()
{
	int N = 10;
	//LOOP TO ADD ELEMENTS
	LinkedStack ls;
	for(int i =0;i<N;i++)
	{
		ls.push(i);
	}
	//LOOP TO REMOVE ELEMENTS
	while(!ls.isEmpty())
	{
		cout<<ls.top()<<" " <<endl;
		ls.pop();
	}

}
