module MidtermStudyGuide

(*
MIDTERM STUDY GUIDE + PRACTICE
Based on your uploaded "Sample Solutions to Practice Problems on Midterm
Study Guide." Answers are in 02_MidtermSolutions.fs, with matching numbers.
Java and C++ snippets are inside F# comments so this remains an F# file.

HOW TO USE
1. Review the notes, then cover them and explain each idea aloud.
2. Attempt the problems without opening the solutions file.
3. Check both your answer AND your explanation. Retry missed problems later.
4. For a timed review, attempt P01-P20 in 75-90 minutes.

QUICK REVIEW

A. VARIANCE AND TYPE SAFETY
If Dog is a subtype of Animal:
- Covariant output: a function returning Dog can replace one returning Animal.
- Contravariant input: a function accepting Animal can replace one accepting Dog.
- Together: Animal -> Dog can replace Dog -> Animal.
These are safe substitution rules; a language need not allow every safe conversion.
A mutable container that both reads and writes generally must be invariant.
Java arrays are covariant but check writes at runtime. Java generic classes such
as ArrayList<T> are invariant. Wildcards provide restricted views:
? extends Animal: read as Animal; cannot add a specific non-null Animal.
? super Dog: can add Dog; reading gives Object without a cast.
Memory cue: producer extends, consumer super.

B. F# FUNCTIONS, RECURSION, AND OPTIONS
let f (x,y) = x+y      // int * int -> int: one tuple argument
let g x y = x+y        // int -> int -> int: curried
let add3 = g 3         // partial application, int -> int
A recursive call is in tail position when its result is returned directly:
no addition, list construction, or other work remains after it returns.
An accumulator stores progress so recursion can be tail-recursive.
p x && loop rest can be tail-recursive because && short-circuits.
Some x means a present result; None means no result.
Option.map:  ('a -> 'b) -> 'a option -> 'b option
Option.bind: ('a -> 'b option) -> 'a option -> 'b option
map transforms a present value; bind chains an operation that can fail.
Integer division truncates toward zero. For these exercises, assume values fit
in int and exclude Int32.MinValue / -1; handling every arithmetic failure is extra.

C. SCOPE AND CLOSURES
Lexical/static scope resolves a name using where a function is DEFINED.
Dynamic scope resolves it using the active calling environment.
A closure combines function code with captured bindings. A captured mutable
binding is shared by closures capturing that same binding. Separate factory
calls can create separate mutable bindings.
Temporarily changing a global can simulate some dynamic-scope behavior; restore
it with try/finally. Explicit environment parameters are another approach.

D. EXPRESSION TREES
Discriminated unions describe alternatives; recursive cases build trees.
Evaluation recursively reduces children, combines values, and propagates errors.
An evaluator need not be tail-recursive unless explicitly required.

E. GENERICS AND C++ CONCEPTS
Java generics mostly use erasure: T becomes its upper bound (Object if unbounded),
with casts/bridge methods where needed. One class type parameter cannot be used
as a static field's type: a static field belongs to the class, not each T.
C++ templates are instantiated for requested arguments. Some checks occur at
initial definition; dependent operations are checked at instantiation.
Concepts constrain template arguments and participate in overload resolution.
Dropping a requires clause may still compile for valid arguments, but can change
overload selection and errors. Templates are not simply "never type-checked."

F. OBJECT-ORIENTED DISPATCH AND MEMORY
Overloading: same name, different parameter lists; Java chooses the signature
using compile-time types. Overriding: subclass supplies an inherited instance
method's implementation; runtime receiver selects the implementation.
Dynamic dispatch also exists in statically typed languages; it is not dynamic typing.
A covariant reference return is allowed when overriding in Java. Narrowing the
parameter type instead creates an overload, not an override.
C++ pure virtual member: virtual double area() const = 0;
It makes the class abstract. Use a virtual destructor for deletion through a base.
Polymorphism does not universally require heap allocation: a base reference can
refer to a stack-allocated derived object. Dynamic allocation is useful when
runtime lifetime/ownership or allocation size cannot fit a fixed local object.
Leak: allocated storage becomes unreachable without being freed.
Dangling pointer: pointer refers to an object whose lifetime has ended.
Double delete/use after free: undefined behavior, not a guaranteed exception.
Scope is name visibility; lifetime is when an object exists. Assignment usually
changes an existing object's value; a C++ move does not itself end the source
object's lifetime. A valid object can move in memory under a moving GC.

G. PULL STREAMS
Here a stream has type unit -> 'a option. Each call requests the next item.
limit n: emit at most n items, without pulling extra source items.
takeWhile p: emit a prefix; permanently stop at the first failure.
filter p: skip failures and continue searching. An infinite source with no
matching item can make a single filtered pull run forever.
We use permanent end-of-stream: after None, future calls also return None.

SOURCE CORRECTIONS TO REMEMBER
- The uploaded Fibonacci solution has misspelled/wrong helper calls.
- The scope example prints nothing until g() is called.
- The alternate Divide evaluator can return the original unevaluated expression
  on error; errors must propagate as RuntimeError.
- C++ B must inherit A for override; pointers use ->; overload examples must
  have parameter types matching the actual arguments.
- The uploaded take_while can resume after failure; our version stays stopped.
- A returned GNU C nested-function pointer is unsafe after the enclosing call
  ends; ordinary C does not support nested function definitions at all.

PRACTICE PROBLEMS — WRITE ANSWERS BEFORE OPENING FILE 02

P01. Function variance
Assume Dog <: Animal. Which can safely replace Dog -> Animal?
(a) Animal -> Dog (b) Dog -> Dog (c) Animal -> Animal
(d) Poodle -> Animal, where Poodle <: Dog. Explain each decision.
Why is an unrestricted mutable Box<Dog> not a Box<Animal>?

P02. Java array covariance and generics
For each independent snippet, say: compile error, successful execution, or
runtime failure. Explain the exact operation that causes failure.
(a) Object[] xs = new String[2]; xs[0] = "hi"; xs[1] = 42;
(b) ArrayList<Object> xs = new ArrayList<String>();
(c) List<? extends Number> xs = new ArrayList<Integer>(); xs.add(3);
(d) List<? super Integer> xs = new ArrayList<Number>(); xs.add(3);
What static type can you safely use for xs.get(0) in (d)?

P03. Currying and inferred types
let f (x,y) = x+y
let g x y = x+y
let h = g 7
Give the types of f, g, h. Evaluate h 5 and f (7,5).
Explain why f 7 and g (7,5) fail for these definitions.

P04. Tail-recursive Fibonacci
Use F1=1, F2=1. Explain why the naive two-call implementation is not
tail-recursive. Write fib : int -> int using a tail-recursive helper.
Reject n < 1 using invalidArg. Give fib 1, fib 2, fib 7.
Compare the naive and accumulator versions' time complexity.

P05. Tail position
Which recursive calls are in tail position? Explain short-circuit evaluation.
(a) let rec sum xs = match xs with [] -> 0 | h::t -> h + sum t
(b) let rec all p xs = match xs with [] -> true | h::t -> p h && all p t
(c) let rec copy xs = match xs with [] -> [] | h::t -> h :: copy t
(d) let rec any p xs = match xs with [] -> false | h::t -> p h || any p t

P06. Option composition
Write safeDiv : int -> int -> int option with None for a zero denominator.
Evaluate:
Some 3 |> Option.bind (fun y -> Some 14 |> Option.bind (fun x -> safeDiv x y))
Replace Some 3 with Some 0, then None. What changes?
Why use bind rather than map with a function returning an option?

P07. Tail-recursive counting
Write howmany xs predicate without List.filter or List.length.
Example: howmany [-2;0;3;4;7] (fun x -> x > 0) = 3.
Give its time complexity and explain the accumulator invariant.

P08. First match
Write tail-recursive find_first predicate xs, returning an option.
Evaluate it for even numbers in [3;7;8;10], and for [].
Explain why it should not evaluate the predicate after the first match.

P09. Lexical scope
let x = 10
let f y = x + y
let g () =
    let x = 99
    f 2
What does g() return? What would it return under dynamic scope?
Show a mutable-global simulation that restores the old value even if f throws.

P10. Stateful closures
let make n =
    let mutable x = n
    fun y -> x <- x+y; x
let a = make 10
let b = make 10
let c = a
Evaluate in order: a 2; a 3; b 4; c 1; b 0.
Which closures share state? Must a itself be declared mutable?

P11. Expression evaluator
Using the expr type below, implement eval : expr -> expr.
Propagate RuntimeError; integer division by zero yields RuntimeError.
Predict these results before running:
(a) Plus(Num 3, Times(Num 4, Num 2))
(b) Divide(Num 7, Num 2)
(c) Times(Num 0, Divide(Num 1, Num 0))
(d) Divide(RuntimeError, Num 2)

P12. Java erasure
(a) Why is class Box<T> { static T value; } rejected?
(b) What is T erased to in class Box<T extends Number> { T value; }?
(c) Can you write new T() or new T[10] inside an ordinary generic class?
(d) Contrast Java generics and C++ templates without claiming C++ skips checks.

P13. C++ concepts
Given template<typename T> requires std::totally_ordered<T>
bool before(T a, T b) { return a < b; }
If requires is removed, must every use compile? Explain for int and for a
custom type with no operator<. How can constraints help overloaded templates?

P14. Java overloading AND overriding
class A {
    String f(Object x) { return "A:Object"; }
}
class B extends A {
    @Override String f(Object x) { return "B:Object"; }
    String f(String x) { return "B:String"; }
}
A a = new B();
B b = new B();
Predict a.f("hi"), b.f("hi"), b.f((Object) "hi").
Separate compile-time signature selection from runtime implementation selection.

P15. Java covariance
interface I { Object f(); }
class C implements I { public String f() { return "ok"; } }
Does it compile? If I instead declares void put(Object x), does
public void put(String x) alone implement it? Explain.

P16. C++ abstraction and allocation
Write an abstract Shape with area(), a virtual destructor, and a Square.
Demonstrate dynamic dispatch through a Shape reference to a stack Square.
Why does this refute the claim that all polymorphic objects require the heap?

P17. C++ memory diagnosis
int* p = new int(3);
int* q = new int(4);
p = q;
delete p;
delete q;
Identify the leak and double delete precisely. Is *q valid after delete p?
Show a corrected version using std::unique_ptr.

P18. Lifetime, scope, and moves
Distinguish scope from lifetime. Does assigning 9 to an existing int end that
int object's lifetime? Does std::move(s) itself destroy s? Explain why a pointer
to a local variable must not be returned for use after the function exits.

P19. Pull-stream modifiers (larger coding problem)
Write makeOdds(), limit n stream, takeWhile predicate stream, and
filterStream predicate stream. Use permanent termination after None.
A fresh odds stream emits 1,3,5,... . For independent fresh sources, predict:
(a) makeOdds() |> limit 3                         (five pulls)
(b) makeOdds() |> takeWhile (fun x -> x < 6)      (five pulls)
(c) makeOdds() |> filterStream (fun x -> x % 3 = 0) |> limit 3
Explain why filterStream must keep pulling after a failed predicate, and why
limit 0 should not pull the source at all.

P20. Closures in C
Why is this unsafe in GNU C, and invalid in standard C?
typedef int (*intfun)(int);
intfun K(int x) {
    int inner(int y) { return x; }
    return inner;
}
How does an F# closure avoid the captured-local lifetime problem?

EXTRA CHALLENGE P21. Combine topics
Write reciprocalOfFirstEven xs using find_first and Option.bind.
Find the first even number, then calculate integer 100 / that number safely.
Predict outputs for [3;4;8], [1;0;4], and [1;3;5].
Do not skip a matching zero to look for a later nonzero number.
*)

type expr =
    | Num of int
    | Plus of expr * expr
    | Times of expr * expr
    | Divide of expr * expr
    | RuntimeError

// Put your implementations below, or practice on paper first.
// Suggested order: P03, P06-P08, P04-P05, P09-P11, P19, P21.
