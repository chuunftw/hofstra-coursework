// In the VS Code terminal, open this file's folder and run:
// Compile: g++ -std=c++17 -Wall -Wextra -pedantic 04_lifetimes_and_cleanup.cpp -o 04_lifetimes_and_cleanup.exe
// Run:     .\04_lifetimes_and_cleanup.exe
// Each lesson has its own main(); compile one .cpp file at a time.
// Study guide section 4: Lifetime and automatic cleanup.
// Predict the output, run, then change one value and try again.

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
