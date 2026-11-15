// In the VS Code terminal, open this file's folder and run:
// Compile: g++ -std=c++17 -Wall -Wextra -pedantic 18_tracing_memory.cpp -o 18_tracing_memory.exe
// Run:     .\18_tracing_memory.exe
// Each lesson has its own main(); compile one .cpp file at a time.

#include <iostream>
using namespace std;

// Study guide section 18: a worked trace. Assume both allocations succeed.
// Before running, follow the target of each pointer and count live allocations.
int main() {
    cout << "1. Count allocations and record their kind\n";
    int* A = new int[2]{10, 20}; // Allocation 1: array. Owner: A.
    int* B = new int[3]{30, 40, 50}; // Allocation 2: array. Owner: B.
    int& r = A[0]; // Alias to the first integer of allocation 1.
    r += 1;
    cout << "A[0] = " << A[0] << '\n'; // 11. Two live allocations.

    cout << "\n2. Before reassignment, account for the old allocation\n";
    // A = B here would leak allocation 1 if no usable cleanup address remained.
    delete[] A; // Allocation 1 released. r now dangles: stop using it.
    A = B; // Both pointers reach allocation 2. B remains its cleanup owner.
    // r does not follow A to the new target. Never read or write r again.
    cout << "A[1] = " << A[1] << '\n'; // 40. One live allocation.

    cout << "\n3. Finish all uses before the final release\n";
    A[1] += 2;
    cout << "B[1] = " << B[1] << '\n'; // 42: same array as A.
    delete[] B; // Allocation 2 released exactly once. Both pointers dangle.
    A = nullptr;
    B = nullptr;
    cout << "End: two allocations, two releases, zero live allocations.\n";
    // No second delete through A; no reads through r, A, or B after release.

    // For any code question:
    // 1. Count new expressions and distinguish objects from arrays.
    // 2. Track pointer targets separately from reference targets and values.
    // 3. Check whether reassignment loses a required cleanup address.
    // 4. Match delete/delete[] and release each allocation exactly once.
    // 5. Mark ALL aliases dangling after deletion and reject further access.
    // 6. At scope exit, account for destructors and any remaining allocations.
    return 0;
}
