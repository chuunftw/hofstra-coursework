# Mock Midterm — Solved Version

Solutions to the photographed CSC 123/252 November 3, 2025 midterm, with matching question numbers and explanations. The printed typo in 2(a) and technical qualifications in 6, 8, and 14 are called out explicitly.

[Open questions only](03_MockMidterm_Questions.md)

## 1. Name (10 points)

Write your name on the exam.

### Solution

Write your own name.

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

### Solution

**Intended corrected (a): tail-recursive.** The recursive call `reduce (op id a) op b` is the final operation. The accumulator update `op id a` happens before the call; no work remains after it returns.

**Printed-code issue:** `reduce` takes three curried arguments, but the printed recursive call supplies only two and passes the list tail where the operator belongs. The displayed definition does not type-check as the intended reducer.

**(b): not tail-recursive.** After `f (n - 1)` returns, the function still multiplies its result by n. For example, `f 3` waits for `f 2` before doing `3 * ...`.

---

## 3. Count matching values (8 points)

Write a tail-recursive F# function `howmany` that counts values in a built-in list satisfying a predicate.

```fsharp
howmany (fun x -> x % 2 = 0) [2;5;6;7;9] // returns 2
```

### Solution

```fsharp
let howmany predicate values =
    let rec loop count remaining =
        match remaining with
        | [] -> count
        | head::tail ->
            let next = if predicate head then count + 1 else count
            loop next tail
    loop 0 values
```

The accumulator holds the count so far. Every recursive result is returned directly.

```fsharp
howmany (fun x -> x % 2 = 0) [2;5;6;7;9] // 2
howmany (fun _ -> true) []                // 0
```

---

## 4. Static scoping (8 points)

Write an F# program confirming that F# uses static scoping rather than dynamic scoping. Explain the different results the two rules would produce.

### Solution

```fsharp
let x = 10
let f () = x

let g () =
    let x = 20
    f ()

printfn "%d" (g ()) // 10
```

Static (lexical) scoping resolves the x used by f where f is defined, so it prints 10. Under dynamic scoping, the active caller's local x would be used and the result would be 20. Shadowing x in g does not change f's captured binding.

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

### Solution

```fsharp
let makeswitch initial =
    let mutable state = initial
    fun () ->
        state <- not state
        state
```

Each call to makeswitch allocates a separate captured state. Calling the returned function flips that state before returning it. Thus s1 produces true, false, true, false, while s2 separately produces false, true.

---

## 6. Closures in GNU C (5 points)

Is it possible to write the previous problem's makeswitch function in (GNU) C? Explain why or why not, considering the same independent, escaping closure behavior and restrictions.

### Solution

**Not with the same general escaping-closure behavior under the stated restrictions.** Ordinary C function pointers carry no captured environment. GNU C nested functions can access enclosing locals while their enclosing activation is alive, but returning a nested function does not preserve that activation after makeswitch returns.

A static variable survives but does not create fresh independent state for every switch. C can simulate closures with an explicit allocated environment plus a function pointer (and a calling convention that passes that environment), but that changes the representation/interface and violates the no-data-structures restriction.

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

### Solution

**a. Compiles; throws ArrayStoreException at `A[0] = 3.5`.** Java arrays are covariant, so a String[] can be referenced as Object[]. However, the actual array is still a String[], and the boxed Double value is rejected by the runtime store check; the loop is never reached.

**b. Does not compile: generic array creation.** T is a non-reifiable type parameter: erasure means the concrete T is not available to create an array with the required runtime component type. Declaring T[] is allowed; `new T[10]` is not.

**c. Does not compile.** ArrayList<String> is not a subtype of ArrayList<Object>; generic classes are invariant. Otherwise an Object view could insert non-String objects into a list intended to contain only Strings.

---

## 8. Dynamic memory and OOP (6 points)

Explain why dynamic memory allocation is required for advanced object-oriented programming. Give an example. Be precise about runtime object creation and object lifetimes.

### Solution

