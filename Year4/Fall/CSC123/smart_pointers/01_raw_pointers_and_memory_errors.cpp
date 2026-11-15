// Open this folder in the VS Code terminal.
// Compile: g++ -std=c++17 -Wall -Wextra -pedantic 01_raw_pointers_and_memory_errors.cpp -o 01_raw_pointers_and_memory_errors.exe
// Run:     .\01_raw_pointers_and_memory_errors.exe
// One standalone program per topic; compile one .cpp file at a time.
// Study guide topic 1: Raw pointer review and memory errors.
// Read, predict, run, then change one value and predict again.

#include <cassert>
#include <functional>
#include <iostream>
#include <memory>
#include <stdexcept>
#include <utility>
#include <vector>
using namespace std;

// A raw pointer holds an address.
// It may point to a local object or to heap storage.
// Copying the pointer copies the address; it does not copy the object.
// With manual allocation, one designated owner must delete each allocation exactly once, after its last use.
// Losing the only owning address leaks memory.
// Predict: Why would assigning heap = &local before delete heap cause two different problems?

int main() {
    cout << "1. Two pointers, one local integer\n";
    int local = 5;
    int* p = &local;
    int* alias = p;
    *alias += 2;
    cout << "local = " << local << '\n'; // 7
    assert(local == 7);

    cout << "\n2. Manual heap ownership\n";
    int* heap = new int(10);
    cout << "heap value = " << *heap << '\n'; // 10
    // heap = &local; // Would lose the allocation: leak.
    // delete &local; // Invalid: local was not allocated with new.
    delete heap;
    heap = nullptr;
    // cout << *heap; // Invalid: null dereference.
    delete heap; // Deleting nullptr is safe; no object is deleted.
    assert(heap == nullptr);
    // Returning &local from this function would leave a dangling pointer.
}
