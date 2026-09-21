#include "Student.h"
#include <iostream>
using namespace std;

void readStudent(Student &s)

{
	cout << "Please enter student info (First / Last name, age, graduation year, ID)" << endl;
	cin >> s.fname >> s.lname>> s.age >> s.gradYear >> s.id;
	
}
void displayStudent(Student s)
{

	cout << s.fname<< " " << s.lname<< " " << s.age << " " << s.gradYear << " "  << s.id<< endl;

}
