type Number =
    | Integer of int
    | Rational of int*int
    | Real of float
    | Complex of float*float;;

let rec multiply left right =
    match (left, right) with
    | (Integer x, Integer y) -> Integer(x * y)
    | (Integer x, Rational(a,b)) -> Rational(x * a, b)
    | (Integer x, Real a) -> Real(float(x) * a)
    | (Integer x, Complex(a,b)) -> Complex(float(x) * a, float(x) * b)
    | (Rational(a,b), Rational(c,d)) -> Rational(a * c, b * d)
    | (Rational(a,b), Real c) -> Real((float(a) / float(b)) * c)
    | (Rational(a,b), Complex(r,i)) ->
        let fraction = float(a) / float(b)
        Complex(fraction * r, fraction * i)
    | (Real a, Real b) -> Real(a * b)
    | (Real a, Complex(r,i)) -> Complex(a * r, a * i)
    | (Complex(a,b), Complex(c,d)) -> Complex(a*c - b*d, a*d + b*c)
    | (x,y) -> multiply y x

let simplify number =
    match number with
    | Rational(a,b) when b <> 0 && a % b = 0 ->
        Integer(a / b)
    | _ -> number


let inverse num =
  match num with     // not equal
    | Integer(x) when (x<>0) -> Some(Rational(1,x))
    | Rational(a,b) when (a<>0) -> Some(Rational(b,a))
    | Real(x) when (x<>0.0) -> Some(Real(1.0/x))
    | Complex(a,b) when (a<>0.0) || (b<>0.0) -> 
        let d = a*a+b*b 
        Some(Complex(a/d , -b/d))
    | _ -> None

let divide x y =
    match inverse y with
    | Some value -> Some (simplify (multiply x value))
    | None -> None
// Monadic Error Handling in F# - condensed professor's notes
open System;

// Option and Result are built-in types used for monadic error handling.
// Option represents a value that may not exist, using Some or None.
// Its definition is:
// type Option<'T> = | None | Some of 'T

// Returning an optional value
// An empty list has no largest number, so return None.
let largest (A:int list) =
    if A.Length=0 then None
    else
        let mutable candidate = A[0]
        for i in 1..A.Length-1 do // range of 1 - A.length -1 
            if A[i] > candidate then candidate <- A[i]
        Some(candidate)

let max = largest [3;5;1;7;4;9;0;8]
// max is Option<int> (also written int option), rather than int.
// Pattern matching handles the possibility that it is None.
match max with
| Some x -> printfn "%d is the greatest value" x
| None -> printfn "an error has occurred"

// map and iter
// map applies a function if the value exists and encloses the result in Some.
// If the input is None, map returns None.
// iter applies an action returning unit, such as printing, if the value exists.
// x |> map f is equivalent to map f x. 
// |> is the pipeline operator. It passes the value on its left to the function on its right
open Option
max
    |> map (fun x -> x+x)
    |> map (fun x -> Math.Sqrt(float x)) // conversion needed for this example to compile
    |> iter (fun x -> printfn "final result is %.3f" x)

// Some(9) mapped with x+x becomes Some(18); None stays None.
// The professor's own version of map:
let mymap func opt =
    match opt with
    | Some x -> Some(func x)
    | None -> None

