# Scary Test — Solved Version

CSC 123/252 — transcribed from the supplied seven-page Scary Test. Original numbering is preserved, including 1b, 8a/8b, and 9b. Formatting is normalized. Suggested time: about 40 minutes.

[Open questions only](05_ScaryTest_Questions.md)

## 1. Functions and mutable state

Explain the difference between f and g and determine the output.
```fsharp
let f x0 =
    fun y ->
        let mutable x = x0
        x <- x+y
        x

let g x0 =
    let mutable x = x0
    fun y ->
        x <- x+y
        x

let f1 = f(2)
let g1 = g(2)
printfn "%d" (f1(1)+f1(1))
printfn "%d" (g1(1)+g1(1))
```

### Solution

Output:
```text
6
7
```
f creates a fresh mutable x inside every call to its returned function. Each f1(1) starts at 2 and returns 3, giving 3 + 3 = 6.

g creates x once when g(2) runs. Its returned closure retains that state: the first g1(1) returns 3 and the next returns 4, giving 7.

---

## 1b. GNU C

Which of the functions above can be written in GNU C? Explain.

### Solution

**Both general factories return closures; only g preserves changing state between calls.** Neither general factory can safely be implemented by returning a GNU C nested function that captures automatic locals after its enclosing call has returned. f still needs its captured x0, even though its mutable x is reset on every invocation.

f's arithmetic behavior can be reproduced by a C function taking x0 and y explicitly. For the specific f1 example, a function that returns 2 + y suffices. These alternatives change or specialize the interface: ordinary C function pointers do not carry arbitrary captured x0, so reproducing the general factory requires an explicit environment or another mechanism.

g must retain a separate, changing x for each returned function after its factory returns. GNU C nested functions do not preserve the enclosing automatic variables after the enclosing call ends. A static variable would share state rather than support arbitrary independent closures. An explicit allocated environment plus function pointer can simulate this with a changed representation/interface.

For the usual course comparison, emphasize f's fresh local versus g's persistent captured mutable state; do not claim GNU C provides general safe escaping closures.

---

## 2. Static and dynamic scoping

A language called C** has familiar syntax:
```cpp
int x = 1;
int f(int y) { return y+1; }
void MAIN() {
    int x = 2;
    stdout << f(x) << endl; // prints 3
}
```
Devise one C** program whose behavior differs under static and dynamic scoping. Explain how to interpret its output.

### Solution

Use a free variable inside f:
```cpp
int x = 1;
int f(int y) { return x+y; }
void MAIN() {
    int x = 2;
    stdout << f(0) << endl;
}
```
**Prints 1 under static scoping:** f uses the global x visible where f was defined.

**Prints 2 under dynamic scoping:** f finds the local x in the active MAIN caller.

The original program cannot distinguish the rules because f uses only its parameter and a constant.

---

## 3. Java generic static field

Explain whether this class compiles:
```java
class A<T> {
    static T x;
}
```

### Solution

**Does not compile.** The class type parameter T cannot be referenced from this static context. A static field belongs to the class, shared across its parameterizations, rather than to an A<String> or A<Integer> instance. An instance field `T x;` is allowed.

---

## 4. Java array covariance

Explain why this should or should not compile, regardless of whether Java actually allows it:
```java
Object[] A = new String[4];
```

### Solution

**Java allows it** because reference arrays are covariant: String is a subtype of Object, and String[] is a subtype of Object[].

**Type-safety objection:** a writable Object[] view permits code such as `A[0] = 3.5;`, but the actual String[] cannot store a Double. A design requiring full static safety could reject this assignment or expose only a read-only covariant view. Java instead checks array stores at runtime and throws ArrayStoreException for an incompatible value.

The declaration alone is valid and does not throw.

---

## 5. Java overload resolution

Determine the output and explain:
```java
class A {}
class B extends A {}

public class goodquestion {
    public int f(A x) { return 1; }
    public int f(B x) { return 2; }

    public static void main(String[] args) {
        A n = new B();
        goodquestion gq = new goodquestion();
        System.out.println(gq.f(n));
    }
}
```

### Solution

**Prints 1.** Overload resolution uses n's declared compile-time type A, selecting f(A). Its runtime class B does not change the selected overload. This is overloading, not overriding a method on the argument object.

---

## 6. Tail-recursive custom-list length

Given:
```fsharp
type List<'T> = Nil | Cons of 'T * List<'T>
```
Write a tail-recursive function that finds a list's length.

### Solution

```fsharp
type List<'T> = Nil | Cons of 'T * List<'T>

let length values =
    let rec loop count remaining =
        match remaining with
        | Nil -> count
        | Cons (_, tail) -> loop (count + 1) tail
    loop 0 values
```
The accumulator holds the number of nodes already visited. No work remains after the recursive call.

