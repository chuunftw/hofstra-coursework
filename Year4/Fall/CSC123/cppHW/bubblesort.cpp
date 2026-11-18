// g++ -std=c++17 bubblesort.cpp -o bubblesort.exe
// .\bubblesort.exe

#include<iostream>
#include<memory>
using namespace std;

template<typename T>  // MY BUBBLESORT PROCEDURE CAN SORT ANYTHING!
void bubblesort(T A[], int length) {
 for(int i=0;i<length-1;i++)
   for(int k=0;k<length-i-1;k++)
     {
       if (A[k+1] < A[k]) { //swap
         T temp = A[k];
         A[k] = A[k+1];
         A[k+1] = temp;
       }
     }
}//bubblesort

// but what about these?
struct roster {
 string class_name;
 string* students;  // pointer to heap-allocated array of student names
 unsigned int count; // number of students;

 roster(string n, std::initializer_list<string> R) { //constructor
   class_name = n;
   count = R.size();
   students = new string[count];  // allocates array on heap
   int i =0;
   for(string n:R) students[i++] = n;
 }
 ~roster() { if (students) delete[] students; }  // destructor

 // rosters are ordered by the count of the number of students
 bool operator <(roster& other) {
   return count < other.count;
 }

 // print roster
 friend ostream& operator <<(ostream& out, roster& r) {
   int i;
   out << "roster for " << r.class_name << ": ";
   for(i=0;i+1<r.count;i++) out << r.students[i] << ", ";
   if (i<r.count) out << r.students[i]; // last student without trailing ,
   out << endl;
   return out;
 }
};  // modify this struct only as instructed

int main() {
 int A[] = {4,3,6,1};
 bubblesort(A,4);
 for(int x:A) cout << x << " ";  cout << endl;  // BUBBLESORT WORKS!

 roster classes[] = {
   roster("csc123",{"Bilbo","Frodo","Gandolf"}),
   roster("csc16",{"Nev Erstudy","Isa Taparty"})
 };

 bubblesort(classes,2);
 for(roster& r:classes) cout << r;
 return 0;
}// main
