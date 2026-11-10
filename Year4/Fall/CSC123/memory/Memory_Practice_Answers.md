# Practice Quiz: Answer Key

## 1

Output: `5 13 5`.

`r` binds to `x` when initialized. Changing `p` to point to `y` does not change that binding. `r += 2` makes `x` equal 5; `*p += r` makes `y` equal 8 + 5 = 13.

## 2

(a) `x = 10`, `y = 9`. `r = y` copies 9 into `x`; it does not rebind the reference. Incrementing `r` increments `x`.

(b) `x = 2`, `y = 10`. `p = &y` changes the pointer's address. Incrementing `*p` now increments `y`.

## 3

| Declaration | Compiles? | Reason |
| --- | --- | --- |
| (a) `int& a = 7` | No | A non-const lvalue reference cannot bind to this temporary. |
| (b) `const int& b = 7` | Yes | A const lvalue reference can bind to the temporary; here its lifetime is extended to the reference's scope. |
| (c) `int&& c = 7` | Yes | An rvalue reference can bind to this temporary. |
| (d) `int&& d = x` | No | The expression `x` is an lvalue. |
| (e) pointer and pointer-to-pointer | Yes | `p` stores `&x`; `pp` stores the address of the pointer variable `p`. |

## 4

`first`: unsafe. Local `x` dies when the function returns, leaving a dangling pointer. Do not fix this by calling `delete`: the object was never allocated with `new`.

`second`: safe to dereference while the allocation remains alive. The caller owns cleanup:

```cpp
int* p = second();
cout << *p << endl;
delete p;
p = nullptr;
```

`third`: unsafe. The returned reference refers to a local object whose lifetime has ended. Return an `int` by value if the goal is simply to return 12.

## 5

`delete[] B;` attempts to release the same allocation a second time. There are two pointers but only one allocation.

```cpp
int* A = new int[4];
int* B = A;
B[0] = 6;
delete[] A;
A = nullptr;
B = nullptr;
```

Setting only `A` to `nullptr` does not change `B`. The original `delete[] B;` would still be invalid. The fix is one deallocation for the allocation, followed by no further use through any dangling alias.

## 6

There are two allocations. The three-int allocation leaks at `A = B;`, when its last pointer is overwritten. The seven-int allocation is released by `delete[] A;` because `A` now contains the same address as `B`.

```cpp
int* A = new int[3];
int* B = new int[7];
delete[] A;  // release old allocation before losing its address
A = B;
delete[] A;  // release shared allocation once
A = nullptr;
B = nullptr;
```

Do not add a second `delete[] B;` after freeing through `A`.

## 7

The read `B[1]` occurs after the allocation is freed: use after free, which is undefined behavior. There is no guaranteed output. It might appear to print 40, print something else, or fail.

```cpp
int* A = new int[2];
A[1] = 40;
int* B = A;
cout << B[1] << endl;
delete[] A;
A = nullptr;
B = nullptr;
```

## 8

There are four allocations: one array of three pointer objects and three individual integers. Deleting the array of raw pointers does not delete their pointees. Replace the original cleanup with:

```cpp
for (int i = 0; i < 3; i++)
    delete A[i];
delete[] A;
A = nullptr;
```

The inner allocations use scalar `new`, so they need scalar `delete`. Cleanup must happen before the pointer array is released.

## 9

(a) Default copy assignment copies the pointer value. B's original five-int allocation loses its last pointer and leaks. A and B now hold the same address. When they leave scope, B's destructor runs first and frees the shared allocation; A's destructor then tries to free it again.

(b) `Buffer B = A;` initializes B using the copy constructor. Its default behavior still copies the pointer, so destruction still double-frees. There is no separate original allocation for B to leak in this version.

(c) Destructor, copy constructor, and copy assignment operator. A deep copy allocates independent storage and copies the elements. Each object can then release its own allocation exactly once.

## 10

```cpp
Buffer(const Buffer& other)
    : size(other.size), cells(new int[other.size]) {
    for (int i = 0; i < size; i++)
        cells[i] = other.cells[i];
}

Buffer& operator=(const Buffer& other) {
    if (this == &other)
        return *this;

    int* replacement = new int[other.size];
    for (int i = 0; i < other.size; i++)
        replacement[i] = other.cells[i];

    delete[] cells;
    cells = replacement;
    size = other.size;
    return *this;
}
```

The constructor initializes a new object, so there is no previously owned array to release. Assignment updates an existing object, whose previous allocation must be released. The self-assignment check prevents destroying the source when source and destination are the same object. Allocating first also leaves the old object intact if allocation fails; copying `int` elements does not throw.

After a successful deep copy, editing `B.cells[0]` does not change `A.cells[0]`. Both destructors can safely run.
