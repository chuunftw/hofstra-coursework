// In the VS Code terminal, open this file's folder and run:
// Compile: g++ -std=c++17 -Wall -Wextra -pedantic 03_unique_arrays.cpp -o 03_unique_arrays.exe
// Run:     .\03_unique_arrays.exe
// Each lesson has its own main(); compile one .cpp file at a time.
// Study guide section 3: Smart pointers to arrays.
// Predict the output, run, then change one value and try again.

#include <cassert>
#include <functional>
#include <iostream>
#include <memory>
#include <stdexcept>
#include <utility>
#include <vector>
using namespace std;

// make_unique<int>(3) creates one integer with value 3.
// make_unique<int[]>(3) creates three value-initialized integers (all zero).
// unique_ptr<T[]> uses delete[] automatically.
// It does not remember the array length or check indices; keep the length separately or use vector.
// Predict: What are the initial contents of make_unique<int[]>(4)?

int main() {
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
