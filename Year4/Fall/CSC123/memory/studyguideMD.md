# Study Guide: References, Pointers, and Heap Memory

Based on the supplied **References versus Pointers** and **Heap Allocated Memory Part I** packets. The supplied old quizzes guide the practice format: trace short fragments, explain behavior, compare similar code, and implement a small function or fix.

Priority: recognize **memory leaks**, **double free**, and **use after free**, explain what caused each, and repair the ownership and lifetime. Also study the reference material and the Rule of Three. Your friend's topic tip is an emphasis, not a guarantee of quiz coverage.

## 1. Read the symbols in context

```cpp
int x = 2;
int* p = &x;
int& r = x;
int** pp = &p;
```

| Syntax | Meaning |
| --- | --- |
| `int* p` | Declare a pointer to an integer. |
| `&x` | Get the address of x. |
| `*p` | Access the object p points to. |
| `int& r = x` | Bind an lvalue reference to x. |
| `int** pp = &p` | Store the address of the pointer variable p. |
| `**pp` | Follow pp to p, then p to x. |
| `int&& rr = 3` | Bind an rvalue reference to a temporary integer. |

`*` and `&` mean different things in declarations and expressions. A pointer contains an address; dereferencing accesses the object at that address.

```cpp
**pp = 9;
cout << x;  // 9
```

`int** pp = &&x;` is not the way to take the address of an address. First store `&x` in a pointer variable, then take that variable's address.

## 2. A reference is an alias for one object

Once initialized, a reference continues to refer to the same object. Assignment through it changes that object.

```cpp
int x = 4, y = 8;
int& r = x;
r = y;      // x becomes 8; r still aliases x
r++;        // x becomes 9
cout << x << " " << y;  // 9 8
```

A pointer can be reassigned to a different object:

```cpp
int* p = &x;
p = &y;
(*p)++;     // changes y
```

Binding a reference through a pointer does not make the reference follow future pointer changes:

```cpp
int x = 1, y = 2;
int* p = &x;
int& r = *p;
p = &y;
r *= 10;
cout << x << " " << y;  // 10 2
```

For output questions, track pointer targets and reference targets separately from integer values.

## 3. Passing by value, reference, and pointer

```cpp
void by_value(int x) { x++; }
void by_reference(int& x) { x++; }
void by_pointer(int* x) { (*x)++; }

int n = 5;
by_value(n);       // n stays 5
by_reference(n);   // n becomes 6
by_pointer(&n);    // n becomes 7
```

The by-value parameter is a copy. The reference parameter aliases the caller's object. The pointer parameter is a copy of an address, so dereferencing it can modify the caller's object. Reassigning that local pointer parameter alone does not reassign a caller's pointer variable.

```cpp
void swap_values(int& a, int& b) {
    int temp = a;
    a = b;
    b = temp;
}
```

Call it with variables, such as `swap_values(x, y)`. The packet's `swap(4,5)` example is a typo: non-const `int&` parameters cannot bind to those literals.

For larger objects, `const Buffer&` lets a function inspect the existing object without copying it or modifying it through that reference.

## 4. Reference loops and pointer arithmetic

```cpp
int A[] = {1, 2, 3};
for (int x : A) x += 2;   // modifies copies; A unchanged
for (int& r : A) r += 2;  // modifies elements; A is {3,4,5}
```

Each iteration initializes a new reference to its element. An existing reference is not being rebound.

```cpp
int* p = A;
cout << *(p + 1);  // A[1], which is 4
p++;              // p now points to A[1]
```

`A[i]` is equivalent to `*(A + i)`. Pointer arithmetic steps in units of the pointed-to type, not single bytes. Stay within the array: a one-past-the-end pointer may be formed but must not be dereferenced. Incrementing an integer reference increments the integer, not an address.

## 5. Lvalues and rvalues

An lvalue expression identifies an object, such as `x`, `A[0]`, or `*p`. Literals like `3` and ordinary computed values like `x + 1` are rvalues. The packet's left/right assignment explanation is a starting intuition; a const object is still an lvalue even though you cannot assign to it.

```cpp
int x = 1;
int& a = x;          // valid
// int& b = 3;       // invalid
const int& c = 3;    // valid; cannot modify through c
int&& d = 3;        // valid
d++;                // modifies the temporary bound to d
// int&& e = x;      // invalid: x is an lvalue
```

