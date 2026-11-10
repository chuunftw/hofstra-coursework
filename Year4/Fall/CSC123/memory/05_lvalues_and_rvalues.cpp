// In the VS Code terminal, open this file's folder and run:
// Compile: g++ -std=c++17 -Wall -Wextra -pedantic 05_lvalues_and_rvalues.cpp -o 05_lvalues_and_rvalues.exe
// Run:     .\05_lvalues_and_rvalues.exe
// Each lesson has its own main(); compile one .cpp file at a time.

#include <iostream>
#include <utility>
using namespace std;

// Study guide section 5. "Left" and "right" of = are not complete definitions.
int main() {
    int x = 1;
    int& a = x; // x identifies an existing object: an lvalue expression.
    a = 8;
    cout << "1. An lvalue reference aliases x: " << x << '\n'; // 8

    // int& b = 3; // Invalid: a non-const int& cannot bind to this temporary.
    const int& c = 3; // Valid; the temporary lives until c's scope ends.
    cout << "\n2. A const reference can bind to a temporary: " << c << '\n';
    // c++; // Invalid: modification through c is forbidden.
    // A const object's name is still an lvalue, despite being read-only.

    int&& d = 3; // && declares an rvalue reference, not reference-to-reference.
    d++; // The temporary integer can be modified through d.
    cout << "\n3. The temporary after d++: " << d << '\n'; // 4
    // int&& e = x; // Invalid: x is an lvalue expression.
    int& alias = d; // Valid: the NAME d is an lvalue expression.
    alias++;
    cout << "d after alias++: " << d << '\n'; // 5

    cout << "\n4. move() alone does not transfer data\n";
    int&& r = std::move(x); // Produces an expression that can bind to int&&.
    r = 12; // r aliases x; no new integer was created here.
    cout << "x = " << x << '\n'; // 12
    // Full move constructors are outside this study guide's scope.
    return 0;
}
