// In the VS Code terminal, open this file's folder and run:
// Compile: g++ -std=c++17 -Wall -Wextra -pedantic 09_double_free.cpp -o 09_double_free.exe
// Run:     .\09_double_free.exe
// Each lesson has its own main(); compile one .cpp file at a time.

#include <iostream>
using namespace std;

// Study guide section 9: count allocations, not pointer variables.
int main() {
    int* A = new int[4]{}; // One allocation; A owns its cleanup.
    int* B = A; // Copies the address. B observes the SAME array.
    B[0] = 5;
    cout << "1. Two pointers, one array\n";
    cout << "A[0] = " << A[0] << '\n'; // 5
    cout << "Same address: " << boolalpha << (A == B) << '\n'; // true

    cout << "\n2. Release the shared allocation once\n";
    delete[] A;
    // Both pointers now have dangling values. Neither may access the array.
    A = nullptr; // Only resets A. B has NOT been reset by this statement.
    // delete[] B; // WRONG: would free the same allocation a second time.
    B = nullptr;
    cout << "Both pointers have now been reset.\n";
    // A non-null check on a dangling pointer would not establish validity.
    // B = A originally created no second array requiring a second release.
    return 0;
}
