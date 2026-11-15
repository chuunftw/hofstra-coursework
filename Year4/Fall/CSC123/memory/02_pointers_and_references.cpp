// In the VS Code terminal, open this file's folder and run:
// Compile: g++ -std=c++17 -Wall -Wextra -pedantic 02_pointers_and_references.cpp -o 02_pointers_and_references.exe
// Run:     .\02_pointers_and_references.exe
// Each lesson has its own main(); compile one .cpp file at a time.

#include <iostream>
using namespace std;

// Section 2: a reference is an alias for one object.
// Originally ptrVSref.cpp; also reviews the basic symbols from section 1.
int main() {
    // Based on sections 1-2 of References_and_Heap_Study_Guide.md
    // and questions 1-2 of Memory_Practice_Quiz.md.
    int* ptr;  // A pointer stores an address. Assign it before using it.
    int var = 7;
    int foo = 21;

    ptr = &var; // &var means "the address of var" in this expression.

    int& ref = *ptr;  // A reference is another name for var, not for ptr.
    // In this declaration, & means "reference"; *ptr accesses var.
    //cout << "ptr: " << ptr << '\n';
    cout << "1. Starting values\n";
    cout << "var: " << var << '\n';
    cout << "foo: " << foo << '\n';
    cout << "Address stored in ptr: " << ptr << '\n';
    cout << "Value pointed to by ptr: " << *ptr << '\n';
    cout << "Value through ref: " << ref << '\n';
    cout << "&var: " << &var << ", &ref: " << &ref << '\n';
    // &ref is the address of var: ref is an alias for that same object.
    // Actual addresses can differ each time you run the program.

    cout << "\n2. Both can change var\n";
    *ptr = 10;  // Follow the pointer and change var to 10.
    cout << "After *ptr = 10: var = " << var << '\n';
    ref += 2;   // Using ref directly changes var to 12; no * is needed.
    cout << "After ref += 2: var = " << var << '\n';

    cout << "\n3. A pointer can change its target\n";
    ptr = &foo;  // Changes ptr itself. It now points to foo, not var.
    // ref stays bound to var, even though it was initialized using *ptr.
    *ptr = 30;   // Changes foo because that is ptr's current target.
    ref = 15;    // Still changes var.
    cout << "var = " << var << ", foo = " << foo << '\n'; // 15, 30
    cout << "*ptr = " << *ptr << ", ref = " << ref << '\n'; // 30, 15

    cout << "\n4. Assignment does not rebind a reference\n";
    ref = foo;  // Copies foo's value into var. ref still aliases var.
    ref++;      // Increments var, leaving foo unchanged.
    cout << "var = " << var << ", foo = " << foo << '\n'; // 31, 30
    cout << "ref = " << ref << ", *ptr = " << *ptr << '\n'; // 31, 30

    cout << "\n5. A pointer can have no target\n";
    ptr = nullptr;
    if (ptr == nullptr) {
        cout << "ptr has no target; do not dereference it.\n";
    }
    // A valid reference must bind to an object when initialized.
    // int& missing;       // Invalid: no object to refer to.
    // int& bad = nullptr; // Invalid: nullptr is not an int object.
    cout << "ref still refers to var: " << ref << '\n'; // 31
    // References can dangle if their object dies; they do not keep it alive.
    // var and foo live until main ends. Neither was allocated with new,
    // so do not use delete on their addresses.

    return 0;
}
