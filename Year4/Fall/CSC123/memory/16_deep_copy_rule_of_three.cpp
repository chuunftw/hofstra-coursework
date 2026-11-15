// In the VS Code terminal, open this file's folder and run:
// Compile: g++ -std=c++17 -Wall -Wextra -pedantic 16_deep_copy_rule_of_three.cpp -o 16_deep_copy_rule_of_three.exe
// Run:     .\16_deep_copy_rule_of_three.exe
// Each lesson has its own main(); compile one .cpp file at a time.

#include <iostream>
using namespace std;

// Study guide section 16. Start at main(), then follow the operation it calls.
// This learning example uses small positive sizes and valid element indices.
struct Buffer {
    int size;
    int* cells;

    Buffer(int n) : size(n), cells(new int[n]{}) {
        cout << "Constructor: allocate " << size << " integers.\n";
    }

    // Rule of Three, operation 1: destructor releases this object's resource.
    ~Buffer() {
        cout << "Destructor: release " << size << " integers.\n";
        delete[] cells;
    }

    // Operation 2: copy constructor initializes a NEW Buffer from another one.
    Buffer(const Buffer& other)
        : size(other.size), cells(new int[other.size]) {
        for (int i = 0; i < size; i++) cells[i] = other.cells[i];
        cout << "Copy constructor: allocate and copy " << size << " integers.\n";
        // Same values, but a separate heap array. other remains unchanged.
    }

    // Operation 3: copy assignment replaces an ALREADY EXISTING Buffer's data.
    Buffer& operator=(const Buffer& other) {
        if (this == &other) { // this is destination's address; &other is source's.
            cout << "Self-assignment: keep existing data.\n";
            return *this;
        }
        // Allocate before deleting: if new throws, existing data is intact.
        int* replacement = new int[other.size];
        for (int i = 0; i < other.size; i++) replacement[i] = other.cells[i];
        delete[] cells; // Release the destination's OLD array.
        cells = replacement;
        size = other.size;
        cout << "Copy assignment: replace data with " << size << " integers.\n";
        return *this; // Return this destination object by reference.
    }
};

void inspect(const Buffer& b) {
    cout << "Inspect by const reference: first value = " << b.cells[0] << '\n';
    // No Buffer copy is made. This function only reads.
    // A raw pointer member has shallow constness: const Buffer& alone does NOT
    // make the pointed-to integers const. Avoid writing them in this function.
}

void modify_copy(Buffer b) { // Calls the copy constructor for our lvalue argument.
    b.cells[0] = 500;
    cout << "Inside by-value function: " << b.cells[0] << '\n'; // 500
} // Destroys the independent parameter copy.

int main() {
    cout << "1. Copy construction: create B from A\n";
    Buffer A(3);
    A.cells[0] = 7;
    Buffer B = A; // B is being declared: copy CONSTRUCTOR.
    B.cells[0] = 99;
    cout << "A[0] = " << A.cells[0] << ", B[0] = " << B.cells[0] << '\n'; // 7, 99
    cout << "Separate arrays: " << boolalpha << (A.cells != B.cells) << '\n'; // true

    cout << "\n2. Copy assignment: replace C's existing data\n";
    Buffer C(5);
    C = A; // C already exists: copy ASSIGNMENT.
    C.cells[0] = 42;
    cout << "A[0] = " << A.cells[0] << ", C[0] = " << C.cells[0] << '\n'; // 7, 42
    cout << "C.size = " << C.size << '\n'; // 3

    cout << "\n3. Self-assignment\n";
    B = B;
    cout << "B[0] remains " << B.cells[0] << '\n'; // 99

    cout << "\n4. Reference parameter versus value parameter\n";
    inspect(A); // No copy-constructor message.
    modify_copy(A); // Copy-constructor message, then destructor for the copy.
    cout << "Original A[0] remains " << A.cells[0] << '\n'; // 7
    // Returning an object by value can use copy elision or a move. Do not
    // assume every return causes a copy-constructor call.

    cout << "\n5. Scope ends: destroy C, B, then A\n";
    // Each object owns a different allocation, so each deletes its own once.
    // Production code often uses vector<int> to manage this resource for us.
    return 0;
}
