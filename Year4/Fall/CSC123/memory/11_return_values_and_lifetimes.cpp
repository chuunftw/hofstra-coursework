// In the VS Code terminal, open this file's folder and run:
// Compile: g++ -std=c++17 -Wall -Wextra -pedantic 11_return_values_and_lifetimes.cpp -o 11_return_values_and_lifetimes.exe
// Run:     .\11_return_values_and_lifetimes.exe
// Each lesson has its own main(); compile one .cpp file at a time.

#include <iostream>
using namespace std;

// Study guide section 11. Broken functions stay commented out.
/*
int* bad_pointer() {
    int x = 10;
    return &x; // x dies on return; its address becomes dangling.
}
int& bad_reference() {
    int x = 10;
    return x; // Same lifetime problem, expressed as a reference.
}
*/

int make_value() {
    int x = 10;
    return x; // Returns the integer value; caller does not depend on local x.
}

int* make_array(int n) {
    return new int[n]{}; // For this lesson, n is a small positive number.
    // Heap storage survives return. The caller must eventually delete[].
}

int main() {
    cout << "1. Return a value when you need the value\n";
    int value = make_value();
    cout << "value = " << value << '\n'; // 10

    cout << "\n2. A returned heap allocation outlives the function\n";
    int* A = make_array(3);
    A[0] = 12;
    cout << "A[0] = " << A[0] << '\n'; // 12
    delete[] A; // Caller owns this release, not make_array().
    A = nullptr;
    // Never try to fix a returned local address by deleting it.
    // Only storage allocated with matching new can be released with delete.
    return 0;
}
