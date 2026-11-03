# CSC123 Midterm - Questions Organized by Topic

Created November 2, 2026. This is the question bank for Ryan's topic-by-topic study method.

Study each topic from the professor's materials, then attempt every related question here one at a time. Check solutions after an attempt and revisit mistakes. Day 1 covers Topics 1-2; Day 2 covers Topics 3-8, followed by mixed review. These blocks differ in size, so two of eight blocks does not guarantee exactly one quarter of the study time.

## Sources and preservation

The three sources are the sets identified in our study plan:

- **Professor practice set:** M01 in [CSC123_Midterm_Handoff.md](CSC123_Midterm_Handoff.md), including original lettered questions: 27 entries.
- **Mock Midterm:** [03_MockMidterm_Questions.md](03_MockMidterm_Questions.md), based on the photographed November 3, 2025 midterm: 14 entries including the name instruction. Original total: 100 points; point labels are retained.
- **Scary Test:** [05_ScaryTest_Questions.md](05_ScaryTest_Questions.md), transcribed from the supplied seven-page test: 12 entries. Its suggested duration is about 40 minutes; this does not establish the upcoming exam's time limit.

**Total: 53 source entries**, with every internal subpart retained. The separate assistant-created P01-P21 bank in `01_MidtermStudyGuide.fs` is not one of these three sources and is not included here. “Professor Q” below means original professor numbering, not the assistant bank's P-numbering.

Full question text, code, examples and existing transcription notes are preserved. Editorial titles, topic descriptions and cross-references are added around them. Professor questions use text blocks to preserve original indentation and wording. A question spanning topics appears in full once and is cross-referenced elsewhere. No worked solutions are added; expected outputs or clarifications already supplied within questions remain intact.

**Scope:** no beta-reduction drills; the standalone memory-management unit is excluded per Ryan's update. Its questions remain in an excluded reference section. Mixed OOP/allocation questions are flagged in Topic 6. Use the handoff's technical corrections when checking answers: preserved source questions and programs may contain mistakes or intentionally faulty code.

## Topic and question index

