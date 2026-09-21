#include <iostream>
#include <fstream>
using namespace std;

int main()
{
	ifstream input1;
	input1.open("input.txt");
	string s;

	while (!input1.eof())	{
		
		cout<<"Input.txt contained: " << s << endl;
		input1>>s;
	}

return 0;
}
