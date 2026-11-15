// Open this folder in the VS Code terminal.
// Compile: g++ -std=c++17 -Wall -Wextra -pedantic 05_smart_pointers_inside_structs.cpp -o 05_smart_pointers_inside_structs.exe
// Run:     .\05_smart_pointers_inside_structs.exe
// One standalone program per topic; compile one .cpp file at a time.
// Study guide topic 5: Smart pointers inside structs.
// Read, predict, run, then change one value and predict again.

#include <cassert>
#include <functional>
#include <iostream>
#include <memory>
#include <stdexcept>
#include <utility>
#include <vector>
using namespace std;

// A class whose members manage their own resources usually needs no custom destructor, copy constructor, copy assignment, move constructor, or move assignment.
// This is the Rule of Zero.
// With a unique_ptr member, default copying is unavailable but default moving can work.
// Scalar members are copied during a default move; they do not automatically become zero.
// Predict: Why can a moved-from Buffer have empty cells but a size of 3?

struct Buffer {
    unique_ptr<int[]> cells;
    int size;
    explicit Buffer(int n) : cells(make_unique<int[]>(n)), size(n) {}
    // No custom destructor or copy/move operations.
};
int main() {
    cout << "1. Members manage their own resources\n";
    Buffer a(3);
    a.cells[0] = 7;
    // Buffer copy = a; // Compile error: cells cannot be copied.
    Buffer b = move(a);
    cout << "b size = " << b.size << ", first = " << b.cells[0] << '\n'; // 3, 7
    cout << "a cells empty = " << boolalpha << !a.cells
         << ", a size = " << a.size << '\n'; // true, 3
    assert(!a.cells && a.size == 3 && b.cells[0] == 7);

    cout << "\n2. Reassign a moved-from object\n";
    a = Buffer(2);
    assert(a.cells && a.size == 2);
    cout << "a size now = " << a.size << '\n'; // 2
    // Check cells before accessing data; size alone is insufficient after move.
}