| Study block | Day | Professor questions | Mock questions | Scary questions |
|---|---|---|---|---|
| [1. Lambda concepts](#topic-1) | 1 | 7, 7b | 4; also 7 for type checking | 2 |
| [2. F# functions and recursion](#topic-2) | 1 | 3, 4, 5, 6b; also 6c in Topic 3 | 2, 3 | 6 |
| [3. Patterns and errors](#topic-3) | 2 | 6, 6c, 6d, 8 | 10, 11 | 7, 9, 9b |
| [4. Closures, streams and OOP comparison](#topic-4) | 2 | 9, 18, 18b, 18c | 5, 9, 12 | 1, 8a, 8b |
| [5. C limitations](#topic-5) | 2 | 19 | 6 | 1b |
| [6. OOP essentials](#topic-6) | 2 | 12, 12b, 13, 14 | 8, 13 | 5 |
| [7. Templates, generics and variance](#topic-7) | 2 | 1, 2, 15 | 7, especially (a)/(c) | 4 |
| [8. Generic implementation](#topic-8) | 2 | 10, 11, 15b | 14; also 7(b) in Topic 7 | 3 |
| [Excluded: memory management](#excluded-memory) | Skip | 16, 17 | - | - |
| [Administrative item](#administrative) | - | - | 1 | - |

## Coverage gaps

The professor's topic list determines what to study. Absence from these sets does not remove a topic. Review lambda theory and C#/F# generic implementation from the handoff even though these sets offer little direct practice. Any new tutor-created checks should be labeled separately instead of attributed to a professor test.


---

<a id="topic-1"></a>
## 1. Lambda calculus concepts

**Schedule:** Day 1

**Topics:** Basic notation; abstraction/application; free and bound variables; normal form; Church-Rosser; call-by-value/name; static/dynamic scoping; type soundness; static/dynamic type checking.

These questions directly practice scoping. The three sets have no dedicated questions on Church-Rosser, evaluation strategies or the type-soundness theorem. Those remain required topics. Basic notation and normal form support understanding; beta-reduction drills are excluded. For applied compile-time/runtime type checks, also see [Mock Q7](#question-m7).


<a id="question-p7"></a>
### Professor Q7 - Static scoping

Source: Professor practice set, original question 7.

```text
7. Determine the output of the following program and explain why:

     let x = 1
     let f y = x+y
     let g() =
       let x = 2
       printfn "f(1) is %d"  (f 1)
```


<a id="question-p7b"></a>
### Professor Q7b - Emulating dynamic scoping

Source: Professor practice set, original question 7b.

```text
7b. Show how to emulate dynamic scoping in a programming language that
   only allows static scoping
```


<a id="question-m4"></a>
### Mock Q4 - Static scoping (8 points)

Source: Mock Midterm, original question 4.

Write an F# program confirming that F# uses static scoping rather than dynamic scoping. Explain the different results the two rules would produce.


<a id="question-s2"></a>
### Scary Q2 - Static and dynamic scoping

Source: Scary Test, original question 2.

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

<a id="topic-2"></a>
## 2. F# functions and recursion

**Schedule:** Day 1

**Topics:** Function types; curried/uncurried functions; partial application; list basics; tail position; tail recursion and accumulators.

The combined tail-recursion/option question [Professor Q6c](#question-p6c) is in Topic 3, after options are introduced. Return to it to check tail recursion too.


<a id="question-p3"></a>
### Professor Q3 - Curried and uncurried functions

Source: Professor practice set, original question 3.

```text
3. Explain the difference between the following functions:

   a. let f(x,y) = x+y
   b. let g x y = x+y

   Give an example of the functions behaving differently
```


<a id="question-p4"></a>
### Professor Q4 - Tail-recursive Fibonacci

Source: Professor practice set, original question 4.

```text
4. Determine if the following function is tail-recursive and if not,
   write a tail-recursive version

     let rec fib n = if (n<3) then 1 else fib(n-1) + fib(n-2)
```


<a id="question-p5"></a>
### Professor Q5 - Tail position and short-circuit evaluation

Source: Professor practice set, original question 5.

```text
5. Is the following function tail-recursive?

     let rec forall predicate m =
       match m with
         | [] -> true
	 | a::b -> (predicate a) && forall predicate b
```


<a id="question-p6b"></a>
### Professor Q6b - Tail-recursive counting

Source: Professor practice set, original question 6b.

```text
6b.

   Write a function 'howmany' that takes a list and a predicate, and
   returns how many values x in the list are such that predicate(x) evaluates
   to true.  By list I mean built-in F# lists, with [] and a::b notation.
   The function must be tail-recursive
```


<a id="question-m2"></a>
### Mock Q2 - Tail recursion (6 points)

Source: Mock Midterm, original question 2.

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


<a id="question-m3"></a>
### Mock Q3 - Count matching values (8 points)

Source: Mock Midterm, original question 3.

Write a tail-recursive F# function `howmany` that counts values in a built-in list satisfying a predicate.

```fsharp
howmany (fun x -> x % 2 = 0) [2;5;6;7;9] // returns 2
```


<a id="question-s6"></a>
### Scary Q6 - Tail-recursive custom-list length

Source: Scary Test, original question 6.

Given:
```fsharp
type List<'T> = Nil | Cons of 'T * List<'T>
```
Write a tail-recursive function that finds a list's length.


---

<a id="topic-3"></a>
## 3. Pattern matching and error handling

**Schedule:** Day 2

**Topics:** List and discriminated-union patterns; guards; Some/None; Option.map/bind; safe operations; expression-tree evaluation and error propagation.

Also revisit list-pattern questions in [Topic 2](#topic-2). [Mock Q12](#question-m12), in Topic 4, compares the expression-tree approaches used in Mock Q11.


<a id="question-p6"></a>
### Professor Q6 - Safe division with options

Source: Professor practice set, original question 6.

```text
6. Rewrite the following to use the Option monad instead of raising exceptions

     let safediv a b =
       if b<>0 then a/b else raise(Exception "div by zero")
```


<a id="question-p6c"></a>
### Professor Q6c - Tail-recursive first match

Source: Professor practice set, original question 6c.

```text
6c. Write a function 'find_first' that takes a predicate and returns as
    an Option the first value in the list that satisfy the predicate, if
    it exists.  The function must be tail-recursive.
```


<a id="question-p6d"></a>
### Professor Q6d - Tracing option composition

Source: Professor practice set, original question 6d.

```text
6d. Given
  open Option
  let a = Some 8
  let b = Some 4
  
  what is the value of
  b |> bind (fun y -> if y=0 then None else a |> map (fun x -> x/y))
```


<a id="question-p8"></a>
### Professor Q8 - Expression-tree evaluation

Source: Professor practice set, original question 8.

```text
8. Given

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


<a id="question-m10"></a>
### Mock Q10 - Option.map and Option.bind (8 points)

Source: Mock Midterm, original question 10.

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


<a id="question-m11"></a>
### Mock Q11 - Expression trees in F# (8 points)

Source: Mock Midterm, original question 11.

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


<a id="question-s7"></a>
### Scary Q7 - Options and addition

Source: Scary Test, original question 7.

Given two int option values a and b, explain what, if anything, is wrong:
```fsharp
a |> Option.bind (fun x -> b |> Option.map (fun y -> x+y))
  |> Option.iter (printfn "sum is %d")
```


<a id="question-s9"></a>
### Scary Q9 - Division with Number and options

Source: Scary Test, original question 9.

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


<a id="question-s9b"></a>
### Scary Q9b - Division without pattern matching

Source: Scary Test, original question 9b.

**Context:** The Number type, times and inverse definitions are in [Scary Q9](#question-s9).

Write the divide function from Question 9 without pattern matching, using map/bind.


---

<a id="topic-4"></a>
## 4. Mutable closures, streams and comparison to OOP

**Schedule:** Day 2

**Topics:** Captured mutable bindings; independent/shared state; tracing closures; streams of type unit -> option; limit; take_while; filter; foreach; functional expression trees versus OOP.

GNU C comparisons appear in [Topic 5](#topic-5). Expression-tree construction and evaluation appear in [Topic 3](#topic-3).


<a id="question-p9"></a>
### Professor Q9 - Mutable closures

Source: Professor practice set, original question 9.

```text
9. Determine the output of the following program:

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


<a id="question-m5"></a>
### Mock Q5 - Mutable closure (8 points)

Source: Mock Midterm, original question 5.

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


<a id="question-s1"></a>
### Scary Q1 - Functions and mutable state

Source: Scary Test, original question 1.

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


<a id="question-p18"></a>
### Professor Q18 - Stream limit

Source: Professor practice set, original question 18.

```text
18. Concerning streams in F# such as the following (infinite odd numbers):

    let mutable x = 1
    let oddstream = fun () ->
      x <- x+2
      Some(x-2)
      
    Show how to define a stream modifier `limit` that would limit the
    stream to a certain number, i.e oddstream |> limit 10, should limit
    the stream to the first 10 odds.
```


<a id="question-p18b"></a>
### Professor Q18b - Stream take_while

Source: Professor practice set, original question 18b.

**Context:** Stream context: [Professor Q18](#question-p18).

```text
18b. Show how to define a stream modifier take_while that would return
     values that satisfy a predicate, and None otherwise.
```


<a id="question-p18c"></a>
### Professor Q18c - Stream filter

Source: Professor practice set, original question 18c.

**Context:** Stream context: [Professor Q18](#question-p18).

```text
18c. (harder) Show how to define a stream modifier `filter` that takes
     a predicate and modifies a stream to only return values that satisfy
     the predicate.
```


<a id="question-m9"></a>
### Mock Q9 - Limit a stream (8 points)

Source: Mock Midterm, original question 9.

Given this F# stream:
```fsharp
let oddstream() =
    let mutable x = 1
    fun () -> x <- x + 2; Some(x - 2)
```
Write a stream modifier `limit` that limits a stream to the first n values, unless None occurs earlier. For example, `oddstream() |> limit 5` should represent 1,3,5,7,9.

A stream here is a function of type `unit -> 'a option`, not a built-in sequence. The modified stream should return None after it ends.


<a id="question-s8a"></a>
### Scary Q8a - Stream take_while

Source: Scary Test, original question 8a.

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


<a id="question-s8b"></a>
### Scary Q8b - Stream foreach

Source: Scary Test, original question 8b.

**Context:** The odds() definition is in [Scary Q8a](#question-s8a).

Write foreach, taking an action of type 'T -> unit and a stream of type unit -> 'T option. Call the action on each value until the stream ends.
```fsharp
odds() |> foreach (printf "%d ")
// prints 1 3 5 7 9 11 ... through 99
```


<a id="question-m12"></a>
### Mock Q12 - Expression tree design tradeoffs (4 points)

Source: Mock Midterm, original question 12.

**Context:** Required setup: [Mock Q11: Java expression tree](#question-m11).

Identify a distinct advantage of each expression tree approach in Question 11: Java classes and F# discriminated unions. Be specific to extending this expression tree program.


---

<a id="topic-5"></a>
## 5. Limitations of C

**Schedule:** Day 2

**Topics:** C support for functional and object-oriented programming; function pointers versus capturing closures; GNU C extensions; whether returned functions preserve needed state.

Read the linked F# setup before each cross-language question. These are C/closure questions from the confirmed topic list; the standalone memory unit is excluded.


<a id="question-p19"></a>
### Professor Q19 - GNU C and escaping functions

Source: Professor practice set, original question 19.

```text
19.  Explain why in (Gnu) C the K combinator cannot be defined as follows:

    typedef int (*intfun)(int);
    intfun K(int x) {
       int inner(int y) { return x; }
       return inner;
    }
```


<a id="question-m6"></a>
### Mock Q6 - Closures in GNU C (5 points)

Source: Mock Midterm, original question 6.

**Context:** Required setup: [Mock Q5: makeswitch](#question-m5).

Is it possible to write the previous problem's makeswitch function in (GNU) C? Explain why or why not, considering the same independent, escaping closure behavior and restrictions.


<a id="question-s1b"></a>
### Scary Q1b - GNU C

Source: Scary Test, original question 1b.

**Context:** Required setup: [Scary Q1: f and g](#question-s1).

Which of the functions above can be written in GNU C? Explain.


---

<a id="topic-6"></a>
## 6. OOP essentials

**Schedule:** Day 2

**Topics:** The professor's three D's; static/runtime types; dynamic dispatch; overloading/overriding; abstract classes and pure virtual functions; casts; C/C++/Java support.

Professor Q12 and Mock Q8 overlap allocation and OOP. They are retained because the three D's remain on the supplied OOP scope; the memory exclusion does not specifically settle these mixed questions. Treat them as lower priority pending clarification. Their premises have technical qualifications in the handoff; consult its corrections when checking answers. Also see [Professor Q15](#question-p15) for return-type variance and [Mock Q12](#question-m12) for design tradeoffs.


<a id="question-p12"></a>
### Professor Q12 - Dynamic allocation and OOP

Source: Professor practice set, original question 12.

```text
12. Explain why advanced object oriented programming requires dynamic
    memory allocation.  Why is stack allocation not enough?
```


<a id="question-p12b"></a>
### Professor Q12b - Dynamic dispatch and runtime typing

Source: Professor practice set, original question 12b.

```text
12b.    Explain what is meant by "dynamic dispatch" and "dynamic typing"
```


<a id="question-p13"></a>
### Professor Q13 - Overloading versus overriding

Source: Professor practice set, original question 13.

```text
13. What's the difference between "overloading" and "overriding"?
    Give an example of each.
```


<a id="question-p14"></a>
### Professor Q14 - Pure virtual functions

Source: Professor practice set, original question 14.

```text
14. Given an example of a "pure virtual function" in the context of
    the shapes example in C++.
```


<a id="question-m8"></a>
### Mock Q8 - Dynamic memory and OOP (6 points)

Source: Mock Midterm, original question 8.

Explain why dynamic memory allocation is required for advanced object-oriented programming. Give an example. Be precise about runtime object creation and object lifetimes.


<a id="question-m13"></a>
### Mock Q13 - Java overloading (6 points)

Source: Mock Midterm, original question 13.

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


<a id="question-s5"></a>
### Scary Q5 - Java overload resolution

Source: Scary Test, original question 5.

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

<a id="topic-7"></a>
## 7. Templates, generics and variance

**Schedule:** Day 2

**Topics:** Purpose of generic types/templates; subtype substitution; covariance; contravariance; array covariance; mutable generic containers; covariant return types.

Mock Q7 spans topics: parts (a)/(c) belong here; part (b) also belongs to [Topic 8](#topic-8). The whole question is kept together to preserve all instructions and code.


<a id="question-p1"></a>
### Professor Q1 - Covariance and contravariance

Source: Professor practice set, original question 1.

```text
1. Explain what is meant by "covariance" and by "contravariance".  Under
   what circumstances is each principle valid?  Give an example of each.
```


<a id="question-p2"></a>
### Professor Q2 - Java arrays versus generic collections

Source: Professor practice set, original question 2.

```text
2. What's the difference between the following two lines in Java. Will
   either compile and run?

    i. Object[] A = new String[10];
   ii. ArrayList<Object> B = new ArrayList<String>();
```


<a id="question-p15"></a>
### Professor Q15 - Covariant return types

Source: Professor practice set, original question 15.

```text
15. Explain if the following compiles in Java:

    interface I {
      Object f();
    }
    class A implements I {
      public String f() { return "abc"; }
    }
```


<a id="question-m7"></a>
### Mock Q7 - Java compilation and runtime errors (9 points)

Source: Mock Midterm, original question 7.

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


<a id="question-s4"></a>
### Scary Q4 - Java array covariance

Source: Scary Test, original question 4.

Explain why this should or should not compile, regardless of whether Java actually allows it:
```java
Object[] A = new String[4];
```


---

<a id="topic-8"></a>
## 8. How generics are implemented

**Schedule:** Day 2

**Topics:** C++ template instantiation and concepts; Java erasure, generic arrays and static fields; C#/F# CLR generics and runtime type arguments; implementation comparisons.

Also attempt [Mock Q7(b)](#question-m7). These sets directly cover C++ and Java, with no dedicated C#/F# generic-implementation question. C#/F# remains part of the explicit exam scope.


<a id="question-p10"></a>
### Professor Q10 - C++ versus Java generic implementation

Source: Professor practice set, original question 10.

```text
10. Concerning templates (generics), explain the differences between how
    they're implemented in C++ compared to Java.
```


<a id="question-p11"></a>
### Professor Q11 - C++20 concepts

Source: Professor practice set, original question 11.

```text
11. C++20 introduced "concepts", illustrated in

      template<typename T> requires std::totally_ordered<T>

    Explain whether the program will still compile if the "requires"
    clause is dropped.
```


<a id="question-p15b"></a>
### Professor Q15b - Generic static fields

Source: Professor practice set, original question 15b.

```text
15b. How about the following:

    class A<T> {
      T x;
      static T y;
    }
```


<a id="question-m14"></a>
### Mock Q14 - C++ templates (6 points)

Source: Mock Midterm, original question 14.

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


<a id="question-s3"></a>
### Scary Q3 - Java generic static field

Source: Scary Test, original question 3.

Explain whether this class compiles:
```java
class A<T> {
    static T x;
}
```


---

<a id="excluded-memory"></a>
## Excluded reference: memory management

**Schedule:** Outside the study plan

**Topics:** Allocation/deallocation strategies; stack versus heap as a standalone unit; memory errors; object lifetime.

Ryan reported on November 2, 2026 that memory management will not be covered. These original questions are retained only to preserve the complete collection. Skip them during study.


<a id="question-p16"></a>
### Professor Q16 - Memory-error diagnosis

Source: Professor practice set, original question 16.

```text
16. (maybe) Determine if the following C++ code contain any memory errors, and if so,
    what type of errors:

    int* px = new int(3);
    int* qx = new int(4);
    px = qx;
    delete px;
    delete qx;
```


<a id="question-p17"></a>
### Professor Q17 - Object lifetime

Source: Professor practice set, original question 17.

```text
17. Explain what's meant by the "lifetime" of a value in memory.  When does
    lifetime end?
```


---

<a id="administrative"></a>
## Administrative exam item

**Schedule:** Reference only

**Topics:** Original exam instruction.

Preserved for completeness; this is not a study topic.


<a id="question-m1"></a>
### Mock Q1 - Name (10 points)

Source: Mock Midterm, original question 1.

Write your name on the exam.
