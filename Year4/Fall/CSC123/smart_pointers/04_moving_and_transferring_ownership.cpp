// Open this folder in the VS Code terminal.
// Compile: g++ -std=c++17 -Wall -Wextra -pedantic 04_moving_and_transferring_ownership.cpp -o 04_moving_and_transferring_ownership.exe
// Run:     .\04_moving_and_transferring_ownership.exe
// One standalone program per topic; compile one .cpp file at a time.
// Study guide topic 4: Moving and transferring ownership.
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

// SECTION 1: Moving ownership
// Move construction initializes a new owner.
// Move assignment replaces an existing owner's target, cleaning up its old target first.
// After a transfer between distinct unique_ptr objects, the source is empty but remains a live, reusable object.
// The heap object itself stays at the same address.
// Predict: After b = move(a), which old object is destroyed, and which owner is empty?
namespace section_1 {
struct Tracked {
    int id;
    explicit Tracked(int n) : id(n) {}
    ~Tracked() { cout << "Destroy " << id << '\n'; }
};
void run() {
    auto a = make_unique<Tracked>(1);
    auto b = make_unique<Tracked>(2);
    auto original_address = a.get(); // Observer only.
    cout << "1. Move assignment\n";
    b = move(a); // Destroy 2; b now owns object 1.
    cout << "a empty = " << boolalpha << !a << ", b id = " << b->id << '\n';
    assert(!a && b->id == 1 && b.get() == original_address);
    // cout << a->id; // Invalid: a is empty b/c b took its value 

    cout << "\n2. Move construction\n";
    auto c = move(b);
    assert(!b && c->id == 1);
    cout << "c id = " << c->id << '\n'; // 1
    a = make_unique<Tracked>(3); // A moved-from owner can be reused.
    cout << "reused a id = " << a->id << '\n'; // 3
} // Destroy 1 (c), then 3 (a); b is empty.
}

// SECTION 2: Functions: borrow or take ownership
// A parameter of type unique_ptr<T> receives ownership by value.
// Passing a named owner requires move.
// A T& or const T& parameter can borrow the target without transferring ownership.
// Return an owner by value to hand ownership to the caller; return a local owner normally, without adding move.
// Predict: Which call leaves the caller's pointer empty: inspect(*p), increment(*p), or consume(move(p))?
namespace section_2 {
void inspect(const int& value) { cout << "Inspect " << value << '\n'; }
void increment(int& value) { ++value; }
void consume(unique_ptr<int> value) {
    cout << "Consume " << *value << '\n';
} // Parameter destroys its target.
unique_ptr<int> create_value() {
    auto result = make_unique<int>(42);
    return result; // Elided or implicitly moved; no dangling local target.
}
void run() {
    cout << "1. Borrow the integer\n";
    auto p = make_unique<int>(7);
    inspect(*p); // 7; still owned by p.
    increment(*p);
    assert(p && *p == 8);

    cout << "\n2. Pass ownership\n";
    consume(move(p)); // 8
    assert(!p);
    // consume(p); // Compile error: would copy unique_ptr.

    cout << "\n3. Return ownership\n";
    auto returned = create_value();
    cout << "returned = " << *returned << '\n'; // 42
    assert(*returned == 42);
}
}

int main() {
    cout << "\n=== Section 1: Moving ownership ===\n";
    section_1::run();
    cout << "\n=== Section 2: Functions: borrow or take ownership ===\n";
    section_2::run();
}
