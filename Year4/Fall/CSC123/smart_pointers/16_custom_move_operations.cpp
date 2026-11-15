// In the VS Code terminal, open this file's folder and run:
// Compile: g++ -std=c++17 -Wall -Wextra -pedantic 16_custom_move_operations.cpp -o 16_custom_move_operations.exe
// Run:     .\16_custom_move_operations.exe
// Each lesson has its own main(); compile one .cpp file at a time.
// Study guide section 16: Custom move constructors and assignment.
// Predict the output, run, then change one value and try again.

#include <cassert>
#include <functional>
#include <iostream>
#include <memory>
#include <stdexcept>
#include <utility>
#include <vector>
using namespace std;

// Sometimes a moved-from object must preserve a relationship between members, such as empty storage implying size zero.
// Define move operations to maintain that relationship.
// A move constructor creates a new object; move assignment updates an existing one.
// Return *this by lvalue reference from assignment.
// Rule of Five means consider all five special operations; they may be defaulted or deleted.
// Predict: Which operation runs for Buffer b(move(a)), and which runs for c = move(b)?

struct Buffer {
    unique_ptr<int[]> cells;
    int size;
    explicit Buffer(int n) : cells(make_unique<int[]>(n)), size(n) {}
    ~Buffer() = default;
    Buffer(const Buffer&) = delete;
    Buffer& operator=(const Buffer&) = delete;
    Buffer(Buffer&& other) noexcept
        : cells(move(other.cells)), size(exchange(other.size, 0)) {
        cout << "Move constructor\n";
    }
    Buffer& operator=(Buffer&& other) noexcept {
        cout << "Move assignment\n";
        if (this != &other) {
            cells = move(other.cells); // Deletes destination's old array.
            size = exchange(other.size, 0);
        }
        return *this;
    }
};
int main() {
    cout << "1. Construct by moving\n";
    Buffer a(3);
    a.cells[0] = 7;
    Buffer b(move(a));
    assert(!a.cells && a.size == 0 && b.cells[0] == 7);
    cout << "a size = " << a.size << ", b size = " << b.size << '\n'; // 0, 3

    cout << "\n2. Assign by moving\n";
    Buffer c(2);
    Buffer& result = (c = move(b));
    assert(&result == &c && !b.cells && b.size == 0 && c.cells[0] == 7);
    Buffer& same = c; // Aliasing can make source and destination identical.
    c = move(same); // Our explicit self-move check preserves c.
    assert(c.size == 3 && c.cells[0] == 7);
    cout << "c size = " << c.size << '\n'; // 3
}
