# Mock Midterm Questions

CSC 123/252 — practice copy based on the photographed November 3, 2025 midterm.

Total: 100 points. Give clear technical explanations. Minor formatting is normalized; clarifications are explicitly identified.

[Open the solved version](04_MockMidterm_Solved.md)

## 1. Name (10 points)

Write your name on the exam.

---

## 2. Tail recursion (6 points)

Determine whether each function is tail-recursive and explain why.

**a. As printed in the photo:**
```fsharp
let rec reduce id op m =
    match m with
    | [] -> id
    | a::b -> reduce (op id a) b
```
Transcription note: the printed recursive call appears to omit the `op` argument. For the intended tail-recursion question, analyze the corrected call `reduce (op id a) op b`. Also identify the problem with the printed version.

**b.**
```fsharp
let rec f n = if n < 2 then 1 else n * f (n - 1)
```

---

## 3. Count matching values (8 points)

Write a tail-recursive F# function `howmany` that counts values in a built-in list satisfying a predicate.

```fsharp
howmany (fun x -> x % 2 = 0) [2;5;6;7;9] // returns 2
```

---

## 4. Static scoping (8 points)

Write an F# program confirming that F# uses static scoping rather than dynamic scoping. Explain the different results the two rules would produce.

---

## 5. Mutable closure (8 points)

Write `makeswitch`, which creates a closure that toggles between true and false. Use a mutable closure and no data structures. Separate switches must maintain independent state.

```fsharp
let s1 = makeswitch false
let s2 = makeswitch true
printfn "%A" (s1()) // true
printfn "%A" (s1()) // false
printfn "%A" (s1()) // true
printfn "%A" (s1()) // false
printfn "%A" (s2()) // false
printfn "%A" (s2()) // true
```

---

## 6. Closures in GNU C (5 points)

Is it possible to write the previous problem's makeswitch function in (GNU) C? Explain why or why not, considering the same independent, escaping closure behavior and restrictions.

---

## 7. Java compilation and runtime errors (9 points)

For each program, determine whether it compiles and, if it does, whether it produces a runtime error. Explain each answer in 1–2 sentences. Assume each public class has its own correctly named file.

**a.**
```java
public class lotsofobjects {
    public static void main(String[] args) {
        Object[] A = new String[10];
        A[0] = 3.5; // Doubles are also objects
        for (Object x : A) System.out.println(x);
    }
}
```

**b.**
```java
public class A<T> {
    public T[] M = new T[10];
}
```

**c.**
```java
import java.util.ArrayList;
public class waytoogeneric {
    public static void main(String[] args) {
        ArrayList<Object> L = new ArrayList<String>();
        L.add("abc");
    }
}
```

---

## 8. Dynamic memory and OOP (6 points)

Explain why dynamic memory allocation is required for advanced object-oriented programming. Give an example. Be precise about runtime object creation and object lifetimes.

---

## 9. Limit a stream (8 points)

Given this F# stream:
```fsharp
let oddstream() =
    let mutable x = 1
    fun () -> x <- x + 2; Some(x - 2)
```
Write a stream modifier `limit` that limits a stream to the first n values, unless None occurs earlier. For example, `oddstream() |> limit 5` should represent 1,3,5,7,9.

A stream here is a function of type `unit -> 'a option`, not a built-in sequence. The modified stream should return None after it ends.

---

## 10. Option.map and Option.bind (8 points)

Given:
```fsharp
let safediv (a:float) (b:float) =
    if b <> 0.0 then Some(a / b) else None
// float -> float -> float option
```
and two `float option` values a and b, explain what, if anything, is wrong with:
```fsharp
a |> Option.bind (fun x ->
    b |> Option.map (fun y -> safediv x y))
  |> Option.iter (fun z -> printfn "quotient is %.2f" z)
```
Give a corrected version.

---

## 11. Expression trees in F# (8 points)

Write an equivalent F# program for the following Java expression tree implementation. Use a discriminated union and an evaluation function.

```java
public interface expr {
    int eval();
}
class intnode implements expr {
    int val;
    public intnode(int v) { val = v; }
    public int eval() { return val; }
}
class plusnode implements expr {
    expr left; expr right;
    public plusnode(expr l, expr r) { left = l; right = r; }
    public int eval() { return left.eval() + right.eval(); }
}
class timesnode implements expr {
    expr left; expr right;
    public timesnode(expr l, expr r) { left = l; right = r; }
    public int eval() { return left.eval() * right.eval(); }
}
```

---

## 12. Expression tree design tradeoffs (4 points)

Identify a distinct advantage of each expression tree approach in Question 11: Java classes and F# discriminated unions. Be specific to extending this expression tree program.

---

## 13. Java overloading (6 points)

Will this compile? Will it run? Describe what happens and explain why.
```java
interface city {}
class NY implements city {}
class LA implements city {}
public class tourist {
    static void visit(NY ny) {
        System.out.println("go to a yankees game");
    }
    static void visit(LA ca) {
        System.out.println("go to a dodgers game");
    }
    public static void main(String[] args) {
        city[] Cities = { new NY(), new LA() };
        for (city c : Cities) visit(c);
    }
}
```

---

## 14. C++ templates (6 points)

Will this C++ template class compile? Explain why or why not. Distinguish defining a template from instantiating and using its members.
```cpp
#include <iostream>
template<typename T>
class A {
private:
    T x;
public:
    A(T y) { x = y; }
    void f() { x = 3; }
};
```
