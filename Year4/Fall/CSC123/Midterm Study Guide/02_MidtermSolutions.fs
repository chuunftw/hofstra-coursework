module MidtermSolutions

(*
WORKED SOLUTIONS — attempt file 01 first.
The F# implementations are actual code; Java/C++ answers are in comments.
Compile with an F# SDK, or load in F# Interactive, then call runChecks().
Assume arithmetic fits int, excluding Int32.MinValue / -1.

P01. (a), (b), and (c) are safe replacements. Each accepts every Dog input
and returns an Animal or subtype. (d) is unsafe: it cannot accept every Dog.
If Box<Dog> were an unrestricted Box<Animal>, a caller could put a Cat into
it, violating the original promise that its contents are Dogs.

P02. (a) Compiles. The string write succeeds; the integer write (boxed as
Integer) throws ArrayStoreException because the actual array is String[].
(b) Compile error: ArrayList is invariant.
(c) Compile error at add(3): the unknown element type might be a different
Number subtype. (Adding null is allowed, but does not help here.)
(d) Compiles and runs. Integer can be stored in a supertype container.
Reading through that wildcard view gives Object.

P03. f : int * int -> int; g : int -> int -> int; h : int -> int.
h 5 = 12; f (7,5) = 12. f expects a tuple, not a single integer.
g expects an integer first, not a tuple.
*)
let f (x,y) = x+y
let g x y = x+y
let h = g 7

// P04. Naive recursion must add two results after calls return, so neither
// recursive result is returned directly. Naive time is exponential (Theta(phi^n));
// accumulator time is O(n). The helper uses constant stack with tail calls.
// Invariant: a=F_k and b=F_(k+1), with remaining=n-k advances left.
let fib n =
    if n < 1 then invalidArg "n" "Use a positive Fibonacci index."
    let rec loop remaining a b =
        if remaining = 0 then a
        elif remaining = 1 then b
        else loop (remaining-1) b (a+b)
    loop (n-1) 1 1
// fib 1 = 1; fib 2 = 1; fib 7 = 13.

(*
P05. (a) No: addition remains. (b) Yes: if p h is false, return false;
otherwise directly return the recursive result. (c) No: constructing the
cons cell remains. (d) Yes: if p h is true, return true; otherwise return
the recursive result directly. Syntax alone does not determine tail position.
*)

// P06. Integer division: 14/3 is 4, so answers are Some 4, None, None.
let safeDiv (a:int) (b:int) =
    if b = 0 then None else Some (a/b)

let divideOptions numerator denominator =
    denominator |> Option.bind (fun y ->
        numerator |> Option.bind (fun x -> safeDiv x y))
// map with safeDiv would wrap the returned option: Some(Some 4) or Some None.
// bind keeps a single option layer and propagates absence.

// P07. Invariant: count equals the number of matching values in the
// already-processed prefix. One predicate call per item: O(n) time if
// each predicate call is O(1), and constant auxiliary stack with tail calls.
let howmany xs predicate =
    let rec loop remaining count =
        match remaining with
        | [] -> count
        | x::rest -> loop rest (if predicate x then count+1 else count)
    loop xs 0

// P08. Some 8 and None. First-match search returns immediately on success;
// evaluating later elements wastes work and could trigger unwanted effects.
let rec find_first predicate xs =
    match xs with
    | [] -> None
    | x::_ when predicate x -> Some x
    | _::rest -> find_first predicate rest

(*
P09. g() returns 12 under lexical scope: f uses its defining x=10.
Under dynamic scope it would return 101 using the caller's x=99.
Defining g does not execute it. The following simulation returns 101,
then restores sharedX to 10. try/finally restores it on exceptions too.
This global-state simulation is unsuitable for concurrent use without care.
*)
let mutable sharedX = 10
let scopedF y = sharedX+y
let simulatedDynamicG () =
    let saved = sharedX
    try
        sharedX <- 99
        scopedF 2
    finally
        sharedX <- saved

(*
P10. Results in order: 12, 15, 14, 16, 14.
a and c refer to the same closure and captured mutable binding.
b has its own state from a separate make call.
a need not be mutable: the captured x changes, not the binding a.
*)
let make n =
    let mutable x = n
    fun y ->
        x <- x+y
        x

