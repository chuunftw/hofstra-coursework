// Open this folder in the VS Code terminal.
// Compile: g++ -std=c++17 -Wall -Wextra -pedantic 12_rules_of_three_five_and_zero.cpp -o 12_rules_of_three_five_and_zero.exe
// Run:     .\12_rules_of_three_five_and_zero.exe
// One standalone program per topic; compile one .cpp file at a time.
// Study guide topic 12: Rules of Three, Five, and Zero.
// Read, predict, run, then change one value and predict again.

#include <cassert>
#include <functional>
#include <iostream>
#include <memory>
#include <stdexcept>
#include <utility>
#include <vector>
using namespace std;

// The Rule of Three concerns a destructor, copy constructor, and copy assignment when a class directly owns resources.
// The Rule of Five adds move construction and move assignment to that design decision.
// Default or delete operations as appropriate.
// The Rule of Zero means letting resource-managing members handle those operations for you.
// vector<int> gives value copying; unique_ptr gives exclusive ownership and moving.
// A virtual base destructor is needed when deleting derived objects through that base.
// Predict: Why is copying ValueBuffer safe while copying OwnerBuffer is disabled?

struct ValueBuffer {
    vector<int> cells; // Implements deep value copying and cleanup itself.
};
struct OwnerBuffer {
    unique_ptr<int> value; // Implements unique ownership and cleanup itself.
};
// Neither class defines any of the five special member functions.
struct Base {
    virtual ~Base() = default; // Required for this polymorphic deletion pattern.
};
struct Derived : Base {
    int& destroyed;
    explicit Derived(int& count) : destroyed(count) {}
    ~Derived() override { ++destroyed; }
};
int main() {
    cout << "1. Rule of Zero with value semantics\n";
    ValueBuffer a{{1, 2, 3}};
    auto b = a; // vector copies the elements into independent storage.
    b.cells[0] = 99;
    assert(a.cells[0] == 1 && b.cells[0] == 99);
    cout << "a first = " << a.cells[0] << ", b first = " << b.cells[0] << '\n';

    cout << "\n2. Rule of Zero with exclusive ownership\n";
    OwnerBuffer source{make_unique<int>(7)};
    // auto copy = source; // Disabled: unique_ptr cannot be copied.
    auto target = move(source);
    assert(!source.value && *target.value == 7);
    cout << "target = " << *target.value << '\n'; // 7

    cout << "\n3. Destruction through a base pointer\n";
    int destroyed = 0;
    {
        unique_ptr<Base> base = make_unique<Derived>(destroyed);
    }
    assert(destroyed == 1);
    cout << "derived destructor calls = " << destroyed << '\n'; // 1
    // Lesson 11 shows a deliberate custom move invariant; defaults suit many classes.
}
