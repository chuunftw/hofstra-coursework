// Open this folder in the VS Code terminal.
// Compile: g++ -std=c++17 -Wall -Wextra -pedantic 13_building_a_custom_smart_pointer.cpp -o 13_building_a_custom_smart_pointer.exe
// Run:     .\13_building_a_custom_smart_pointer.exe
// One standalone program per topic; compile one .cpp file at a time.
// Study guide topic 13: Building a custom smart pointer.
// Read, predict, run, then change one value and predict again.

#include <cassert>
#include <functional>
#include <iostream>
#include <memory>
#include <stdexcept>
#include <utility>
#include <vector>
using namespace std;

// Namespaces keep the small demonstrations independent within this one file.
// Start at main() at the bottom, then read one section at a time.

// SECTION 1: Inside a teaching smart pointer
// This small managed pointer follows the professor's idea: private raw pointer, private adoption constructor, factory friend, destructor, disabled copies, move operations, and a runtime lock.
// It handles single objects of the same type only.
// The lock is an educational policy, not thread synchronization or a general memory-safety guarantee.
// Unlike the packet example, this version checks both source and destination before move assignment.
// Predict: Why must a rejected move leave both pointers unchanged?
namespace section_1 {
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
void run() {
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
    c = move(same); // Check aliasing between source and destination.
    assert(*c == 7);
    cout << "c = " << *c << '\n'; // 7
}
// This is a learning implementation, not a replacement for std::unique_ptr.
// It omits arrays, custom deleters, cross-type moves, and other library features.
// A lock does not stop destruction or mutation through * / ->.
}

// SECTION 2: Packet corrections and a final ownership trace
// Use the packet for its learning sequence, with these corrections: get() retains ownership; moved-from unique_ptr objects remain alive and reusable; move itself is a cast; unique_ptr can transfer into shared_ptr; four shared handles mean count four.
// Raw observers can coexist with one unique owner.
// The packet's assignment operators should conventionally return the destination as T&.
// Generic moved-from objects are not all guaranteed empty.
// Predict: Trace every owner and strong count below before running it.
namespace section_2 {
void run() {
    cout << "1. Observe, move, then share\n";
    auto a = make_unique<int>(10);
    int* observer = a.get(); // a retains ownership.
    auto b = move(a);
    assert(!a && *observer == 10); // b still keeps the integer alive.
    shared_ptr<int> shared = move(b); // Supported unique -> shared conversion.
    assert(!b && shared.use_count() == 1);
    weak_ptr<int> weak = shared;
    {
        auto copy = shared;
        assert(shared.use_count() == 2);
        auto locked = weak.lock();
        cout << "inside count = " << shared.use_count() << '\n'; // 3
        assert(locked && shared.use_count() == 3);
    }
    assert(shared.use_count() == 1);
    shared.reset();
    observer = nullptr; // Its former target has been destroyed.
    assert(weak.expired());
    cout << "expired = " << boolalpha << weak.expired() << '\n'; // true

    cout << "\n2. Reuse the original owner\n";
    a = make_unique<int>(99);
    cout << "a = " << *a << '\n'; // 99
    assert(*a == 99);
    // unique_ptr<int> back = shared; // No automatic shared -> unique conversion.
    // A unique_ptr cannot test whether a raw address already has another owner.
    // Avoid forming two owners from the same raw address.
}
}

int main() {
    cout << "\n=== Section 1: Inside a teaching smart pointer ===\n";
    section_1::run();
    cout << "\n=== Section 2: Packet corrections and a final ownership trace ===\n";
    section_2::run();
}