`int&&` is an rvalue reference, not a reference to a reference. A named rvalue-reference variable is itself an lvalue expression when used by name.

With `<utility>`, `std::move(x)` produces an expression that can bind to an rvalue reference. **It does not itself transfer memory or ownership.** The move operation selected afterward determines what happens. This packet introduces the syntax; full move semantics belongs to the later heap packet, which was not supplied.

## 6. Stack versus heap: track two lifetimes

```cpp
void example() {
    int* A = new int[10];
    A[0] = 7;
    // Missing cleanup here would leak this allocation.
}
```

Here the local pointer variable A has automatic storage, described as the stack in the notes. The array is dynamically allocated on the heap. Returning from the function destroys the local pointer variable; it does not automatically delete the array.

| Object | Lifetime in this example |
| --- | --- |
| Local pointer A | Until the function scope ends. |
| Heap array | Until correctly released using `delete[]`. |

Heap allocation is useful for data whose size is determined at runtime or whose lifetime must extend beyond a function call. It brings an explicit responsibility to manage cleanup when using owning raw pointers.

Two lifetime failures matter:

- Data outlives every usable owning pointer: the allocation becomes unreachable and leaks.
- A pointer or reference is used after its target dies: dangling access, also called use after free for freed heap storage.

## 7. Match allocation and deallocation

```cpp
int* p = new int(10);
delete p;
p = nullptr;

int* A = new int[10];
delete[] A;
A = nullptr;
```

| Allocation | Matching release |
| --- | --- |
| `new int(10)` | `delete p` |
| `new account(100)` | `delete p` |
| `new int[10]` | `delete[] p` |
| Automatic local object or array | Automatic destruction at scope exit; do not delete it. |

Mismatching `new` with `delete[]`, or `new[]` with `delete`, is undefined behavior. Deleting an interior array pointer is also invalid: release using the original allocation's start address.

```cpp
int A[] = {1, 2, 3};
// delete[] A;  // invalid: A is an automatic array
```

`delete` releases the pointed-to allocation. It does not destroy the pointer variable or reset its stored value.

## 8. Memory leaks: lost or unreleased ownership

```cpp
void leak() {
    int* A = new int[4];
}  // allocation survives, but its only pointer is gone
```

Fix: release the allocation before scope exit, after its final use.

Another common trigger is overwriting the only address:

```cpp
int* A = new int[4];
int* B = new int[8];
A = B;  // the four-int array becomes unreachable here
delete[] B;
```

Fix:

```cpp
int* A = new int[4];
int* B = new int[8];
delete[] A;
A = B;
// use the eight-int array through A or B
delete[] B;
A = nullptr;
B = nullptr;
```

Setting an owning pointer to `nullptr` before releasing its allocation can itself create a leak. Assigning a pointer never automatically releases its previous pointee.

## 9. Double free: one allocation released twice

```cpp
int* A = new int[4];
int* B = A;
delete[] A;
delete[] B;  // invalid: same allocation
```

`B = A` copies the address. It does not allocate another array. Count allocations, not pointer names: this code has two pointer variables and one allocation.

Fix: finish all uses, then release the shared allocation once. Treat one pointer as the owner and the other as a non-owning observer.

```cpp
int* A = new int[4];
int* B = A;
B[0] = 5;
delete[] A;
A = nullptr;
B = nullptr;
```

Setting `A = nullptr` alone does not change B. An `if (B != nullptr)` check does not prove B points to live storage; a dangling pointer can be non-null.

## 10. Use after free: released too early

```cpp
int* A = new int[2];
A[1] = 40;
int* B = A;
delete[] A;
cout << B[1];  // undefined behavior
```

Fix: move deletion after the final use. Merely removing deletion can trade the dangling access for a leak.

Freed storage may be reused for a later allocation. A dangling pointer can then appear to access or corrupt that later object's data. Reuse is not guaranteed. For such code, the correct answer is **undefined behavior; no guaranteed output**, even if a particular run seems to work.

References can dangle too:

```cpp
int* p = new int(9);
int& r = *p;
delete p;
// cout << r;  // invalid: r's target has died
```

A reference does not keep heap storage alive.

## 11. Returning addresses and references

