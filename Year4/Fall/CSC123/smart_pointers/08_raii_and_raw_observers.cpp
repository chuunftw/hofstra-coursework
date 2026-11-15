// In the VS Code terminal, open this file's folder and run:
// Compile: g++ -std=c++17 -Wall -Wextra -pedantic 08_raii_and_raw_observers.cpp -o 08_raii_and_raw_observers.exe
// Run:     .\08_raii_and_raw_observers.exe
// Each lesson has its own main(); compile one .cpp file at a time.
// Study guide section 8: RAII and raw observers.
// Predict the output, run, then change one value and try again.

#include <cassert>
#include <functional>
#include <iostream>
#include <memory>
#include <stdexcept>
#include <utility>
#include <vector>
using namespace std;

// RAII ties resource cleanup to an owning object's destruction, including stack unwinding after an exception.
// Prefer make_unique for normal allocation.
// get() returns a non-owning raw pointer and DOES NOT release ownership.
// release() does relinquish ownership without deleting, so avoid it unless responsibility is explicitly passed elsewhere.
// Predict: Why must you never call delete on the result of owner.get() while owner still owns it?

struct Resource {
    int& live;
    explicit Resource(int& count) : live(count) { ++live; }
    ~Resource() { --live; cout << "Resource cleaned up\n"; }
};
int main() {
    cout << "1. Cleanup also happens on exceptions\n";
    int live = 0;
    try {
        auto owner = make_unique<Resource>(live);
        assert(live == 1);
        throw runtime_error("example");
    } catch (const runtime_error&) {
        cout << "Caught exception; live = " << live << '\n'; // 0
    }
    assert(live == 0);

    cout << "\n2. get() observes without releasing\n";
    auto owner = make_unique<int>(9);
    int* observer = owner.get();
    *observer = 11;
    assert(owner && *owner == 11);
    cout << "owner still owns " << *owner << '\n'; // 11
    // delete observer; // Wrong: owner would later delete the same object.
    owner.reset();
    observer = nullptr; // It would otherwise dangle after reset.
    // unique_ptr<int> duplicate(owner.get()); // Never manufacture a second owner.
}
