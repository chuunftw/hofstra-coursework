#include "Student.h"
#include <iostream>
using namespace std;
//default constructor
#include<string.h>
Student :: Student()
{
	strcpy(fname,"Unknown");
//	fname = "Unknown";
	strcpy(lname,"Unknown");
//	lname = "Unknown";
	age=0;
	gradYear =0; 
	id =0;
}


int Student :: getAge()
{
	return age;
}

void Student::setAge(short age)
{

	if((age<= 100) && (age<=15)){
  	this->age = age;

	}
}

void Student :: readStudent()

{
	cout << "Please enter student info (First / Last name, age, graduation year, ID)" << endl;
	cin >> fname >> lname>> age >> gradYear >> id;

}
void Student :: displayStudent()
{

	cout << fname<< " " << lname<< " " << age << " " << gradYear << " "  << id<< endl;

}
