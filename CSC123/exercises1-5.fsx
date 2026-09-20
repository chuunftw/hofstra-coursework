// F# Tutorial Exercises 1-5

printfn "============================================================"
printfn "                 F# TUTORIAL EXERCISES 1-5"
printfn "============================================================"

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


// Exercise 4: Not completed yet.

printfn "\nExercise 4 - Static vs. Dynamic Scoping"
printfn "Status: Not completed yet."


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

printfn "\n============================================================"
printfn "                       END OF OUTPUT"
printfn "============================================================"
