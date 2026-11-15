// In the VS Code terminal, open this file's folder and run:
// Compile: g++ -std=c++17 -Wall -Wextra -pedantic 17_packet_corrections.cpp -o 17_packet_corrections.exe
// Run:     .\17_packet_corrections.exe
// Each lesson has its own main(); compile one .cpp file at a time.

#include <iostream>
using namespace std;

// Study guide section 17: runnable checks for the packet's main corrections.
int main() {
    cout << "1. Deleting nullptr is safe\n";
    int* p = nullptr;
    delete p;
    delete[] p;
    cout << "Both null deletes completed.\n";

    cout << "\n2. The corrected reference trace\n";
    int x = 5, y = 6;
    int& rx = x;
    rx += 1; // x becomes 6.
    rx = y;  // Copies 6 into x. rx still aliases x.
    rx += 1; // x becomes 7; y remains 6.
    cout << "x = " << x << ", y = " << y << '\n'; // 7, 6 (not 6, 6).

    cout << "\n3. Corrections to keep in mind\n";
    cout << "Non-null does not prove that a target is alive.\n";
    cout << "References can dangle when their target dies.\n";
    cout << "Undefined behavior has no guaranteed output or crash.\n";
    cout << "Deleting an array of raw pointers does not delete their targets.\n";
    // See files 09, 10, and 12 for the corresponding runnable repairs.
    // swap_values(4, 5) with int& parameters is invalid; pass variables (file 03).
    // Allocator reuse in a broken example is not a guaranteed sequence of events.
    // Garbage collection reclaims unreachable managed objects. Its costs vary;
    // there is no universal fixed memory multiplier. These raw-pointer examples
    // instead require explicit ownership and matching releases.
    return 0;
}
