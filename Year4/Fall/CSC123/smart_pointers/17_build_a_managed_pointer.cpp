// In the VS Code terminal, open this file's folder and run:
// Compile: g++ -std=c++17 -Wall -Wextra -pedantic 17_build_a_managed_pointer.cpp -o 17_build_a_managed_pointer.exe
// Run:     .\17_build_a_managed_pointer.exe
// Each lesson has its own main(); compile one .cpp file at a time.
// Study guide section 17: Inside a teaching smart pointer.
// Predict the output, run, then change one value and try again.

#include <cassert>
#include <functional>
#include <iostream>
#include <memory>
#include <stdexcept>
#include <utility>
#include <vector>
using namespace std;

// This small managed pointer follows the professor's idea: private raw pointer, private adoption constructor, factory friend, destructor, disabled copies, move operations, and a runtime lock.
// It handles single objects of the same type only.
// The lock is an educational policy, not thread synchronization or a general memory-safety guarantee.
// Unlike the packet example, this version checks both source and destination before move assignment.
// Predict: Why must a rejected move leave both pointers unchanged?

template<class T> class Managed;
template<class T, class... Args> Managed<T> make_managed(Args&&... args);

template<class T>
class Managed {
    T* ptr = nullptr;
    bool locked = false;
    explicit Managed(T* p) : ptr(p) {}
    template<class U, class... Args>
    friend Managed<U> make_managed(Args&&... args);
public:
    Managed() = default;
    ~Managed() { delete ptr; } // nullptr is safe.
    Managed(const Managed&) = delete;
    Managed& operator=(const Managed&) = delete;

    Managed(Managed&& other) {
        if (other.locked) throw logic_error("source locked");
        ptr = exchange(other.ptr, nullptr);
    }
    Managed& operator=(Managed&& other) {
        if (this == &other) return *this;
        if (locked || other.locked) throw logic_error("owner locked");
        delete ptr;
        ptr = exchange(other.ptr, nullptr);
        return *this;
    }
    T& operator*() const { return *ptr; } // Requires nonempty.
    T* operator->() const { return ptr; }
    explicit operator bool() const { return ptr != nullptr; }
    void lock() { locked = true; }
    void unlock() { locked = false; }
};
template<class T, class... Args>
Managed<T> make_managed(Args&&... args) {
    // forward preserves the argument's value category for T's constructor.
    return Managed<T>(new T(forward<Args>(args)...));
}
int main() {
    cout << "1. Reject a locked source\n";
    auto a = make_managed<int>(7);
    auto b = make_managed<int>(9);
    a.lock();
    try { b = move(a); assert(false); }
    catch (const logic_error&) { cout << "Move blocked\n"; }
    assert(*a == 7 && *b == 9);

    cout << "\n2. Unlock and transfer\n";
    a.unlock();
    b = move(a);
    assert(!a && *b == 7);
    auto c = move(b); // Move construction.
    assert(!b && *c == 7);

    cout << "\n3. Locked destination is also protected\n";
    auto d = make_managed<int>(11);
    c.lock();
    try { c = move(d); assert(false); }
    catch (const logic_error&) { cout << "Replacement blocked\n"; }
    assert(*c == 7 && *d == 11);
    c.unlock();
    Managed<int>& same = c;
    c = move(same); // Also handle aliasing between source and destination.
    assert(*c == 7);
    cout << "c = " << *c << '\n'; // 7
}
// This is a learning implementation, not a replacement for std::unique_ptr.
// It omits arrays, custom deleters, cross-type moves, and other library features.
// A lock does not stop destruction or mutation through * / ->.
