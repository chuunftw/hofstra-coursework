#include "Student.h" 
#include <iostream>
using namespace std;

int main()
{
	Student s;
	cout << "Student values after constructor call" << endl;
	s.readStudent();
	s.displayStudent();
	cout << "Student values after readStudent call" <<endl;
	s.setAge(234);
	s.displayStudent();
	return 0;
}
