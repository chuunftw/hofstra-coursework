# 14. Memory Review

Determine if each of the following C++ functions contain any memory errors.
DESCRIBE EACH ERROR.

Transcribed from the two supplied photos. Answers are added below each question.

## 1.

```cpp
void f1() {
    int* a = new int(1);
    int* b = new int(2);
    a = b;
    delete a;
}
```

**Answer:**

The int containing 1 leaks: a = b overwrites its only pointer without deleting it.
Both pointers then point to the int containing 2. delete a frees that int once.
Both pointers become dangling, but neither is dereferenced or deleted again.

## 2.

```cpp
int* f2() {
    int x = 1;
    int* a = new int(2);
    int* b = new int(3);
    delete a;
    a = &x;
    return b;
}
```

**Answer:**

There is no memory error on the normal execution path inside this function.
delete a frees the int containing 2; assigning &x to a is valid while x lives.
a is local and is not returned or used after x dies.
The returned b points to a live heap int containing 3. The caller must eventually
delete it; otherwise that allocation leaks. Returning b does not itself leak it.
Exception edge case: if the second new throws, the first allocation leaks.

## 3.

```cpp
void f3() {
    unique_ptr<int> x = make_unique<int>(2);
    unique_ptr<int> y = make_unique<int>(3);
    x = y;
}
```

**Answer:**

This does not compile: unique_ptr cannot be copied because ownership is exclusive.
Thus this is a compile-time error, not an executed memory error.
Use x = move(y); to transfer ownership. This deletes x's old int containing 2,
makes x own the int containing 3, and leaves y empty (nullptr).

## 4. What are the "Rule of Three" and the "Rule of Zero"?

**Answer:**

Rule of Three: If a class needs a custom destructor, copy constructor, or copy
assignment operator to manage a resource, it usually needs all three. Copies
must handle ownership correctly instead of accidentally sharing an owning raw
pointer, which could cause double deletion.

Rule of Zero: Let resource-managing members such as unique_ptr, vector, and
string handle cleanup and ownership. Avoid defining your own destructor,
copy/move constructors, and copy/move assignment operators when the members'
default behavior is appropriate. A unique_ptr member makes copying disabled
by default; Rule of Zero does not mean every class must be copyable.

## 5. Describe what happens during a "transfer of ownership" between
unique pointers:
```cpp
a = move(b);
```

**Answer:**

For distinct, compatible unique_ptr objects, a first releases its old owned
object (if any), then takes ownership of b's object. b becomes empty (nullptr).
The transferred object stays at the same address; it is not copied or moved.
a will delete it when a is destroyed or reset, unless ownership moves again.
move(b) enables move assignment; move itself is a cast, not the transfer.

## 6. Give a specific example of something bad that can happen when unique_ptr
are mixed with raw pointers (write code).

**Answer:**

```cpp
auto owner = std::make_unique<int>(42);
int* raw = owner.get();
delete raw;  // BAD: deletes the int while owner still thinks it owns it.
// When owner is destroyed, it tries to delete the same int again:
// double deletion, which is undefined behavior.
```

get() only provides an observing pointer; it does not transfer ownership.
Do not manually delete that pointer.

## 7. Is it possible to have a memory leak even with the exclusive use of
unique_ptr and make_unique (with no raw pointers).

**Answer:**

Yes. You can construct an unreachable ownership cycle using moves:

```cpp
struct Node {
    std::unique_ptr<Node> next;
};
```

```cpp
auto head = std::make_unique<Node>();            // Node A
head->next = std::make_unique<Node>();           // A owns B
head->next->next = std::move(head);              // B now owns A
```

After the last statement, head is empty. A owns B and B owns A, with no
external owner left to start destruction. Both nodes leak. Each node still
has exactly one owner, so unique ownership alone does not prevent cycles.
Ordinary acyclic ownership with unique_ptr automatically cleans up resources.

## 8. Explain why references are safer than raw pointers.

**Answer:**

A reference must be initialized to refer to an object, cannot be reseated to
another object, and has no valid null state. It also does not support pointer
arithmetic. These restrictions prevent several common raw-pointer mistakes.
However, references do not manage lifetime: a reference can still dangle if
its object is destroyed. Using a dangling reference is undefined behavior.
