// In the VS Code terminal, open this file's folder and run:
// Compile: g++ -std=c++17 -Wall -Wextra -pedantic 07_structs_and_rule_of_zero.cpp -o 07_structs_and_rule_of_zero.exe
// Run:     .\07_structs_and_rule_of_zero.exe
// Each lesson has its own main(); compile one .cpp file at a time.
// Study guide section 7: Smart pointer members and the Rule of Zero.
// Predict the output, run, then change one value and try again.

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
