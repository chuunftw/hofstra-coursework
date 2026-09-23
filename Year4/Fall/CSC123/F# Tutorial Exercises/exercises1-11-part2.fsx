
printfn "                 F# TUTORIAL EXERCISES 1-11 + PART II"


// Exercise 1: Define the S combinator.
let S x y z = x z (y z)

printfn "\nExercise 1 - S Combinator"
printfn "Result: %A"
    (S (fun x1 y1 -> x1 + y1) (fun z1-> z1 * 2) 3)


// Exercise 2: Apply printfn to 1 and g(2,4).
let g (x, y) = x + y

printfn "\nExercise 2 - Function Application"
printfn "Result: %d %d" 1 (g (2, 4))


// Exercise 3: Apply a function twice.
let square f = fun x -> f (f x)
let quadruple = square (fun a -> 2 * a)

printfn "\nExercise 3 - Applying a Function Twice"
printfn "quadruple 3 = %A" (quadruple 3)


// Exercise 4: Verify that F# uses static rather than dynamic scoping.
// addInt uses the integer from the scope where addInt was defined.
let integer = 1
let addInt () = integer + 1

let main () =
    let integer = 2
    printfn "Value of integer inside main: %d" integer
    printfn "Result of addInt (): %d" (addInt ())

printfn "\nExercise 4 - Static vs. Dynamic Scoping"
main ()
printfn "Conclusion: addInt uses the outer value 1, so F# uses static scoping."


// Exercise 5: Apply an action to every value in a list.
let rec forloop a b action =
    if a < b then
        action a
        forloop (a + 1) b action

let foreach (list: 'a list) action =
    forloop 0 list.Length (fun i -> action list[i])

let exercise5Values = [1; 4; 5; 3; 6; 11]

printfn "\nExercise 5 - foreach"
printfn "Input: %A" exercise5Values
printfn "Output:"
foreach exercise5Values (fun x -> printfn "  x is %d" x)


// Exercise 6: Multiply two Numbers while keeping precision where possible.
type Number =
    | Integer of int
    | Rational of int * int
    | Real of float
    | Complex of float * float

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

printfn "\nExercise 6 - Number Multiplication"
printfn "2 * 1/3 = %A" (multiply (Integer 2) (Rational(1,3)))
printfn "(1 + 2i) * (3 + 4i) = %A" (multiply (Complex(1.0,2.0)) (Complex(3.0,4.0)))


// Exercise 6b: Return a string representation of each Number.
let numToStr num =
    match num with
    | Integer x -> string x
    | Rational(a,b) -> sprintf "%d/%d" a b
    | Real x -> string x
    | Complex(a,b) -> sprintf "%f + %fi" a b

printfn "\nExercise 6b - Number Strings"
printfn "Integer: %s" (numToStr (Integer 2))
printfn "Rational: %s" (numToStr (Rational(1,3)))
printfn "Real: %s" (numToStr (Real 2.5))
printfn "Complex: %s" (numToStr (Complex(2.0,3.0)))


// Exercise 7: Repeat every value in a custom linked list.
type LList<'T> =
    | Nil
    | Cons of 'T * LList<'T>

let rec doubleup list =
    match list with
    | Nil -> Nil
    | Cons(head, tail) -> Cons(head, Cons(head, doubleup tail))

let exercise7Values = Cons(2, Cons(4, Cons(7, Nil)))

printfn "\nExercise 7 - doubleup"
printfn "Input: %A" exercise7Values
printfn "Result: %A" (doubleup exercise7Values)


// Exercise 8: Count values that satisfy the predicate.
let rec howmany predicate list =
    match list with
    | Nil -> 0
    | Cons(head, tail) ->
        if predicate head then
            1 + howmany predicate tail
        else
            howmany predicate tail

let numbers = Cons(2, Cons(3, Cons(5, Cons(6, Cons(9, Nil)))))

printfn "\nExercise 8 - howmany"
printfn "Input: %A" numbers
printfn "Odd values: %d" (howmany (fun x -> x % 2 = 1) numbers)


// Exercise 9: Keep values that satisfy the predicate.
let rec filter predicate list =
    match list with
    | Nil -> Nil
    | Cons(head, tail) ->
        if predicate head then
            Cons(head, filter predicate tail)
        else
            filter predicate tail

printfn "\nExercise 9 - filter"
printfn "Input: %A" numbers
printfn "Odd values: %A" (filter (fun x -> x % 2 = 1) numbers)


// Exercise 9b: Keep values up to and including the first match.
let rec until predicate list =
    match list with
    | Nil -> Nil
    | Cons(head, tail) ->
        if predicate head then
            Cons(head, Nil)
        else
            Cons(head, until predicate tail)

printfn "\nExercise 9b - until"
printfn "Input: %A" numbers
printfn "Through 5: %A" (until (fun x -> x = 5) numbers)


// Exercise 10: Check whether every value in the first list appears in the second.
let rec forall predicate m =
    match m with
    | Nil -> true
    | Cons(a,b) -> predicate a && forall predicate b

let thereExists predicate m =
    not (forall (fun x -> not (predicate x)) m)

let subset firstList secondList =
    forall
        (fun x -> thereExists (fun y -> x = y) secondList)
        firstList

let first = Cons(2, Cons(4, Nil))
let second = Cons(4, Cons(2, Cons(3, Cons(4, Nil))))

printfn "\nExercise 10 - subset"
printfn "First list: %A" first
printfn "Second list: %A" second
printfn "Result: %A" (subset first second)


// Exercise 11: Convert a custom linked list to a native F# list.
let rec toNativeList list =
    match list with
    | Nil -> []
    | Cons(head, tail) -> head :: toNativeList tail

printfn "\nExercise 11 - Native List Conversion"
printfn "Input: %A" numbers
printfn "Result: %A" (toNativeList numbers)


printfn "\n                 PART II"


// Exercise II.1: Fix the countdown by adding one line, without references.
let countdown x =
    let mutable x = x
    while x > 0 do
        printfn "%d" x
        x <- x - 1

printfn "\nExercise II.1 - Countdown"
printfn "Input: 3"
printfn "Output:"
countdown 3


// Exercise II.2: Test whether a function receives the same array or a copy.
let changeFirst (values: int[]) =
    values[0] <- 99

let arrayValues = [|2; 3; 5|]

printfn "\nExercise II.2 - Passing an Array"
printfn "Before: %A" arrayValues
changeFirst arrayValues
printfn "After: %A" arrayValues
printfn "Conclusion: the function receives a reference to the same array."
printfn "Changing an element changes its contents; arrayValues still refers to the same array."
