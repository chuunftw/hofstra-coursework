#include<iostream>
using namespace std;

int main()
{
	char name[] = "James";
	cout << name << endl;
	
	int i = 0;
	while (name[i]!= 0)
	{
		cout << "index i is: " << i << " and value at i is: " << name[i] <<" ascii code is: " << (int)name[i]<<endl;
		i += 1;
	}
	cout << "index i is: " << i << " and value at i is: " << (int)name[i] << endl;
return 0;
}
