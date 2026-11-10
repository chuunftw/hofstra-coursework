// In the VS Code terminal, open this file's folder and run:
// Compile: g++ -std=c++17 -Wall -Wextra -pedantic 14_resizing_arrays.cpp -o 14_resizing_arrays.exe
// Run:     .\14_resizing_arrays.exe
// Each lesson has its own main(); compile one .cpp file at a time.

#include <iostream>
using namespace std;

// Study guide section 14, shown directly in main to expose every step.
// This fixed example starts with positive capacity and sizes that fit in int.
int main() {
    int capacity = 2; // How many elements fit in the allocation.
    int tos = 0;     // How many elements are currently in use.
    int* cells = new int[capacity]{};
    cells[tos++] = 10; // Store at index 0, THEN increase tos to 1.
    cells[tos++] = 20; // Store at index 1, THEN increase tos to 2.
    cout << "1. Array is full\n";
    cout << "size = " << tos << ", capacity = " << capacity << '\n'; // 2, 2

    cout << "\n2. Grow before adding another element\n";
    if (tos == capacity) {
        int newcapacity = capacity * 2;
        int* replacement = new int[newcapacity]{}; // 1. Allocate.
        for (int i = 0; i < tos; i++) {
            replacement[i] = cells[i];            // 2. Copy live elements.
        }
        delete[] cells;                          // 3. Release old storage.
        cells = replacement;                     // 4. Adopt new storage.
        capacity = newcapacity;
        // replacement is a temporary pointer; cells now owns the allocation.
        // Do not delete replacement here: that would invalidate cells too.
    }
    // Deleting before copying would read freed memory.
    // Overwriting cells before releasing its old array would leak that array.
    cells[tos++] = 30;
    cout << "size = " << tos << ", capacity = " << capacity << '\n'; // 3, 4
    for (int i = 0; i < tos; i++) cout << cells[i] << ' ';
    cout << '\n'; // 10 20 30

    cout << "\n3. Pop changes logical size, not allocation size\n";
    if (tos > 0) { // Never pop an empty collection.
        int popped = cells[--tos]; // Decrease to 2, THEN read index 2.
        cout << "popped = " << popped << '\n'; // 30
    }
    cout << "size = " << tos << ", capacity = " << capacity << '\n'; // 2, 4
    // The allocation still holds four int slots. Only two are logically used.
    delete[] cells;
    cells = nullptr;
    // One resize copies n elements: O(n). Repeated doubling spreads that cost
    // across pushes: amortized O(1) per push, with O(log n) growth allocations.
    return 0;
}
