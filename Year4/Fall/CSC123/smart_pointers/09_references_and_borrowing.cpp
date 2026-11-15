// In the VS Code terminal, open this file's folder and run:
// Compile: g++ -std=c++17 -Wall -Wextra -pedantic 09_references_and_borrowing.cpp -o 09_references_and_borrowing.exe
// Run:     .\09_references_and_borrowing.exe
// Each lesson has its own main(); compile one .cpp file at a time.
// Study guide section 9: Borrowing the owner versus borrowing the target.
// Predict the output, run, then change one value and try again.

#include <cassert>
#include <functional>
#include <iostream>
#include <memory>
#include <stdexcept>
#include <utility>
#include <vector>
using namespace std;

// unique_ptr<int>& aliases the owner object.
// int& bound to *owner aliases the heap integer.
// Moving ownership empties the source owner but does not move the integer, so a reference to the integer can remain valid while the new owner keeps it alive.
// Neither reference extends its referent's lifetime.
// Predict: After the move below, why is value_ref usable while *owner_ref is invalid?

int main() {
    cout << "1. Two different things to borrow\n";
    auto owner = make_unique<int>(5);
    unique_ptr<int>& owner_ref = owner;
    int& value_ref = *owner;
    auto destination = move(owner);
    cout << "owner_ref empty = " << boolalpha << !owner_ref << '\n'; // true
    cout << "value_ref = " << value_ref << '\n'; // 5
    assert(!owner_ref && value_ref == 5);
    // cout << *owner_ref; // Invalid: the OWNER is now empty.

    cout << "\n2. The target is still alive\n";
    value_ref += 2;
    cout << "destination value = " << *destination << '\n'; // 7
    assert(*destination == 7);
    destination.reset(); // value_ref now dangles: do not use it.
    owner_ref = make_unique<int>(20); // Reuses owner through its alias.
    cout << "reused owner = " << *owner << '\n'; // 20
    assert(*owner == 20);
}