// Another optional result: find the first value satisfying a predicate.
let rec find_first predicate (m:'T list) =
    match m with
    | [] -> None
    | a::b when (predicate a) -> Some(a)
    | a::b -> find_first predicate b

// Arithmetic examples from the professor
let safeadd(a:int, b:int) =
    let sum = a+b
    if (a>0 && b>0 && sum<a) || (a<0 && b<0 && sum>a) then None
    else Some(sum)

let safemult(a:int, b:int) =
    let ab = a*b
    if b<>0 && ab/b <> a then None
    else Some(ab)

let safediv(a:int, b:int) =
    if b = 0 then None
    else
        let quotient = a/b
        if quotient<0 && a<0 && b<0 then None
        else Some(quotient)

(*
Option lets a function return one consistent type when it might have a value or might not:
- Some value means a value is present.
- None means no value is available.
*)

// bind
// Use bind when the function applied to the enclosed value also returns Option.
// map and bind can be mixed in a pipeline.

//bind is used when a function has several steps that might return None, 
// bind is used as a way to reduce repitition 
let final_result =
    safeadd(8,4)
        |> bind (fun x -> safediv(x,3))
        |> bind (fun x -> safeadd(x,-14))
        |> map (fun x -> x*0)
        |> bind (fun x -> safediv(1,x))

printfn "result is %A" final_result

// map versus bind: examples from the notes
// (Some 3) |> map (fun x -> x+2)          returns Some 5
// (Some 3) |> bind (fun x -> Some(x+2))   returns Some 5
// (Some 3) |> map (fun x -> Some(x+2))    returns Some(Some 5)
// bind avoids creating a nested Option when the function already returns Option.
// map and bind both return None when applied to None.

// flatten removes a nested Option:
// flatten (Some(Some 5)) returns Some 5.
// map followed by flatten is equivalent to bind.
// bind is also called flatMap in Java or and_then in Rust.
let and_then = Option.bind

// Option.get and defaultValue
// Option.get (Some 3) returns 3, but Option.get None throws an exception.
// Using get without checking for None can cause problems similar to null.
// A check is possible, but it is up to the programmer to remember it:
// if (Option.isSome x) then printfn "%A" (Option.get x)
// defaultValue requires a fallback for None. Use it only for a reasonable default.
let get_or = Option.defaultValue
let thestring = get_or "" None // returns ""

// Integrating Option with exceptions
let x = "this is not a number"
// let y = int(x) // throws an exception
// int must return an integer, but no integer represents a failed conversion.
// Catching the exception in a caller can leave that caller with the same problem.
// The professor illustrates this with an area calculation:
(*
let area() =
    try
        let radius = float(Console.ReadLine())
        Math.PI * radius * radius
    with | exception1 -> ????
*)
// Returning Option lets the function catch the exception locally and return None.
let parse_int (s:string) =
    try Some(int(s))
    with | _ -> None

// A general version that runs a supplied function:
let on_behalf f =
    try Some(f())
    with | _ -> None

let argv = Environment.GetCommandLineArgs()

on_behalf (fun () -> float(argv[2]))
    |> map (fun radius -> Math.PI * radius * radius)
    |> iter (fun area -> printfn "area is %f" area)

// fun () -> ... delays evaluation until on_behalf calls the function.
// This lets it catch errors such as missing arguments or failed conversions.

// Chaining two optional conversions and a division
on_behalf (fun () -> int(argv[2]))
    |> and_then (fun a ->
        printfn "got %d" a
        on_behalf (fun () -> int(argv[3]))
            |> and_then (fun b ->
                printfn "got %d" b
                safediv(a,b)))
    |> iter (fun q -> printfn "quotient = %d" q)

// if_else, map2 and flatten
let if_else some_func none_func = function
    | Some x -> some_func x
    | None -> none_func()

// some_func and none_func should return values of the same type.
// map2 applies a function to two optional values.
// Here safediv returns Option, so flatten removes the extra Option layer.
(on_behalf (fun () -> int(argv[2])),
 on_behalf (fun () -> int(argv[3])))
    ||> map2 (fun a b -> safediv(a,b))
    |> flatten
    |> if_else (fun q -> printfn "quotient = %d" q)
               (fun () -> printfn "no result due to errors")

// These operations let us compose calculations on optional values while
// carrying forward the possibility that an error has occurred.

// Addendum Part C
// Given the definition of Number:


// c.

let make_rat(a,b) = if b=0 then None else Some(Rational(a,b))

// This function creates a rational Number but only if b is not zero.
// 1. Write a function that takes two Option<Number> objects and multiply one
// by the other, if both exist

// bind is like map, but doesnt return it back rewrapped as some 

let optionMultiply (x1: Option<Number>) (y1: Option<Number>) = 
    x1 |> Option.bind (fun x -> y1 |> Option.map (fun y -> multiply x y))


// 2. Write a function that takes two Option<Number> objects and divide one
// by the other, if both exist

let optionDivide (x2: Option<Number>) (y2: Option<Number>) = 
    x2 |> Option.bind (fun x -> y2 |> Option.bind (fun y -> divide x y))
//inner uses bind b/c divide already returns of type option 
// Both functions should return Option<Number>.  Try to use map/bind instead
// of pattern matching (but use pattern matching if you can't do it otherwise).

// test with
let f1 = make_rat(1,2);
let f2 = make_rat(2,3);
let f3 = make_rat(2,0);
let f4 = make_rat(0,1);

printfn "optionMultiply f1 f2 = %A" (optionMultiply f1 f2) // Some(Rational(2,6))
printfn "optionMultiply f1 f3 = %A" (optionMultiply f1 f3) // None
printfn "optionDivide f1 f2 = %A" (optionDivide f1 f2)     // Some(Rational(3,4))
printfn "optionDivide f1 f3 = %A" (optionDivide f1 f3)     // None
printfn "optionDivide f4 f2 = %A" (optionDivide f4 f2)     // Some(Integer 0)
printfn "optionDivide f1 f4 = %A" (optionDivide f1 f4)     // None
