// In the VS Code terminal, open this file's folder and run:
// Compile: g++ -std=c++17 -Wall -Wextra -pedantic 10_reference_wrappers.cpp -o 10_reference_wrappers.exe
// Run:     .\10_reference_wrappers.exe
// Each lesson has its own main(); compile one .cpp file at a time.
// Study guide section 10: Reseatable borrowing.
// Predict the output, run, then change one value and try again.

#include <cassert>
#include <functional>
#include <iostream>
#include <memory>
#include <stdexcept>
#include <utility>
#include <vector>
using namespace std;

// An ordinary reference stays bound to the same object.
// reference_wrapper holds a non-owning reference-like handle that can be reassigned.
// Its get() returns a reference.
// The professor's borrow class illustrates the same basic idea with a private raw pointer.
// Neither wrapper keeps the target alive.
// Predict: What does r = b change: the old integer a, or which integer r observes?

template<class T>
class Borrow {
    T* ptr;
public:
    explicit Borrow(T& value) : ptr(&value) {}
    void rebind(T& value) { ptr = &value; }
    T& operator*() const { return *ptr; }
};
int main() {
    cout << "1. Standard reference_wrapper\n";
    int a = 1, b = 5;
    reference_wrapper<int> r = a;
    r.get() = 2; // Changes a.
    r = b; // Rebinds wrapper to b.
    r.get() += 1;
    cout << "a = " << a << ", b = " << b << '\n'; // 2, 6
    assert(a == 2 && b == 6);

    cout << "\n2. Borrow an owner object\n";
    auto p1 = make_unique<int>(10);
    auto p2 = make_unique<int>(20);
    Borrow<unique_ptr<int>> borrowed(p1);
    borrowed.rebind(p2);
    cout << "**borrowed = " << **borrowed << '\n'; // 20
    assert(p1 && p2 && **borrowed == 20);
    // First * accesses unique_ptr; second * accesses its integer.
}
