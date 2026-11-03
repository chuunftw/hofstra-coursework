## Topic 1: Lambda calculus concepts

### Question 1

```text
Determine the output of the following program and explain why:

     let x = 1
     let f y = x+y
     let g() =
       let x = 2
       printfn "f(1) is %d"  (f 1)
```

### Question 2

```text
Show how to emulate dynamic scoping in a programming language that
   only allows static scoping
```

### Question 3

Write an F# program confirming that F# uses static scoping rather than dynamic scoping. Explain the different results the two rules would produce.

### Question 4

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

## Topic 2: F# functions and recursion

### Question 1

```text
Explain the difference between the following functions:

   a. let f(x,y) = x+y
   b. let g x y = x+y

   Give an example of the functions behaving differently
```

### Question 2

```text
Determine if the following function is tail-recursive and if not,
   write a tail-recursive version

     let rec fib n = if (n<3) then 1 else fib(n-1) + fib(n-2)
```

### Question 3

```text
Is the following function tail-recursive?

     let rec forall predicate m =
       match m with
         | [] -> true
	 | a::b -> (predicate a) && forall predicate b
```

### Question 4

```text
Write a function 'howmany' that takes a list and a predicate, and
   returns how many values x in the list are such that predicate(x) evaluates
   to true.  By list I mean built-in F# lists, with [] and a::b notation.
   The function must be tail-recursive
```

### Question 5

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

### Question 6

Write a tail-recursive F# function `howmany` that counts values in a built-in list satisfying a predicate.

```fsharp
howmany (fun x -> x % 2 = 0) [2;5;6;7;9] // returns 2
```

### Question 7

Given:
```fsharp
type List<'T> = Nil | Cons of 'T * List<'T>
```
Write a tail-recursive function that finds a list's length.

## Topic 3: Pattern matching and error handling

### Question 1

```text
Rewrite the following to use the Option monad instead of raising exceptions

     let safediv a b =
       if b<>0 then a/b else raise(Exception "div by zero")
```

### Question 2

```text
Write a function 'find_first' that takes a predicate and returns as
    an Option the first value in the list that satisfy the predicate, if
    it exists.  The function must be tail-recursive.
```

### Question 3

```text
Given
  open Option
  let a = Some 8
  let b = Some 4
  
  what is the value of
  b |> bind (fun y -> if y=0 then None else a |> map (fun x -> x/y))
```

### Question 4

```text
Given

 type expr =
   | Num of int
   | Plus of expr*expr
   | Times of expr*expr
   | Divide of expr*expr
   | RuntimeError

Write a function 'eval' that evaluates an expression to an expr.  A
Num or RuntimeError should be evaluated to itself (normal form).
Division by zero should evaluate to a runtime error.  For example,
eval (Plus(Num 2, Times(Num 2, Num 3))) should return (Num 8).  and
eval (Divide(Num 2, Num 0)) should return RuntimeError.
```

### Question 5

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

### Question 6

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

### Question 7

Given two int option values a and b, explain what, if anything, is wrong:
```fsharp
a |> Option.bind (fun x -> b |> Option.map (fun y -> x+y))
  |> Option.iter (printfn "sum is %d")
```

### Question 8

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

### Question 9

Write the divide function from Question 8 without pattern matching, using map/bind.

## Topic 4: Mutable closures, streams and comparison to OOP

### Question 1

```text
Determine the output of the following program:

     let make n =
       let mutable x = n
       fun y ->
         x <- x+y
	 x
	 
     let mutable a1 = make 0
     let mutable a2 = make 0
     a1 2
     a1 2
     a1 2
     a2 2
```

### Question 2

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

### Question 3

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

### Question 4

```text
Concerning streams in F# such as the following (infinite odd numbers):

    let mutable x = 1
    let oddstream = fun () ->
      x <- x+2
      Some(x-2)
      
    Show how to define a stream modifier `limit` that would limit the
    stream to a certain number, i.e oddstream |> limit 10, should limit
    the stream to the first 10 odds.
```

### Question 5

