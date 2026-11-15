// In the VS Code terminal, open this file's folder and run:
// Compile: g++ -std=c++17 -Wall -Wextra -pedantic 05_move_ownership.cpp -o 05_move_ownership.exe
// Run:     .\05_move_ownership.exe
// Each lesson has its own main(); compile one .cpp file at a time.
// Study guide section 5: Moving ownership.
// Predict the output, run, then change one value and try again.

#include <cassert>
#include <functional>
#include <iostream>
#include <memory>
#include <stdexcept>
#include <utility>
#include <vector>
using namespace std;

// Move construction initializes a new owner.
// Move assignment replaces an existing owner's target, cleaning up its old target first.
// After a transfer between distinct unique_ptr objects, the source is empty but remains a live, reusable object.
// The heap object itself stays at the same address.
// Predict: After b = move(a), which old object is destroyed, and which owner is empty?

struct Tracked {
    int id;
    explicit Tracked(int n) : id(n) {}
    ~Tracked() { cout << "Destroy " << id << '\n'; }
};
int main() {
    auto a = make_unique<Tracked>(1);
    auto b = make_unique<Tracked>(2);
    auto original_address = a.get(); // Observer only.
    cout << "1. Move assignment\n";
    b = move(a); // Destroy 2; b now owns object 1.
    cout << "a empty = " << boolalpha << !a << ", b id = " << b->id << '\n';
    assert(!a && b->id == 1 && b.get() == original_address);
    // cout << a->id; // Invalid: a is empty.

    cout << "\n2. Move construction\n";
    auto c = move(b);
    assert(!b && c->id == 1);
    cout << "c id = " << c->id << '\n'; // 1
    a = make_unique<Tracked>(3); // A moved-from owner can be reused.
    cout << "reused a id = " << a->id << '\n'; // 3
} // Destroy 1 (c), then 3 (a); b is empty.
