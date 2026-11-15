// In the VS Code terminal, open this file's folder and run:
// Compile: g++ -std=c++17 -Wall -Wextra -pedantic 06_function_parameters_and_returns.cpp -o 06_function_parameters_and_returns.exe
// Run:     .\06_function_parameters_and_returns.exe
// Each lesson has its own main(); compile one .cpp file at a time.
// Study guide section 6: Functions: borrow or take ownership.
// Predict the output, run, then change one value and try again.

#include <cassert>
#include <functional>
#include <iostream>
#include <memory>
#include <stdexcept>
#include <utility>
#include <vector>
using namespace std;

// A parameter of type unique_ptr<T> receives ownership by value.
// Passing a named owner requires move.
// A T& or const T& parameter can borrow the target without transferring ownership.
// Return an owner by value to hand ownership to the caller; return a local owner normally, without adding move.
// Predict: Which call leaves the caller's pointer empty: inspect(*p), increment(*p), or consume(move(p))?

void inspect(const int& value) { cout << "Inspect " << value << '\n'; }
void increment(int& value) { ++value; }
void consume(unique_ptr<int> value) {
    cout << "Consume " << *value << '\n';
} // Parameter destroys its target.
unique_ptr<int> create_value() {
    auto result = make_unique<int>(42);
    return result; // Elided or implicitly moved; no dangling local target.
}
int main() {
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
