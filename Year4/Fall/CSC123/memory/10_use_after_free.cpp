// In the VS Code terminal, open this file's folder and run:
// Compile: g++ -std=c++17 -Wall -Wextra -pedantic 10_use_after_free.cpp -o 10_use_after_free.exe
// Run:     .\10_use_after_free.exe
// Each lesson has its own main(); compile one .cpp file at a time.

#include <iostream>
using namespace std;

// Study guide section 10. Undefined behavior has no guaranteed output.
int main() {
    cout << "1. Finish reading before deleting\n";
    int* A = new int[2]{};
    A[1] = 40;
    int* B = A;
    // delete[] A; // Moving deletion here would make the next read invalid.
    cout << "B[1] = " << B[1] << '\n'; // 40: allocation is still alive.
    delete[] A;
    // cout << B[1]; // Use after free: might appear to work, fail, or do worse.
    A = nullptr;
    B = nullptr;
    // Removing delete entirely would trade this error for a leak.

    cout << "\n2. References can dangle too\n";
    int* p = new int(9);
    int& r = *p;
    cout << "r before deletion = " << r << '\n'; // 9
    delete p;
    p = nullptr;
    // cout << r; // Invalid: the reference's target has died.
    // r = 10;    // Also invalid. This writes through a dangling reference.
    // A reference cannot be reset to nullptr or rebound to repair its target.
    cout << "After deletion, we stop using r.\n";
    // Having an alias never keeps a heap allocation alive by itself.
    return 0;
}
