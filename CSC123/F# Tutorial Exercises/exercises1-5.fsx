
printfn "                 F# TUTORIAL EXERCISES 1-5"


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

