// Open this folder in the VS Code terminal.
// Compile: g++ -std=c++17 -Wall -Wextra -pedantic 07_references_and_borrowing.cpp -o 07_references_and_borrowing.exe
// Run:     .\07_references_and_borrowing.exe
// One standalone program per topic; compile one .cpp file at a time.
// Study guide topic 7: References and borrowing.
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

// SECTION 1: Borrowing the owner versus borrowing the target
// unique_ptr<int>& aliases the owner object.
// int& bound to *owner aliases the heap integer.
// Moving ownership empties the source owner but does not move the integer, so a reference to the integer can remain valid while the new owner keeps it alive.
// Neither reference extends its referent's lifetime.
// Predict: After the move below, why is value_ref usable while *owner_ref is invalid?
namespace section_1 {
void run() {
    cout << "1. Two different things to borrow\n";
    auto owner = make_unique<int>(5);
    unique_ptr<int>& owner_ref = owner;
    int& value_ref = *owner;
    auto destination = move(owner);
    cout << "owner_ref empty = " << boolalpha << !owner_ref << '\n'; // true
    cout << "value_ref = " << value_ref << '\n'; // 5
    assert(!owner_ref && value_ref == 5);
    // cout << *owner_ref; // Invalid: the OWNER is now empty.

    cout << "\n2. The target is still alive\n";
    value_ref += 2;
    cout << "destination value = " << *destination << '\n'; // 7
    assert(*destination == 7);
    destination.reset(); // value_ref now dangles: do not use it.
    owner_ref = make_unique<int>(20); // Reuses owner through its alias.
    cout << "reused owner = " << *owner << '\n'; // 20
    assert(*owner == 20);
}
}

// SECTION 2: Reseatable borrowing
// An ordinary reference stays bound to the same object.
// reference_wrapper holds a non-owning reference-like handle that can be reassigned.
// Its get() returns a reference.
// The professor's borrow class illustrates the same basic idea with a private raw pointer.
// Neither wrapper keeps the target alive.
// Predict: What does r = b change: the old integer a, or which integer r observes?
namespace section_2 {
template<class T>
class Borrow {
    T* ptr;
public:
    explicit Borrow(T& value) : ptr(&value) {}
    void rebind(T& value) { ptr = &value; }
    T& operator*() const { return *ptr; }
};
void run() {
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
}

// SECTION 3: Traversing owned structures
// A vector can hold unique_ptr elements.
// Iterate by reference to avoid copying owners.
// A linked list can also use unique_ptr links; a non-owning pointer can traverse it without transferring ownership.
// Recursion with reference parameters is another approach, but C++ does not guarantee tail-call optimization.
// Predict: Why would for (auto p : values) fail when values holds unique_ptr objects?
namespace section_3 {
struct Node {
    int item;
    unique_ptr<Node> next;
    explicit Node(int value) : item(value) {}
};
void print_recursive(const unique_ptr<Node>& node) {
    if (!node) return;
    cout << node->item << ' ';
    print_recursive(node->next);
}
void run() {
    cout << "1. Vector of owners\n";
    vector<unique_ptr<int>> values;
    values.push_back(make_unique<int>(2));
    values.push_back(make_unique<int>(4));
    int sum = 0;
    for (const auto& p : values) { cout << *p << ' '; sum += *p; }
    cout << '\n'; // 2 4
    assert(sum == 6);
    // for (auto p : values) {} // Compile error: copies each unique_ptr.

    cout << "\n2. Observe a linked list without consuming it\n";
    auto head = make_unique<Node>(1);
    head->next = make_unique<Node>(2);
    sum = 0;
    for (const Node* current = head.get(); current; current = current->next.get()) {
        cout << current->item << ' ';
        sum += current->item;
    }
    cout << '\n'; // 1 2
    assert(head && head->next && sum == 3);
    print_recursive(head); // 1 2 again: still intact.
    cout << '\n';
} // Tiny teaching list; deep recursive destruction can exhaust the stack.
}

int main() {
    cout << "\n=== Section 1: Borrowing the owner versus borrowing the target ===\n";
    section_1::run();
    cout << "\n=== Section 2: Reseatable borrowing ===\n";
    section_2::run();
    cout << "\n=== Section 3: Traversing owned structures ===\n";
    section_3::run();
}
