#include <iostream>
using namespace std;
#include "Queue.h"

int main()
{
	Queue q;
	const int N = 20;
	for (int i =0;i<N;i++)
		try
		{
			q.enqueue(i);
//			q.enqueue(i);
//			q.dequeue();
		}
		catch(int err)
		{
			cout << "Error caught: " << err << endl;
			q.dequeue();
		}
	q.display(cout);
	while(!q.empty())
	{
		cout << q.front()<<endl;
		q.dequeue();
	}
}