// P11. Results: (a) Num 11 (b) Num 3 (c) RuntimeError (d) RuntimeError.
// Even multiplication by zero propagates an erroneous operand in this evaluator.
type expr =
    | Num of int
    | Plus of expr * expr
    | Times of expr * expr
    | Divide of expr * expr
    | RuntimeError

let rec eval e =
    match e with
    | Num _ | RuntimeError -> e
    | Plus(a,b) ->
        match eval a, eval b with
        | Num x, Num y -> Num(x+y)
        | _ -> RuntimeError
    | Times(a,b) ->
        match eval a, eval b with
        | Num x, Num y -> Num(x*y)
        | _ -> RuntimeError
    | Divide(a,b) ->
        match eval a, eval b with
        | Num _, Num 0 -> RuntimeError
        | Num x, Num y -> Num(x/y)
        | _ -> RuntimeError

(*
P12. (a) A class type parameter is unavailable in a static context; there
is one static field per loaded class, not one per type argument.
(b) Number. (c) Neither new T() nor new T[10] is permitted here: T is not
reified as a constructible class or runtime array component type.
(d) Java checks generic bodies against declared bounds and generally erases
parameters; C++ instantiates templates, checking dependent expressions with
concrete arguments. C++ may produce multiple specialized implementations.
Neither approach guarantees that every operation has zero runtime cost.

P13. Removing the constraint does not guarantee success. int still works.
A type without operator< fails when that body is instantiated. A type with
only < could work unconstrained while failing totally_ordered, which requires
more operations. Constraints let overloads express eligibility and can help
select the more constrained overload, as well as improve diagnostics.

P14. a.f("hi") -> "B:Object". a has static type A, so f(Object) is
selected; runtime dispatch invokes B's override of that signature.
b.f("hi") -> "B:String". The more specific f(String) overload is selected.
b.f((Object) "hi") -> "B:Object". The cast makes f(Object) applicable
and f(String) inapplicable without another cast.

P15. C compiles: String is a covariant return subtype of Object, and the
implementation is public. put(String) alone does not implement put(Object):
it changes the parameter type, so it overloads instead of overriding.

P16. Valid C++ example:
#include <iostream>
struct Shape {
    virtual double area() const = 0;
    virtual ~Shape() = default;
};
struct Square : Shape {
    double side;
    explicit Square(double s) : side(s) {}
    double area() const override { return side * side; }
};
int main() {
    Square square(3);          // stack object, no new
    const Shape& shape = square;
    std::cout << shape.area(); // 9, runtime dispatch
}
Shape is abstract; Square is concrete. The reference has fixed size while
referring to a complete Square whose storage is already allocated.
Runtime-selected ownership/lifetimes often motivate heap allocation, but
virtual dispatch itself does not require heap allocation.

P17. p=q loses the last pointer to the first allocation (int(3)): a leak.
delete p destroys/frees int(4); q now dangles. Dereferencing q is use after
free; delete q attempts a second deletion. Both yield undefined behavior.
A corrected ownership version:
#include <memory>
#include <utility>
int main() {
    auto p = std::make_unique<int>(3);
    auto q = std::make_unique<int>(4);
    p = std::move(q); // frees old int(3), transfers ownership of int(4)
}                    // p frees int(4); q is empty

P18. Scope controls where a name is visible; lifetime describes when the
object exists. Assigning 9 to an int ordinarily changes its value, without
ending that object's lifetime. std::move(s) is a cast enabling move operations;
it does not destroy s. Even after a move construction from s, s still exists
until destruction; for standard-library types it is generally valid with an
unspecified state unless a stronger guarantee is provided.
A local automatic object's lifetime ends at block exit. Returning its address
does not extend its lifetime, so subsequent use through that pointer is invalid.

P19. Five pulls in (a): Some 1, Some 3, Some 5, None, None.
Five pulls in (b): Some 1, Some 3, Some 5, None, None.
(c) yields Some 3, Some 9, Some 15, then permanently None.
A filter rejects individual items; takeWhile ends the entire prefix on failure.
limit 0 must immediately return None, preserving the source's next item.
The takeWhile implementation consumes the first failing item to discover it.
*)
type Stream<'a> = unit -> 'a option

let makeOdds () : Stream<int> =
    let mutable next = 1
    fun () ->
        let result = next
        next <- next+2
        Some result

