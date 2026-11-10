// In the VS Code terminal, open this file's folder and run:
// Compile: g++ -std=c++17 -Wall -Wextra -pedantic 04_loops_and_pointer_arithmetic.cpp -o 04_loops_and_pointer_arithmetic.exe
// Run:     .\04_loops_and_pointer_arithmetic.exe
// Each lesson has its own main(); compile one .cpp file at a time.

#include <iostream>
using namespace std;

// Study guide section 4.
int main() {
    int A[] = {1, 2, 3};
    cout << "1. Loop over copies\n";
    for (int x : A) {
        x += 2; // Only modifies the copy for this iteration.
    }
    for (int x : A) cout << x << ' ';
    cout << '\n'; // 1 2 3

    cout << "\n2. Loop over references\n";
    for (int& r : A) {
        r += 2; // Modifies the actual array element.
    }
    // A new reference is initialized each iteration; none is rebound.
    for (int x : A) cout << x << ' ';
    cout << '\n'; // 3 4 5

    cout << "\n3. Move a pointer through an array\n";
    int* p = A; // Here A converts to a pointer to its first element.
    cout << "*p = " << *p << '\n';             // 3
    cout << "*(p + 1) = " << *(p + 1) << '\n'; // 4
    cout << "A[1] = " << A[1] << '\n';         // 4
    p++; // Advances by ONE int element, not one byte.
    cout << "After p++, *p = " << *p << '\n';  // 4

    int& r = A[1];
    r++; // Increments the integer, not an address.
    cout << "After r++, A[1] = " << A[1] << '\n'; // 5

    cout << "\n4. Stop before the one-past-the-end pointer\n";
    int* end = A + 3; // Legal to form, but not to dereference.
    for (p = A; p != end; p++) cout << *p << ' ';
    cout << '\n'; // 3 5 5
    // cout << *end; // Invalid: no array element exists here.
    return 0;
}
