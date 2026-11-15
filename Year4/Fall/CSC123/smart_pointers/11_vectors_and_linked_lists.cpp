// In the VS Code terminal, open this file's folder and run:
// Compile: g++ -std=c++17 -Wall -Wextra -pedantic 11_vectors_and_linked_lists.cpp -o 11_vectors_and_linked_lists.exe
// Run:     .\11_vectors_and_linked_lists.exe
// Each lesson has its own main(); compile one .cpp file at a time.
// Study guide section 11: Traversing owned structures.
// Predict the output, run, then change one value and try again.

#include <cassert>
#include <functional>
#include <iostream>
#include <memory>
#include <stdexcept>
#include <utility>
#include <vector>
using namespace std;

// A vector can hold unique_ptr elements.
// Iterate by reference to avoid copying owners.
// A linked list can also use unique_ptr links; a non-owning pointer can traverse it without transferring ownership.
// Recursion with reference parameters is another approach, but C++ does not guarantee tail-call optimization.
// Predict: Why would for (auto p : values) fail when values holds unique_ptr objects?

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
int main() {
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