```fsharp
length Nil                         // 0
length (Cons (4, Cons (7, Nil)))    // 2
```

---

## 7. Options and addition

Given two int option values a and b, explain what, if anything, is wrong:
```fsharp
a |> Option.bind (fun x -> b |> Option.map (fun y -> x+y))
  |> Option.iter (printfn "sum is %d")
```

### Solution

**Nothing is wrong.** x+y returns an int, so the inner map wraps the sum once as int option. The callback supplied to the outer bind therefore returns the option type bind expects, and bind adds no extra layer.

If both inputs are Some, it prints their sum. If either is None, it prints nothing.
```text
a = Some 2, b = Some 5  -> sum is 7
a = None,   b = Some 5  -> no output
```
Do not change the inner map to bind unless its callback also changes to return an option.

---

## 8a. Stream take_while

A possibly infinite stream has type unit -> 'T option and ends when it returns None:
```fsharp
let odds() =
    let mutable n = 1
    fun () ->
        if n > 99 then None
        else
            n <- n+2
            Some(n-2)
```
Write take_while, taking a predicate and a stream, without Option.get. It must work for any stream and predicate:
```fsharp
odds() |> take_while (fun x -> x < 10)
// represents 1 3 5 7 9
```

### Solution

```fsharp
let take_while predicate (stream: unit -> 'T option) =
    let mutable ended = false
    fun () ->
        if ended then None
        else
            match stream () with
            | Some value when predicate value -> Some value
            | _ ->
                ended <- true
                None
```
It returns the initial consecutive values satisfying the predicate. The first failed predicate or source None ends the modified stream permanently. This is take-while, not filtering: it does not skip failures and search for later matches.

The first failing value is consumed from the source. Once ended, repeated calls return None without pulling more values.

```fsharp
let s = odds() |> take_while (fun x -> x < 10)
// Successive s() calls: Some 1, Some 3, Some 5, Some 7, Some 9, None
```

---

## 8b. Stream foreach

Write foreach, taking an action of type 'T -> unit and a stream of type unit -> 'T option. Call the action on each value until the stream ends.
```fsharp
odds() |> foreach (printf "%d ")
// prints 1 3 5 7 9 11 ... through 99
```

### Solution

```fsharp
let foreach (action: 'T -> unit) (stream: unit -> 'T option) =
    let rec loop () =
        match stream () with
        | None -> ()
        | Some value ->
            action value
            loop ()
    loop ()
```
Each iteration pulls one value, performs the action, and repeats. None ends the traversal. The recursive call is in tail position.

The supplied odds() is finite: without a wrapper, it produces 50 values, from 1 through 99. A truly infinite source with no terminating wrapper keeps running. Here take_while stops the traversal at 9:
```fsharp
odds()
|> take_while (fun x -> x < 10)
|> foreach (printf "%d ")
// 1 3 5 7 9
```

---

## 9. Division with Number and options

Given:
```fsharp
type Number = Integer of int | Rational of int * int

let times a b =
    match (a,b) with
    | (Integer x, Integer y) -> Integer (x*y)
    | (Integer x, Rational(n,d)) -> Rational(x*n,d)
    | (Rational(a,b), Rational(c,d)) -> Rational(a*c,b*d)
    | (Rational(n,d), Integer x) -> Rational(x*n,d)

let inverse a =
    match a with
    | Integer x when x <> 0 -> Some(Rational(1,x))
    | Rational(n,d) when n <> 0 -> Some(Rational(d,n))
    | _ -> None
```
Write divide, multiplying the first Number by the inverse of the second when it exists. Return an option. Do not use Option.get.

### Solution

```fsharp
let divide a b =
    match inverse b with
    | None -> None
    | Some reciprocal -> Some (times a reciprocal)
```
Invert the denominator b, not the numerator a. If inversion fails, propagate None; otherwise multiply a by the reciprocal and return Some.

```fsharp
divide (Integer 6) (Integer 2) // Some (Rational (6,2))
divide (Integer 6) (Integer 0) // None
divide (Integer 0) (Integer 2) // Some (Rational (0,2))
```
The provided operations do not reduce fractions, so Rational(6,2) need not become Integer 3. This follows the supplied inverse exactly and assumes valid rational inputs (nonzero denominators); the provided definition does not itself validate all malformed Rational values.

---

## 9b. Division without pattern matching

Write the divide function from Question 9 without pattern matching, using map/bind.

### Solution

```fsharp
let divide a b =
    inverse b |> Option.map (fun reciprocal -> times a reciprocal)
```
Or, using partial application:
```fsharp
let divide a b =
    inverse b |> Option.map (times a)
```
Use map because times returns a plain Number. map produces the required Number option and preserves None automatically.

A valid but longer bind version explicitly wraps the result:
```fsharp
let divide a b =
    inverse b |> Option.bind (fun reciprocal ->
        Some (times a reciprocal))
```
