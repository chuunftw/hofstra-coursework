// Open this folder in the VS Code terminal.
// Compile: g++ -std=c++17 -Wall -Wextra -pedantic 10_weak_ptr.cpp -o 10_weak_ptr.exe
// Run:     .\10_weak_ptr.exe
// One standalone program per topic; compile one .cpp file at a time.
// Study guide topic 10: weak_ptr.
// Read, predict, run, then change one value and predict again.

#include <cassert>
#include <functional>
#include <iostream>
#include <memory>
#include <stdexcept>
#include <utility>
#include <vector>
using namespace std;

// weak_ptr observes a shared ownership group without adding a strong owner.
// lock() returns a shared_ptr if the object is still alive, or an empty shared_ptr otherwise; always check it.
// Strong ownership cycles can keep counts above zero forever.
// Use a weak link where the relationship should not keep an object alive.
// Predict: Why does the previous link below not prevent cleanup?

struct Node {
    int item;
    shared_ptr<Node> next;
    weak_ptr<Node> previous;
    explicit Node(int n) : item(n) {}
    ~Node() { cout << "Destroy node " << item << '\n'; }
};
int main() {
    weak_ptr<Node> watch;
    cout << "1. Forward owner, backward observer\n";
    {
        auto first = make_shared<Node>(1);
        auto second = make_shared<Node>(2);
        first->next = second;
        second->previous = first; // Does not increase first's strong count.
        watch = first;
        assert(first.use_count() == 1 && second.use_count() == 2);
        if (auto previous = second->previous.lock()) {
            cout << "previous item = " << previous->item << '\n'; // 1
            assert(first.use_count() == 2); // Temporary strong owner.
        }
        assert(first.use_count() == 1);
        // If previous were shared_ptr, these two links would form a strong cycle.
    } // Destroy node 1, then node 2.
    cout << "\n2. Check after owners disappear\n";
    cout << "expired = " << boolalpha << watch.expired() << '\n'; // true
    auto attempt = watch.lock();
    assert(!attempt && watch.expired());
    // cout << attempt->item; // Invalid: failed lock returns empty.
}
