// In the VS Code terminal, open this file's folder and run:
// Compile: g++ -std=c++17 -Wall -Wextra -pedantic 12_mutation_and_remaining_hazards.cpp -o 12_mutation_and_remaining_hazards.exe
// Run:     .\12_mutation_and_remaining_hazards.exe
// Each lesson has its own main(); compile one .cpp file at a time.
// Study guide section 12: Mutation and remaining hazards.
// Predict the output, run, then change one value and try again.

#include <cassert>
#include <functional>
#include <iostream>
#include <memory>
#include <stdexcept>
#include <utility>
#include <vector>
using namespace std;

// Smart pointers automate deletion; they do not prevent every invalid access or ownership cycle.
// Appending to a vector during a range-for invalidates the cached end iterator, and reallocation can invalidate all iterators/references.
// Read the original data in a separate stage.
// Do not move a list's root owner into one of its own descendants.
// Predict: Why is reserving capacity alone insufficient to make the commented range-for safe?

int main() {
    cout << "1. Append from a stable snapshot\n";
    vector<int> values{2, 4, 6};
    // for (int x : values) values.push_back(x); // Invalid iteration.
    const auto original = values;
    for (int x : original) values.push_back(x);
    for (int x : values) cout << x << ' ';
    cout << '\n'; // 2 4 6 2 4 6
    assert((values == vector<int>{2, 4, 6, 2, 4, 6}));

    cout << "\n2. Preserve old values until both results are ready\n";
    int x = 2, y = 3;
    // A 90-degree rotation should produce (-y, x).
    // x = -y; y = x; // Wrong: y would read the UPDATED x.
    const int old_x = x, old_y = y;
    x = -old_y;
    y = old_x;
    cout << "rotated = " << x << ", " << y << '\n'; // -3, 2
    assert(x == -3 && y == 2);

    // For head -> node2 -> node3, this loses the external owner:
    // head->next->next = move(head);
    // node3 is deleted, while node1/node2 form an unreachable owning cycle.
    // unique_ptr does not automatically detect cycles in a data structure.
}
