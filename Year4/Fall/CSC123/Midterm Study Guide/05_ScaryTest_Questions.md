# Scary Test Questions

CSC 123/252 — transcribed from the supplied seven-page Scary Test. Original numbering is preserved, including 1b, 8a/8b, and 9b. Formatting is normalized. Suggested time: about 40 minutes.

[Open solved version](06_ScaryTest_Solved.md)

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

---

## 1b. GNU C

Which of the functions above can be written in GNU C? Explain.

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

---

## 3. Java generic static field

Explain whether this class compiles:
```java
class A<T> {
    static T x;
}
```

---

## 4. Java array covariance

Explain why this should or should not compile, regardless of whether Java actually allows it:
```java
Object[] A = new String[4];
```

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

---

## 6. Tail-recursive custom-list length

Given:
```fsharp
type List<'T> = Nil | Cons of 'T * List<'T>
```
Write a tail-recursive function that finds a list's length.

---

## 7. Options and addition

Given two int option values a and b, explain what, if anything, is wrong:
```fsharp
a |> Option.bind (fun x -> b |> Option.map (fun y -> x+y))
  |> Option.iter (printfn "sum is %d")
```

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

---

## 8b. Stream foreach

Write foreach, taking an action of type 'T -> unit and a stream of type unit -> 'T option. Call the action on each value until the stream ends.
```fsharp
odds() |> foreach (printf "%d ")
// prints 1 3 5 7 9 11 ... through 99
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

---

## 9b. Division without pattern matching

Write the divide function from Question 9 without pattern matching, using map/bind.
