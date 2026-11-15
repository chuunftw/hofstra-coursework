// In the VS Code terminal, open this file's folder and run:
// Compile: g++ -std=c++17 -Wall -Wextra -pedantic 15_lvalues_rvalues_and_move.cpp -o 15_lvalues_rvalues_and_move.exe
// Run:     .\15_lvalues_rvalues_and_move.exe
// Each lesson has its own main(); compile one .cpp file at a time.
// Study guide section 15: References and what move actually does.
// Predict the output, run, then change one value and try again.

#include <cassert>
#include <functional>
#include <iostream>
#include <memory>
#include <stdexcept>
#include <utility>
#include <vector>
using namespace std;

// An lvalue identifies an object; a named variable expression is an lvalue even when its declared type is T&&.
// An rvalue reference can bind to a temporary or to an xvalue produced by move.
// std::move is a cast that enables move operations; the receiving constructor or assignment performs the transfer.
// It does not transfer anything merely by binding a reference.
// Predict: Why does binding candidate = move(owner) below leave owner nonempty?

void category(int&) { cout << "lvalue overload\n"; }
void category(int&&) { cout << "rvalue overload\n"; }
int main() {
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
