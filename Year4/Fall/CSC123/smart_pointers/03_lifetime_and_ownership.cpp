// Open this folder in the VS Code terminal.
// Compile: g++ -std=c++17 -Wall -Wextra -pedantic 03_lifetime_and_ownership.cpp -o 03_lifetime_and_ownership.exe
// Run:     .\03_lifetime_and_ownership.exe
// One standalone program per topic; compile one .cpp file at a time.
// Study guide topic 3: Lifetime and ownership.
// Read, predict, run, then change one value and predict again.

#include <cassert>
#include <functional>
#include <iostream>
#include <memory>
#include <stdexcept>
#include <utility>
#include <vector>
using namespace std;

// An owner object and its target are separate objects.
// Destroying a unique_ptr deletes the object it still owns.
// Scope exit and reset can trigger cleanup.
// reset() deletes the current target and leaves the owner empty.
// A destructor message lets you see exactly when cleanup happens.
// Predict: When does target 2 disappear below: at reset or at the closing brace?

struct Tracked {
    int id;
    explicit Tracked(int n) : id(n) { cout << "Create " << id << '\n'; }
    ~Tracked() { cout << "Destroy " << id << '\n'; }
};
int main() {
    cout << "1. Scope cleanup\n";
    {
        auto owner = make_unique<Tracked>(1); // Create 1
        cout << "Inside scope\n";
    } // Destroy 1
    cout << "Outside scope\n";

    cout << "\n2. Early cleanup with reset\n";
    auto owner = make_unique<Tracked>(2); // Create 2
    owner.reset(); // Destroy 2
    assert(!owner);
    cout << "owner empty = " << boolalpha << !owner << '\n'; // true
} // Empty owner has no target to destroy.
