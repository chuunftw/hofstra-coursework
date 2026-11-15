// In the VS Code terminal, open this file's folder and run:
// Compile: g++ -std=c++17 -Wall -Wextra -pedantic 18_packet_corrections_and_trace.cpp -o 18_packet_corrections_and_trace.exe
// Run:     .\18_packet_corrections_and_trace.exe
// Each lesson has its own main(); compile one .cpp file at a time.
// Study guide section 18: Packet corrections and a final ownership trace.
// Predict the output, run, then change one value and try again.

#include <cassert>
#include <functional>
#include <iostream>
#include <memory>
#include <stdexcept>
#include <utility>
#include <vector>
using namespace std;

// Use the packet for its learning sequence, with these corrections: get() retains ownership; moved-from unique_ptr objects remain alive and reusable; move itself is a cast; unique_ptr can transfer into shared_ptr; four shared handles mean count four.
// Raw observers can coexist with one unique owner.
// The packet's assignment operators should conventionally return the destination as T&.
// Generic moved-from objects are not all guaranteed empty.
// Predict: Trace every owner and strong count below before running it.

int main() {
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
