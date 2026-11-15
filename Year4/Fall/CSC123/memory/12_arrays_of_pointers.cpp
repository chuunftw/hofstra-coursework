// In the VS Code terminal, open this file's folder and run:
// Compile: g++ -std=c++17 -Wall -Wextra -pedantic 12_arrays_of_pointers.cpp -o 12_arrays_of_pointers.exe
// Run:     .\12_arrays_of_pointers.exe
// Each lesson has its own main(); compile one .cpp file at a time.

#include <iostream>
using namespace std;

// Study guide section 12. Assume these small allocations succeed.
int main() {
    cout << "1. Allocate the pointer array and its targets\n";
    int** A = new int*[3]{}; // Allocation 1: an array of THREE pointers.
    for (int i = 0; i < 3; i++) {
        A[i] = new int(i + 1); // Allocations 2, 3, 4: one integer each.
    }
    // A points to the pointer array; A[i] points to one integer.
    // *A[i] accesses that integer. No separate integer array was allocated.
    for (int i = 0; i < 3; i++) cout << *A[i] << ' ';
    cout << '\n'; // 1 2 3

    cout << "\n2. Release the integers first\n";
    for (int i = 0; i < 3; i++) {
        delete A[i]; // Scalar new int -> scalar delete.
        A[i] = nullptr;
    }
    cout << "Released three integers.\n";

    cout << "\n3. Release the pointer array last\n";
    delete[] A; // Array new int*[3] -> delete[].
    A = nullptr;
    cout << "Released the pointer array: four releases in total.\n";
    // delete[] A alone would not delete the three target integers.
    // Freeing the pointer array first would lose access to their addresses.
    return 0;
}
