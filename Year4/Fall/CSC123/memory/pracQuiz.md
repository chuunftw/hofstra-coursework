# C++ References and Heap Memory: Practice Quiz

10 original questions based on both packets and the supplied professor quiz examples. This is practice, not a prediction of the actual quiz. The format follows the examples: trace code, explain differences, diagnose errors, and write fixes.

Assume `#include <iostream>` and `using namespace std;`. Allocations succeed. For code with undefined behavior, identify the error instead of inventing a guaranteed output. Each question is worth 10 points, including its subparts.

## 1. References versus pointers

Determine the output and explain what `r` refers to after `p = &y`.

```cpp
int x = 3, y = 8;
int* p = &x;
int& r = *p;
p = &y;
r += 2;
*p += r;
cout << x << " " << y << " " << r << endl;
```

## 2. Assignment through a reference

Explain the difference between fragments (a) and (b). Give the final values of `x` and `y` in each.

```cpp
// (a)
int x = 2, y = 9;
int& r = x;
r = y;
r++;
```

```cpp
// (b)
int x = 2, y = 9;
int* p = &x;
p = &y;
(*p)++;
```

## 3. Which declarations compile?

Consider each declaration independently, after `int x = 5;`. State whether it compiles and explain why.

```cpp
// (a)
int& a = 7;
// (b)
const int& b = 7;
// (c)
int&& c = 7;
// (d)
int&& d = x;
// (e)
int* p = &x;
int** pp = &p;
```

## 4. Returned values and lifetimes

Compare the functions. Is each returned result safe to use after the function returns? Explain why. For any safe heap result, show how the caller releases it correctly.

```cpp
int* first() {
    int x = 12;
    return &x;
}

int* second() {
    return new int(12);
}

int& third() {
    int x = 12;
    return x;
}
```

## 5. Double free

Identify the erroneous statement, explain the cause, and rewrite the fragment to preserve the assignment to `B[0]` while fixing all memory errors.

```cpp
int* A = new int[4];
int* B = A;
B[0] = 6;
delete[] A;
delete[] B;
```

Would adding `A = nullptr;` immediately after `delete[] A;` make the original `delete[] B;` safe? Explain.

## 6. Memory leak caused by reassignment

Identify exactly when a leak occurs, which allocation leaks, and how many distinct allocations exist. Rewrite the fragment to avoid both leaks and double free while keeping `A = B;`.

```cpp
int* A = new int[3];
int* B = new int[7];
A = B;
delete[] A;
```

## 7. Use after free

Does this program have a guaranteed output? Explain the memory error and give a corrected version that prints `40` and releases the allocation.

```cpp
int* A = new int[2];
A[1] = 40;
int* B = A;
delete[] A;
cout << B[1] << endl;
```

## 8. An array of pointers

Why is the final line insufficient? Write the complete cleanup code and state the total number of heap allocations.

```cpp
int** A = new int*[3];
for (int i = 0; i < 3; i++)
    A[i] = new int(i + 1);

delete[] A;
```

## 9. A destructor is not enough

Assume this struct has no custom copy constructor or copy assignment operator.

```cpp
struct Buffer {
    int* cells;
    Buffer(int n) { cells = new int[n]; }
    ~Buffer() { delete[] cells; }
};

void test() {
    Buffer A(3);
    Buffer B(5);
    B = A;
}
```

(a) Explain both memory errors caused by `B = A;` and the later destruction.

(b) How would the situation differ if the body were `Buffer A(3); Buffer B = A;`?

(c) Name the three operations in the Rule of Three and explain how deep copying fixes ownership.

## 10. Implement safe copying

Complete the following struct using a deep-copy constructor and copy assignment operator. Preserve the source's values, handle `B = B`, and avoid leaks and double free during normal operation. Prefer allocating replacement storage before deleting existing storage.

```cpp
struct Buffer {
    int size;
    int* cells;

    Buffer(int n) : size(n), cells(new int[n]{}) {}
    ~Buffer() { delete[] cells; }

    Buffer(const Buffer& other) {
        // complete
    }

    Buffer& operator=(const Buffer& other) {
        // complete
    }
};
```

Then explain why `Buffer B = A;` uses a different operation from `B = A;` when `B` already exists.
