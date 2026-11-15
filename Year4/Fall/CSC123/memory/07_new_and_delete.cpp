// In the VS Code terminal, open this file's folder and run:
// Compile: g++ -std=c++17 -Wall -Wextra -pedantic 07_new_and_delete.cpp -o 07_new_and_delete.exe
// Run:     .\07_new_and_delete.exe
// Each lesson has its own main(); compile one .cpp file at a time.

#include <iostream>
using namespace std;

// Study guide section 7: match the form of new with the form of delete.
int main() {
    cout << "1. One dynamically allocated integer\n";
    int* p = new int(10);
    cout << "*p = " << *p << '\n'; // 10
    delete p; // Scalar new -> scalar delete.
    // delete does not reset p. Do not read through p after deletion.
    p = nullptr; // The pointer variable still exists and can be assigned.

    cout << "\n2. A dynamically allocated array\n";
    int* A = new int[3]{4, 5, 6};
    for (int i = 0; i < 3; i++) cout << A[i] << ' ';
    cout << '\n'; // 4 5 6
    // delete A;        // Wrong: an array needs delete[].
    // delete[] (A+1);  // Wrong: must use the allocation's starting address.
    delete[] A;
    A = nullptr;

    cout << "\n3. Automatic arrays clean up at scope exit\n";
    int local[] = {1, 2, 3};
    cout << "local[0] = " << local[0] << '\n'; // 1
    // delete[] local; // Wrong: local was not allocated with new[].

    delete p;   // Safe: p is nullptr. No allocation is released.
    delete[] A; // Also safe: A is nullptr.
    cout << "Deleting a null pointer is safe.\n";
    return 0;
}
