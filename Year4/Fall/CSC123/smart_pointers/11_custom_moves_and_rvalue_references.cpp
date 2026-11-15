// Open this folder in the VS Code terminal.
// Compile: g++ -std=c++17 -Wall -Wextra -pedantic 11_custom_moves_and_rvalue_references.cpp -o 11_custom_moves_and_rvalue_references.exe
// Run:     .\11_custom_moves_and_rvalue_references.exe
// One standalone program per topic; compile one .cpp file at a time.
// Study guide topic 11: Custom move operations and rvalue references.
// Read, predict, run, then change one value and predict again.

#include <cassert>
#include <functional>
#include <iostream>
#include <memory>
#include <stdexcept>
#include <utility>
#include <vector>
using namespace std;

// Namespaces keep the small demonstrations independent within this one file.
// Start at main() at the bottom, then read one section at a time.

// SECTION 1: References and what move actually does
// An lvalue identifies an object; a named variable expression is an lvalue even when its declared type is T&&.
// An rvalue reference can bind to a temporary or to an xvalue produced by move.
// std::move is a cast that enables move operations; the receiving constructor or assignment performs the transfer.
// It does not transfer anything merely by binding a reference.
// Predict: Why does binding candidate = move(owner) below leave owner nonempty?
namespace section_1 {
void category(int&) { cout << "lvalue overload\n"; }
void category(int&&) { cout << "rvalue overload\n"; }
void run() {
    cout << "1. Reference binding and named expressions\n";
    int x = 3;
    int& lref = x;
    const int& temporary = 4;
    int&& rref = 5;
    category(x); // lvalue
    category(6); // rvalue
    category(rref); // lvalue: rref is a named variable.
    category(move(rref)); // rvalue
    assert(lref == 3 && temporary == 4 && rref == 5);
    // int& bad = 3; // Non-const lvalue reference cannot bind to this temporary.

    cout << "\n2. A cast alone does not transfer ownership\n";
    auto owner = make_unique<int>(8);
    auto&& candidate = move(owner); // Only binds a reference.
    cout << "owner still full = " << boolalpha << bool(owner) << '\n'; // true
    assert(owner && &candidate == &owner);
    auto destination = move(candidate); // Move constructor actually transfers.
    assert(!owner && *destination == 8);
    cout << "destination = " << *destination << '\n'; // 8
}
}

// SECTION 2: Custom move constructors and assignment
// Sometimes a moved-from object must preserve a relationship between members, such as empty storage implying size zero.
// Define move operations to maintain that relationship.
// A move constructor creates a new object; move assignment updates an existing one.
// Return *this by lvalue reference from assignment.
// Rule of Five means consider all five special operations; they may be defaulted or deleted.
// Predict: Which operation runs for Buffer b(move(a)), and which runs for c = move(b)?
namespace section_2 {
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
void run() {
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
    Buffer& same = c; // Source and destination may alias.
    c = move(same); // Self-move check preserves c.
    assert(c.size == 3 && c.cells[0] == 7);
    cout << "c size = " << c.size << '\n'; // 3
}
}

int main() {
    cout << "\n=== Section 1: References and what move actually does ===\n";
    section_1::run();
    cout << "\n=== Section 2: Custom move constructors and assignment ===\n";
    section_2::run();
}
