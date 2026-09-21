#include <iostream>
#include <vector>
#include <ctime>
using namespace std;


/*template<C<T>,T>
void display(C<T> v)
{
	for(C<T>::iterator itr = v.begin();itr!=v.end();itr++)
	{
		cout << v[i]<< " "<<endl;
	}
}*/

int main()
{
	vector<int> v;
	const int N = 2147483648;
	clock_t beginTick = clock();
	for (int i =0;i<N;i++)
	{
		v.push_back(i);
	}
	clock_t endTick = clock();
	double runTime = (endTick - beginTick)/(double)CLOCKS_PER_SEC;
	cout << "Runtime: " << runTime<<" seconds" << endl;
	//display<vector<int>int>
	return 0;
}