Dynamic allocation supports creating objects whose number, concrete type, and lifetime depend on runtime behavior, including objects that outlive the function creating them. For example, a factory can choose between Circle and Rectangle from user input and return the new object through a Shape reference; the object remains usable after the factory returns.

**Precision:** OOP itself does not universally require heap allocation—C++ supports stack-allocated objects and virtual dispatch. The need here is flexible runtime creation and lifetimes independent of the creating stack frame, rather than inheritance or dispatch alone.

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

### Solution

```fsharp
let limit n (stream: unit -> 'a option) =
    let mutable remaining = max 0 n
    let mutable ended = false
    fun () ->
        if ended || remaining = 0 then
            None
        else
            match stream () with
            | None ->
                ended <- true
                None
            | Some value ->
                remaining <- remaining - 1
                Some value
```

The wrapper pulls one source value per call until n values have been produced or the source returns None. After that, it returns None without calling the source again.

```fsharp
let s = oddstream() |> limit 5
// Successive s() calls:
// Some 1; Some 3; Some 5; Some 7; Some 9; None; None
```

For n <= 0, no source values are consumed. The ended flag also makes an early None permanent.

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

### Solution

**The final formatting expression does not type-check.** safediv already returns float option. Mapping it over b adds another option layer, producing float option option. The outer bind removes only the layer associated with a, so its overall result is still float option option. Consequently, z in Option.iter is float option, while %.2f requires float.

Use bind for the inner operation:
```fsharp
a |> Option.bind (fun x ->
    b |> Option.bind (fun y -> safediv x y))
  |> Option.iter (fun z -> printfn "quotient is %.2f" z)
```

Both binds chain option-returning computations without introducing an extra layer. If a or b is None, or b contains zero, nothing is printed. For a = Some 6.0 and b = Some 2.0, it prints `quotient is 3.00`.

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

### Solution

```fsharp
type Expr =
    | IntNode of int
    | PlusNode of Expr * Expr
    | TimesNode of Expr * Expr

let rec eval expression =
    match expression with
    | IntNode value -> value
    | PlusNode (left, right) -> eval left + eval right
    | TimesNode (left, right) -> eval left * eval right

let example =
    TimesNode (PlusNode (IntNode 2, IntNode 3), IntNode 4)

printfn "%d" (eval example) // 20
```

IntNode represents a leaf. PlusNode and TimesNode each contain two subexpressions. Pattern matching selects the corresponding evaluation rule.

---

## 12. Expression tree design tradeoffs (4 points)

Identify a distinct advantage of each expression tree approach in Question 11: Java classes and F# discriminated unions. Be specific to extending this expression tree program.

### Solution

**Java advantage — adding an expression variant:** add a minusnode class implementing expr and its eval method without editing the existing intnode, plusnode, or timesnode classes.

**F# advantage — adding an operation:** add a separate function, such as prettyPrint or countNodes, that pattern-matches on Expr without editing each existing variant. Exhaustiveness checking helps identify missing cases.

With the shown designs, adding a variant in F# requires updating functions that handle all cases; adding an interface operation in Java generally requires updating each implementing class.

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

### Solution

**Does not compile, so there is no program output.** Overload resolution uses the compile-time type of c, which is city. Neither visit(NY) nor visit(LA) accepts an arbitrary city, and there is no visit(city) overload.

The runtime class of c does not select among these overloads. A redesign could put a visit method on city and override it in NY and LA, enabling runtime method dispatch.

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

### Solution

**The template definition is valid.** The assignment `x = 3` depends on T, so its validity is checked when the relevant member is instantiated.

```cpp
A<int> a(1);
a.f();              // OK: int can be assigned 3

struct Item {};
A<Item> b(Item{});   // OK: Item can be default constructed and copy assigned
// b.f();           // Error if used: Item cannot be assigned an int
```

Instantiating A<Item> alone does not ordinarily instantiate the body of its unused f member. The constructor also imposes requirements because x is default initialized and then assigned y.

The snippet is a class definition, not a complete executable: it needs a main function to link as a standalone program. That is separate from whether the template definition is valid.
