// Open this folder in the VS Code terminal.
// Compile: g++ -std=c++17 -Wall -Wextra -pedantic 02_unique_ptr_and_make_unique.cpp -o 02_unique_ptr_and_make_unique.exe
// Run:     .\02_unique_ptr_and_make_unique.exe
// One standalone program per topic; compile one .cpp file at a time.
// Study guide topic 2: unique_ptr and make_unique.
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

// SECTION 1: unique_ptr and make_unique
// A unique_ptr is an object that manages a pointer.
// make_unique creates the heap object and returns its owner.
// Use * to access a value, -> to access an object's members, and a boolean check to test for a target.
// Ordinary copying is disabled because it would create competing owners.
// Predict: Why is auto second = number rejected, while int copy = *number works?
namespace section_1 {
struct Point {
    int x, y;
    Point(int a, int b) : x(a), y(b) {}
};
void run() {
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
}

// SECTION 2: Smart pointers to arrays
// make_unique<int>(3) creates one integer with value 3.
// make_unique<int[]>(3) creates three value-initialized integers (all zero).
// unique_ptr<T[]> uses delete[] automatically.
// It does not remember the array length or check indices; keep the length separately or use vector.
// Predict: What are the initial contents of make_unique<int[]>(4)?
namespace section_2 {
void run() {
    cout << "1. One integer versus an array\n";
    auto single = make_unique<int>(3);
    const int length = 3;
    auto values = make_unique<int[]>(length);
    cout << "single = " << *single << '\n'; // 3
    for (int i = 0; i < length; ++i) assert(values[i] == 0);

    cout << "\n2. Index the owned array\n";
    for (int i = 0; i < length; ++i) values[i] = (i + 1) * 10;
    for (int i = 0; i < length; ++i) cout << values[i] << ' ';
    cout << '\n'; // 10 20 30
    assert(values[0] == 10 && values[2] == 30);
    // values[3] = 40; // Invalid: index is outside this array.
    // No delete[] call: unique_ptr<int[]> performs it.
}
}

int main() {
    cout << "\n=== Section 1: unique_ptr and make_unique ===\n";
    section_1::run();
    cout << "\n=== Section 2: Smart pointers to arrays ===\n";
    section_2::run();
}
