// In the VS Code terminal, open this file's folder and run:
// Compile: g++ -std=c++17 -Wall -Wextra -pedantic 02_unique_ptr_basics.cpp -o 02_unique_ptr_basics.exe
// Run:     .\02_unique_ptr_basics.exe
// Each lesson has its own main(); compile one .cpp file at a time.
// Study guide section 2: unique_ptr and make_unique.
// Predict the output, run, then change one value and try again.

#include <cassert>
#include <functional>
#include <iostream>
#include <memory>
#include <stdexcept>
#include <utility>
#include <vector>
using namespace std;

// A unique_ptr is an object that manages a pointer.
// make_unique creates the heap object and returns its owner.
// Use * to access a value, -> to access an object's members, and a boolean check to test for a target.
// Ordinary copying is disabled because it would create competing owners.
// Predict: Why is auto second = number rejected, while int copy = *number works?

struct Point {
    int x, y;
    Point(int a, int b) : x(a), y(b) {}
};
int main() {
    cout << "1. Own one integer\n";
    auto number = make_unique<int>(10);
    *number += 5;
    cout << "value = " << *number << '\n'; // 15
    assert(*number == 15);
    // auto second = number; // Compile error: cannot copy unique_ptr.
    int copy = *number; // Copies the INTEGER, not its owner.
    assert(copy == 15);

    cout << "\n2. Own a struct\n";
    auto point = make_unique<Point>(3, 5);
    point->x += 1;
    cout << "point = " << point->x << ", " << point->y << '\n'; // 4, 5
    assert(point->x == 4 && point->y == 5);
    unique_ptr<int> empty;
    cout << "empty has data = " << boolalpha << bool(empty) << '\n'; // false
    // delete number; // Compile error: delete expects a raw pointer.
} // Both owned objects are cleaned up automatically.
