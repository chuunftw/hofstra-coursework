// In the VS Code terminal, open this file's folder and run:
// Compile: g++ -std=c++17 -Wall -Wextra -pedantic 13_shared_ptr_and_counts.cpp -o 13_shared_ptr_and_counts.exe
// Run:     .\13_shared_ptr_and_counts.exe
// Each lesson has its own main(); compile one .cpp file at a time.
// Study guide section 13: Shared ownership and reference counts.
// Predict the output, run, then change one value and try again.

#include <cassert>
#include <functional>
#include <iostream>
#include <memory>
#include <stdexcept>
#include <utility>
#include <vector>
using namespace std;

// shared_ptr lets several owners keep one object alive.
// Copying adds an owner; destroying or resetting an owner removes one.
// The last strong owner destroys the object.
// A reference parameter does not add an owner.
// Moving transfers a handle; its effect on counts depends on what the destination owned before.
// Predict: What are the counts after p1 = other, p2 = p3, and p2 = move(p3)?

void by_value(shared_ptr<int> p) { cout << "inside by value = " << p.use_count() << '\n'; }
void by_reference(const shared_ptr<int>& p) { cout << "inside reference = " << p.use_count() << '\n'; }
int main() {
    cout << "1. Trace copies and reassignment\n";
    auto origin = make_shared<int>(10);
    auto p1 = origin, p2 = origin, p3 = origin;
    auto other = make_shared<int>(20);
    cout << "initial = " << origin.use_count() << '\n'; // 4, not 3.
    assert(origin.use_count() == 4);
    p1 = other;
    assert(origin.use_count() == 3 && other.use_count() == 2);
    p2 = p3; // Already share the same target: net count unchanged.
    assert(origin.use_count() == 3);
    p2 = move(p3); // Two handles become one; origin plus p2 remain.
    cout << "after moves = " << origin.use_count() << '\n'; // 2
    assert(!p3 && origin.use_count() == 2);

    cout << "\n2. Function parameters\n";
    by_value(origin); // 3 inside, then back to 2.
    by_reference(origin); // 2
    assert(origin.use_count() == 2);
    auto transferred = move(origin); // New owner replaces source: count stays 2.
    assert(!origin && transferred.use_count() == 2);
}