let limit n (stream: Stream<'a>) : Stream<'a> =
    let mutable remaining = max 0 n
    fun () ->
        if remaining = 0 then None
        else
            match stream() with
            | None ->
                remaining <- 0
                None
            | Some x ->
                remaining <- remaining-1
                Some x

let takeWhile predicate (stream: Stream<'a>) : Stream<'a> =
    let mutable stopped = false
    fun () ->
        if stopped then None
        else
            match stream() with
            | Some x when predicate x -> Some x
            | _ ->
                stopped <- true
                None

let filterStream predicate (stream: Stream<'a>) : Stream<'a> =
    let mutable stopped = false
    let rec pull () =
        if stopped then None
        else
            match stream() with
            | Some x when predicate x -> Some x
            | Some _ -> pull ()
            | None ->
                stopped <- true
                None
    pull

(*
P20. Standard C forbids this nested function definition. GNU C allows it
as an extension, but a nested function accessing x relies on the enclosing
call's environment (and may use a stack trampoline). Calling the returned
pointer after K returns is unsafe. A bare C function pointer does not provide
a managed closure environment. An F# closure retains its captured environment
for as long as needed, rather than leaving access to an expired stack local.
In C, explicitly package a function pointer with context data whose lifetime
is managed by the caller or through allocation.
*)

// P21. Some 25, None, None. A matching zero causes division failure;
// it does not restart the search for another even number.
let reciprocalOfFirstEven xs =
    find_first (fun x -> x % 2 = 0) xs
    |> Option.bind (fun x -> safeDiv 100 x)

// Optional self-checks: load this file in F# Interactive, then run runChecks().
// These checks throw on failure, independent of compiler assertion settings.
let runChecks () =
    let check label expected actual =
        if actual <> expected then
            failwithf "%s: expected %A, got %A" label expected actual
    check "P03" 12 (h 5)
    check "P04" [1;1;2;3;5;8;13] ([1..7] |> List.map fib)
    check "P06" (Some 4) (divideOptions (Some 14) (Some 3))
    check "P06 zero" None (divideOptions (Some 14) (Some 0))
    check "P06 missing" None (divideOptions (Some 14) None)
    check "P07" 3 (howmany [-2;0;3;4;7] (fun x -> x > 0))
    check "P08" (Some 8) (find_first (fun x -> x % 2 = 0) [3;7;8;10])
    check "P08 empty" None (find_first (fun (x:int) -> x % 2 = 0) [])
    check "P09" 101 (simulatedDynamicG())
    check "P09 restored" 10 sharedX
    let a = make 10
    let b = make 10
    let c = a
    let r1 = a 2
    let r2 = a 3
    let r3 = b 4
    let r4 = c 1
    let r5 = b 0
    check "P10" [12;15;14;16;14] [r1;r2;r3;r4;r5]
    check "P11 add" (Num 11) (eval (Plus(Num 3, Times(Num 4, Num 2))))
    check "P11 divide" (Num 3) (eval (Divide(Num 7, Num 2)))
    check "P11 error" RuntimeError (eval (Times(Num 0, Divide(Num 1, Num 0))))
    check "P11 propagation" RuntimeError (eval (Divide(RuntimeError, Num 2)))
    let pullFive stream = List.init 5 (fun _ -> stream())
    let prefix = [Some 1;Some 3;Some 5;None;None]
    check "P19 limit" prefix (pullFive (makeOdds() |> limit 3))
    check "P19 takeWhile" prefix (pullFive (makeOdds() |> takeWhile (fun x -> x < 6)))
    check "P19 filter" [Some 3;Some 9;Some 15;None;None]
        (pullFive (makeOdds() |> filterStream (fun x -> x % 3 = 0) |> limit 3))
    let mutable pulls = 0
    let source () = pulls <- pulls+1; Some pulls
    let empty = limit 0 source
    check "P19 zero" None (empty())
    check "P19 no extra pull" 0 pulls
    // Failure must stay terminal, even if the source could later emit a match.
    let mutable inputs = [Some 1;Some 8;Some 3]
    let finite () =
        match inputs with
        | [] -> None
        | x::rest -> inputs <- rest; x
    check "P19 permanent stop" [Some 1;None;None;None;None]
        (pullFive (takeWhile (fun x -> x < 6) finite))
    check "P21 success" (Some 25) (reciprocalOfFirstEven [3;4;8])
    check "P21 zero" None (reciprocalOfFirstEven [1;0;4])
    check "P21 absent" None (reciprocalOfFirstEven [1;3;5])
    printfn "All midterm self-checks passed."
