// In the VS Code terminal, open this file's folder and run:
// Compile: g++ -std=c++17 -Wall -Wextra -pedantic 13_structs_and_destructors.cpp -o 13_structs_and_destructors.exe
// Run:     .\13_structs_and_destructors.exe
// Each lesson has its own main(); compile one .cpp file at a time.

#include <iostream>
using namespace std;

// Study guide section 13.
struct Account {
    double balance;
    Account(double initial) : balance(initial) {} // Initialize the member.
    ~Account() { cout << "Destroy Account with balance " << balance << '\n'; }
};

struct Buffer {
    int* cells;
    Buffer(int n) : cells(new int[n]{}) {
        cout << "Buffer constructor allocates its array.\n";
    }
    ~Buffer() { // Runs when the Buffer object is destroyed.
        delete[] cells;
        cout << "Buffer destructor releases its array.\n";
    }
    // This lesson forbids copying because a destructor alone is insufficient.
    // = delete disables an operation; it does NOT free memory here.
    Buffer(const Buffer&) = delete;
    Buffer& operator=(const Buffer&) = delete;
    // Section 16 supplies safe copy operations instead.
};

int main() {
    cout << "1. Access members with . and ->\n";
    {
        Account local(100);
        Account* remote = new Account(200);
        local.balance += 10;   // . accesses a member through an object.
        remote->balance += 10; // -> accesses a member through a pointer.
        // remote->balance means the same thing as (*remote).balance.
        cout << "local = " << local.balance << '\n';   // 110
        cout << "remote = " << remote->balance << '\n'; // 210
        delete remote; // Destroys the heap Account now: prints 210.
        remote = nullptr;
        cout << "Leaving the inner scope next.\n";
    } // Destroys the automatic Account: prints 110.

    cout << "\n2. Connect object lifetime to resource cleanup\n";
    {
        Buffer buffer(3); // Buffer is automatic; its array is on the heap.
        buffer.cells[0] = 7;
        cout << "buffer.cells[0] = " << buffer.cells[0] << '\n'; // 7
    } // ~Buffer() releases the array automatically here.
    // This lifetime-based resource management is called RAII.
    // Without our destructor, a raw pointer member would not free its target.
    return 0;
}
