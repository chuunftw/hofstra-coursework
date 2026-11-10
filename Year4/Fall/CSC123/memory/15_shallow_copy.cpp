// In the VS Code terminal, open this file's folder and run:
// Compile: g++ -std=c++17 -Wall -Wextra -pedantic 15_shallow_copy.cpp -o 15_shallow_copy.exe
// Run:     .\15_shallow_copy.exe
// Each lesson has its own main(); compile one .cpp file at a time.

#include <iostream>
using namespace std;

// Study guide section 15. This view does NOT own or delete its target.
// It lets us observe a shallow copy safely; main owns the array below.
struct ArrayView {
    int* cells;
};

/* The guide's BROKEN owning type (not compiled or executed):
struct BadBuffer {
    int* cells;
    BadBuffer(int n) : cells(new int[n]{}) {}
    ~BadBuffer() { delete[] cells; }
};

BadBuffer A(3); // Allocation 1.
BadBuffer B(5); // Allocation 2.
B = A; // Default assignment copies the address, losing allocation 2: leak.
// At scope exit, B and A both delete allocation 1: double free.

// Alternatively, BadBuffer B = A; uses COPY CONSTRUCTION.
// B had no prior allocation to leak, but both destructors still double-free.
*/

int main() {
    cout << "1. Default copying copies a raw pointer's address\n";
    int* owner = new int[3]{1, 2, 3};
    ArrayView A{owner};
    ArrayView B = A; // Memberwise copy: B.cells receives A.cells's address.
    cout << "Same target: " << boolalpha << (A.cells == B.cells) << '\n'; // true
    B.cells[0] = 99;
    cout << "A.cells[0] = " << A.cells[0] << '\n'; // 99
    cout << "B.cells[0] = " << B.cells[0] << '\n'; // 99
    // Two view objects exist, but only ONE integer array exists.

    cout << "\n2. Shared access needs a clear cleanup owner\n";
    delete[] owner; // Release once, through the owner.
    owner = nullptr;
    A.cells = nullptr;
    B.cells = nullptr;
    cout << "One allocation released once.\n";
    // ArrayView has no deleting destructor. The broken owning type above does.
    // For independent owning copies, continue with 16_deep_copy_rule_of_three.cpp.
    return 0;
}
