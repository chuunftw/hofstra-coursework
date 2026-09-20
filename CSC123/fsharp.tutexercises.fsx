//syntax 

let i = fun x -> printfn "%A"(x) // λx.x
let k = fun x y -> x // k = λx.λy.x
//printfn "%A" (i 3)  // "%A" is equal to "this"

// print "this" value 
let f x = x+1 //quickest way to define function 
//printfn "%A" (f 3);

i (8)

//EXERCISE 1: define the combinator S 
//reminder: S = λx.λy.λz. x z (y z)
let S x y z= x z (y z)
printfn "S: %A" (S (fun x1 y1 -> x1 + y1) (fun n -> n * 2) 3)
//x = fun a b -> a + b
//y = fun n -> n * 2
//z = 3

// Currying means a function takes arguments one at a time.

// curried function 
let z x y = x+y //quickest way to def func z
printfn "z: %A" (z 1 2)
// in reality: let f = fun z -> fun y -> z + y
// uncurried function 
let g(x,y) = x+y
printfn "g: %A" (g(1,2))

printfn "%d %d" 1 2


//Exercise 2: figure out how to apply printfn to 1 and g(2,4)
// correctly. And in general, the proper way to apply curried functions.
printfn "%d %d" 1 (g(2,4)) // 1, g and (2,4) are all arguments
//wrap function g to make it 1 argument 

// The following functions convert any function between its Curried and Uncurried form.
let Curry g = fun x -> fun y -> g(x,y)
let Uncurry f = fun (x,y) -> f x y

//EXERCISE 3: Define a function that takes a function and "squares" it by applying it twice.
let square f = fun x -> f (f x) //square = λf.λx. f (f x)
//def a function that takes a func and returns a new fun that applies f twice
let quadruple = square (fun a -> 2 * a) //quadruple = square(λa. 2a)
printfn "sqrt: %A" (quadruple 3)