// In the VS Code terminal, open this file's folder and run:
// Compile: g++ -std=c++17 -Wall -Wextra -pedantic 03_function_parameters.cpp -o 03_function_parameters.exe
// Run:     .\03_function_parameters.exe
// Each lesson has its own main(); compile one .cpp file at a time.

#include <iostream>
using namespace std;

// Study guide section 3. Start reading main(), then inspect each function.
void by_value(int x) {
    x++;  // x is a separate copy; the caller's integer stays unchanged.
}

void by_reference(int& x) {
    x++;  // x is another name for the caller's integer.
}

void by_pointer(int* x) {
    if (x != nullptr) {
        (*x)++;  // Follow the copied address to change the caller's integer.
    }
    // A null check cannot detect a dangling pointer. Pass live objects.
}

void redirect_copy(int* p, int& other) {
    p = &other;  // Only changes the function's local copy of the address.
    cout << "Inside redirect_copy, *p = " << *p << '\n';
}

void swap_values(int& a, int& b) {
    int temp = a;
    a = b;
    b = temp;
}

void inspect(const int& value) {
    cout << "Read through a const reference: " << value << '\n';
    // value++; // Invalid: cannot modify through this const reference.
    // const references are especially useful to avoid copying larger objects.
}

int main() {
    int n = 5;
    cout << "1. Three ways to pass n\n";
    by_value(n);
    cout << "After by_value: " << n << '\n';     // 5
    by_reference(n);
    cout << "After by_reference: " << n << '\n'; // 6
    by_pointer(&n);
    cout << "After by_pointer: " << n << '\n';   // 7

    cout << "\n2. A pointer parameter is a copy of an address\n";
    int other = 20;
    int* p = &n;
    redirect_copy(p, other); // Inside: 20
    cout << "Back in main, *p = " << *p << '\n'; // Still 7

    cout << "\n3. References let a function swap the originals\n";
    swap_values(n, other);
    cout << "n = " << n << ", other = " << other << '\n'; // 20, 7
    // swap_values(4, 5); // Invalid: int& cannot bind to these literals.
    inspect(n); // 20
    return 0;
}
