#include<iostream>
#include<string>
using namespace std;


class myClass
{
public:
	myClass(string name = "NoName")
	{
		this-> name = name;
		cout <<"Default Constructor called for:" << name<<endl;;
	}

	~myClass()
        {
                cout <<"Destructor called for:" << name<<endl;
        }

private:
	string name;
};


void myFunc()
{
	myClass mc("mc myFunc");
	cout <<"Inside my function... " << endl;

	{
		myClass mc2("mc2 myFunc");
	}


}


int main()
{
	myClass mc("mc main");
	cout << "Inside main function... " << endl;
	myFunc();
	return 0;
}
