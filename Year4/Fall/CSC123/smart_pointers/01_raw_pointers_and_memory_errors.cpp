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
    // p holds local's address, so copying p makes alias point to local too.
    // &p is the address of the pointer itself, so it needs int** other = &p.
    // int* other = &p; would be a compiler error: &p has type int**, not int*.
    int* alias = p;
    *alias += 2;
    cout << "local = " << local << '\n'; // 7
    assert(local == 7);

    cout << "\n2. Manual heap ownership\n";
    // Stack: the local pointer variable heap stores an address.
    // Heap: new int(10) creates an integer initialized to 10 and returns its address.
    // Stack: heap [address] ---> Heap: [10]. *heap accesses that integer's value.
    // The name "heap" does not determine where the pointer variable itself lives.
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
    // delete frees the integer; assigning nullptr clears a pointer.
}

void quiz() {
    {
        int* p = new int(20);
        int* q = p;
        delete p; 
        p = nullptr;
    // Questions:
    // 1. Is the integer 20 still allocated?
    // 2. Is q dangling or null?
    // 3. What line should we write next to clear q?
    // Answers:
    // 1. No. delete p freed the allocated integer.
    // 2. q is dangling: it still holds the old address of the freed integer.
    // 3. q = nullptr; clears that address without freeing any memory.
    // Do not delete q here: the integer was already deleted through p.
        q = nullptr;
        assert(q == nullptr);
    }

    // Quiz 2: Does this example free the integer, or leak it?
    {
        int* p = new int(20);
        p = nullptr;
        delete p;
    }
    // Answer: It leaks. Assigning nullptr loses the allocation's only stored address.
    // The integer remains allocated, and deleting nullptr safely does nothing.
    // Correct order: delete p; then p = nullptr;
}
