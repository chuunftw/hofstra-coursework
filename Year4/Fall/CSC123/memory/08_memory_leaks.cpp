// In the VS Code terminal, open this file's folder and run:
// Compile: g++ -std=c++17 -Wall -Wextra -pedantic 08_memory_leaks.cpp -o 08_memory_leaks.exe
// Run:     .\08_memory_leaks.exe
// Each lesson has its own main(); compile one .cpp file at a time.

#include <iostream>
using namespace std;

// Study guide section 8. A leak is an allocation that is not released.
// These examples assume allocations succeed, as in the practice quiz.
// Broken examples are comments, so running this file does not cause leaks.
/*
void leak() {
    int* A = new int[4];
} // The only address is lost. The heap array is not automatically deleted.
*/

int main() {
    cout << "1. Release an allocation before its owner leaves scope\n";
    {
        int* A = new int[4]{}; // {} initializes the integers to zero.
        A[0] = 7;
        cout << "A[0] = " << A[0] << '\n'; // 7
        delete[] A;
    } // Nothing was left allocated.

    cout << "\n2. Release old storage before overwriting its address\n";
    int* A = new int[4]{}; // Allocation 1.
    int* B = new int[8]{}; // Allocation 2.
    B[0] = 21;
    // A = B; // Here, this would lose the only address of allocation 1.
    delete[] A; // Release allocation 1 while its address is available.
    A = B;      // Both pointers now reach allocation 2.
    cout << "A[0] = " << A[0] << '\n'; // 21
    delete[] B; // Release allocation 2 exactly once.
    A = nullptr;
    B = nullptr;
    // Setting A to nullptr BEFORE freeing its sole allocation could leak it.
    // Copying an address never automatically frees its previous target.
    cout << "Two allocations, two matching releases.\n";
    return 0;
}