```text
Show how to define a stream modifier take_while that would return
     values that satisfy a predicate, and None otherwise.
```

### Question 6

```text
(harder) Show how to define a stream modifier `filter` that takes
     a predicate and modifies a stream to only return values that satisfy
     the predicate.
```

### Question 7

Given this F# stream:
```fsharp
let oddstream() =
    let mutable x = 1
    fun () -> x <- x + 2; Some(x - 2)
```
Write a stream modifier `limit` that limits a stream to the first n values, unless None occurs earlier. For example, `oddstream() |> limit 5` should represent 1,3,5,7,9.

A stream here is a function of type `unit -> 'a option`, not a built-in sequence. The modified stream should return None after it ends.

### Question 8

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

### Question 9

Write foreach, taking an action of type 'T -> unit and a stream of type unit -> 'T option. Call the action on each value until the stream ends.
```fsharp
odds() |> foreach (printf "%d ")
// prints 1 3 5 7 9 11 ... through 99
```

### Question 10

Identify a distinct advantage of each expression tree approach in Topic 3, Question 6: Java classes and F# discriminated unions. Be specific to extending this expression tree program.

## Topic 5: Limitations of C

### Question 1

```text
Explain why in (Gnu) C the K combinator cannot be defined as follows:

    typedef int (*intfun)(int);
    intfun K(int x) {
       int inner(int y) { return x; }
       return inner;
    }
```

### Question 2

Is it possible to write the makeswitch function from Topic 4, Question 2 in (GNU) C? Explain why or why not, considering the same independent, escaping closure behavior and restrictions.

### Question 3

Which of the functions in Topic 4, Question 3 can be written in GNU C? Explain.

## Topic 6: OOP essentials

### Question 1

```text
Explain why advanced object oriented programming requires dynamic
    memory allocation.  Why is stack allocation not enough?
```

### Question 2

```text
Explain what is meant by "dynamic dispatch" and "dynamic typing"
```

### Question 3

```text
What's the difference between "overloading" and "overriding"?
    Give an example of each.
```

### Question 4

```text
Given an example of a "pure virtual function" in the context of
    the shapes example in C++.
```

### Question 5

Explain why dynamic memory allocation is required for advanced object-oriented programming. Give an example. Be precise about runtime object creation and object lifetimes.

### Question 6

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

### Question 7

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

## Topic 7: Templates, generics and variance

### Question 1

```text
Explain what is meant by "covariance" and by "contravariance".  Under
   what circumstances is each principle valid?  Give an example of each.
```

### Question 2

```text
What's the difference between the following two lines in Java. Will
   either compile and run?

    i. Object[] A = new String[10];
   ii. ArrayList<Object> B = new ArrayList<String>();
```

### Question 3

```text
Explain if the following compiles in Java:

    interface I {
      Object f();
    }
    class A implements I {
      public String f() { return "abc"; }
    }
```

### Question 4

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

### Question 5

Explain why this should or should not compile, regardless of whether Java actually allows it:
```java
Object[] A = new String[4];
```

## Topic 8: How generics are implemented

### Question 1

```text
Concerning templates (generics), explain the differences between how
    they're implemented in C++ compared to Java.
```

### Question 2

```text
C++20 introduced "concepts", illustrated in

      template<typename T> requires std::totally_ordered<T>

    Explain whether the program will still compile if the "requires"
    clause is dropped.
```

### Question 3

```text
How about the following:

    class A<T> {
      T x;
      static T y;
    }
```

### Question 4

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

### Question 5

Explain whether this class compiles:
```java
class A<T> {
    static T x;
}
```

## Memory management (excluded from the exam)

### Question 1

```text
(maybe) Determine if the following C++ code contain any memory errors, and if so,
    what type of errors:

    int* px = new int(3);
    int* qx = new int(4);
    px = qx;
    delete px;
    delete qx;
```

### Question 2

```text
Explain what's meant by the "lifetime" of a value in memory.  When does
    lifetime end?
```

## Exam instruction

### Question 1

Write your name on the exam.
