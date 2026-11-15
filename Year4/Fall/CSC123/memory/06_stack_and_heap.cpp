// In the VS Code terminal, open this file's folder and run:
// Compile: g++ -std=c++17 -Wall -Wextra -pedantic 06_stack_and_heap.cpp -o 06_stack_and_heap.exe
// Run:     .\06_stack_and_heap.exe
// Each lesson has its own main(); compile one .cpp file at a time.

#include <iostream>
using namespace std;

// Study guide section 6. Local automatic storage is called "stack" here.
int main() {
    int local = 7; // Automatic integer: lives until main's scope ends.
    int* p = &local; // Automatic pointer, pointing to an automatic integer.
    cout << "1. A pointer does not imply a heap allocation\n";
    cout << "*p = " << *p << '\n'; // 7

    cout << "\n2. A local pointer can point to a heap integer\n";
    int* heap = new int(21);
    // heap itself: automatic pointer variable.
    // *heap: dynamically allocated integer, alive until delete.
    cout << "Heap value: " << *heap << '\n'; // 21
    delete heap;
    heap = nullptr;

    cout << "\n3. The allocation can outlive the pointer that created it\n";
    int* owner = nullptr;
    {
        int* temporary = new int(30);
        owner = temporary; // Preserve the address in an outer variable.
    } // temporary dies. Its heap integer is still alive.
    cout << "Value after the inner scope: " << *owner << '\n'; // 30
    delete owner; // The outer owner releases the allocation.
    owner = nullptr;
    // Without a retained address and cleanup, this allocation would leak.
    // local needs no delete: automatic objects end with their scope.
    return 0;
}