```cpp
int* bad_pointer() {
    int x = 10;
    return &x;
}

int& bad_reference() {
    int x = 10;
    return x;
}
```

Both refer to a local object that dies at function return. Return the integer by value when that is the intended result.

Returning a heap pointer can be valid:

```cpp
int* makearray(int n) {
    return new int[n];
}

int* A = makearray(5);
// use A
delete[] A;
```

The allocation outlives the function. Cleanup responsibility passes to the caller. A function using `new` does not necessarily need a `delete` inside that same function.

## 12. Arrays of pointers need cleanup at each allocation level

```cpp
int** A = new int*[3];
for (int i = 0; i < 3; i++)
    A[i] = new int(i);
```

There are four allocations: the array of pointer objects plus three individual integers.

```cpp
for (int i = 0; i < 3; i++)
    delete A[i];
delete[] A;
A = nullptr;
```

`delete[] A` destroys the pointer elements, but raw pointers do not delete what they point to. Delete the pointees first, while their addresses are still accessible.

## 13. Structs, member access, and destructors

```cpp
struct account {
    double balance;
    account(double initial) : balance(initial) {}
};

account local(100);
account* remote = new account(200);
local.balance += 10;
remote->balance += 10;  // equivalent to (*remote).balance += 10
delete remote;
```

An automatic struct object is destroyed at scope exit. A heap struct object is destroyed when correctly deleted. A destructor, named `~TypeName()`, can release resources owned by the object.

```cpp
struct Buffer {
    int* cells;
    Buffer(int n) : cells(new int[n]) {}
    ~Buffer() { delete[] cells; }
};
```

The automatic object can be only a small shell containing a pointer; its array still lives on the heap. The custom destructor connects destruction of the shell to release of its array. This is the resource-management idea commonly called RAII.

The compiler-generated destructor does not delete heap data through raw pointer members. By contrast, members that are resource-managing objects have their own destructors called automatically.

**Warning:** this Buffer definition is incomplete for safe copying. Its destructor alone does not solve ownership when objects are copied.

## 14. Resize without leaks or dangling reads

The packet's vector stores `tos` (number of occupied elements), `capacity` (allocated element count), and `cells` (pointer to storage).

```cpp
void resize() {
    unsigned int newcapacity = capacity * 2;
    int* replacement = new int[newcapacity];
    for (unsigned int i = 0; i < tos; i++)
        replacement[i] = cells[i];
    delete[] cells;
    cells = replacement;
    capacity = newcapacity;
}
```

Assume positive initial capacity and sizes that fit. Order: allocate replacement, copy live elements, release old array, adopt replacement. Deleting the old array before copying reads freed storage. Reassigning `cells` before preserving or releasing its old allocation loses ownership and leaks.

In `cells[tos++] = x`, use the current size as the index, then increment the size. In `cells[--tos]`, decrement size first, then use it as the index. Popping an int changes the logical size; it does not free the entire backing array.

Doubling capacity makes push amortized O(1): an individual resize takes O(n), but n pushes take O(n) total copying work. There are O(log n) growth allocations. This is background from the packet; memory correctness is the priority.

## 15. Shallow copying creates shared raw pointer values

```cpp
Buffer A(3);
Buffer B(5);
B = A;
```

Without custom copying, raw pointer members are copied as addresses. Two failures follow:

1. Assignment overwrites B's pointer, losing B's original allocation: a leak.
2. A and B now point to the same array. Both destructors try to release it: double free.

The default copy operation is memberwise copying. For raw pointers this copies addresses; it is not a recursive clone of their targets. Describing every C++ copy as a literal `memcpy` is an oversimplification, especially for members with their own copy behavior.

```cpp
Buffer A(3);
Buffer B = A;
```

This instead uses copy construction. With default copying it still causes shared ownership and double free, but there was no previous B allocation to lose.

## 16. Deep copy and the Rule of Three

A deep copy gives each Buffer its own allocation containing equivalent values.

```cpp
struct Buffer {
    int size;
    int* cells;

    Buffer(int n) : size(n), cells(new int[n]{}) {}

    ~Buffer() { delete[] cells; }

    Buffer(const Buffer& other)
        : size(other.size), cells(new int[other.size]) {
        for (int i = 0; i < size; i++)
            cells[i] = other.cells[i];
    }

    Buffer& operator=(const Buffer& other) {
        if (this == &other) return *this;

        int* replacement = new int[other.size];
        for (int i = 0; i < other.size; i++)
            replacement[i] = other.cells[i];

        delete[] cells;
        cells = replacement;
        size = other.size;
        return *this;
    }
};
```

