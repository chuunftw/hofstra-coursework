// In the VS Code terminal, open this file's folder and run:
// Compile: g++ -std=c++17 -Wall -Wextra -pedantic 01_pointer_to_pointer.cpp -o 01_pointer_to_pointer.exe
// Run:     .\01_pointer_to_pointer.exe
// Each lesson has its own main(); compile one .cpp file at a time.

#include <iostream>
using namespace std;

// Study guide section 1: the remaining pointer-to-pointer example.
// Continue with 02_pointers_and_references.cpp for ordinary pointers and references.
int main() {
    int x = 2;
    int* p = &x;    // p stores the address of an integer.
    int** pp = &p;  // pp stores the address of a POINTER variable.

    cout << "1. Follow the addresses\n";
    cout << "x = " << x << '\n';           // 2
    cout << "*p = " << *p << '\n';         // 2
    cout << "**pp = " << **pp << '\n';     // 2
    // pp -> p -> x. Each * follows one pointer.
    cout << "pp == &p: " << boolalpha << (pp == &p) << '\n'; // true
    cout << "*pp == p: " << (*pp == p) << '\n';              // true

    cout << "\n2. Change x through two pointers\n";
    **pp = 9;
    cout << "x = " << x << '\n'; // 9

    cout << "\n3. Change p through pp\n";
    int y = 20;
    *pp = &y;  // *pp accesses p itself, so this changes p's target.
    cout << "*p = " << *p << ", x = " << x << '\n'; // 20, 9
    // int** wrong = &&x; // Not how to take the address of an address.
    return 0;
}