| Operation | Example | Main responsibility |
| --- | --- | --- |
| Copy constructor | `Buffer B = A;` | Initialize a new object with independent storage. |
| Copy assignment | `B = A;` with B already alive | Replace existing contents and release old owned storage. |
| Destructor | B leaves scope, or `delete p` for a heap Buffer | Release owned storage once. |

The Rule of Three: when a class needs custom resource management through one of these operations, consider and define all three consistently for this owning raw-pointer design.

`this` is the destination object's address; `&other` is the source object's address. Equality detects self-assignment, such as `B = B`. `return *this` returns the destination object by reference, following the usual assignment convention.

The guide allocates replacement storage before releasing the old array. If allocation fails, the existing object is preserved. This improves on the packet's delete-first assignment code for this int-buffer example.

Passing a Buffer by value can call its copy constructor; passing by reference avoids that copy. Returning by value can use copy elision or a move rather than a copy. Do not assume a copy constructor always runs for every return statement.

Modern production C++ often uses `std::vector<int>` to manage this resource automatically. For this quiz, understand the explicit raw-pointer implementation shown in the supplied packet.

## 17. Packet corrections and careful interpretations

- **`delete nullptr` and `delete[] nullptr` are safe.** The heap packet incorrectly lists deleting a null pointer as an error. Checking for null before delete is optional.
- **Null is different from dangling.** A non-null check cannot prove that an allocation is alive. Resetting one pointer cannot reset its aliases.
- **References can dangle.** Their restricted syntax does not enforce object lifetimes.
- **The swap example should call `swap(x,y)`.** Non-const lvalue references cannot bind to `4` and `5`.
- **A final output comment in the references packet is wrong.** Starting with x=5 and y=6, the steps `rx += 1; rx = y; rx += 1;` end with x=7 and y=6, because rx aliases x. The printed `6 and 6` comment is inconsistent with that code.
- **Undefined behavior does not promise a crash or a particular output.** Treat the packet's observed allocator-reuse results as illustrations.
- **A destructor is not a universal deep cleanup.** An array of raw pointers still needs explicit pointee cleanup; resource-owning object elements can clean up their own resources through destructors.
- **Garbage-collection costs vary.** The packet's fixed memory multiplier and broad performance claims are not universal. Know the conceptual tradeoff: garbage collection can reclaim unreachable managed objects; this raw-pointer C++ design relies on explicit ownership and deterministic destructors.

## 18. How to solve a code question

1. Count each `new` as a distinct allocation and note scalar versus array.
2. Track every pointer's target and every reference's fixed target.
3. At assignment, check whether the destination loses the last address of a live allocation.
4. At deletion, check whether that allocation is still live, whether the pointer is its valid allocation address, and whether the delete form matches.
5. After deletion, mark all aliases as dangling until reset or redirected. Reject later reads, writes, and second deletions through them.
6. At scope exit, account for destructors. A raw pointer going out of scope does not free its pointee.

| Symptom | Diagnosis | Typical repair |
| --- | --- | --- |
| Last address overwritten or owner disappears without release | Leak | Release after final use, before losing ownership; or explicitly transfer ownership. |
| Two deletes target one allocation | Double free | One owner and one release; deep-copy when objects need independent ownership. |
| Read/write after release | Use after free | Keep the object alive until the last required use. |
| Return pointer/reference to a dead local | Dangling result | Return by value or refer to an object with an adequate lifetime. |
| Delete an automatic object or mismatch allocation form | Invalid deallocation | Respect storage duration and match `new`/`delete`, `new[]`/`delete[]`. |

Be ready to explain **why** a fix works: it preserves the needed lifetime, releases every owned allocation once, and leaves no later access through dangling aliases.

## Source files

- References versus Pointers: supplied `Pasted markdown (2).md`.
- Heap Allocated Memory Part I: supplied `Pasted markdown.md`.
- Style reference: supplied `Quiz_Questions_and_Answers.md`, containing transcribed Lambda Calculus, F#, and Options quizzes. Those subjects are style examples, not additional topics for this C++ practice quiz.
