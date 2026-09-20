//syntax 

let i = fun x -> x // λx.x
let k = fun x y -> x // k = λx.λy.x
//printfn "%A" (i 3)  // "%A" is equal to "this"

// print "this" value 
let f x = x+1 //quickest way to define function 
//printfn "%A" (f 3);

i (8)

//EXERCISE 1: define the combinator S 
//reminder: S = λx.λy.λz. x z (y z)
let S x y z= x z (y z)
printfn "Exercise 1 - S: %A" (S (fun x1 y1 -> x1 + y1) (fun n -> n * 2) 3)
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

let func1() = printfn "hello" // func w/ no arguments 


let rec forloop a b action =
    if a<b then 
        action a
        forloop (a+1) b action
forloop 0 10 (fun x -> printfn "x is %d" x) // prints x is 0 to 9	

//there is another way to apply a function to an argument, written arg |> f as in
let h x y = x + y 
printfn "%A" (3 |> (4 |> h)) // same as (h 3 4)  
printfn "%A" ((3,4) ||> h) // also same as (h 3 4), uncurries h internally

//tuples and lists 
let a = (1,2,4.1)  // This is a tuple of type int*int*float
let b = [1;2;4]  // This is a 'int list'
let c = [(1,2,4);(2,3,4)]  // list of tuples
let lenb = b.Length
let first = b[0]
printfn "b length: %A first b value: %A" lenb first 

//To extract the individual values from a tuple you can deconstruct it by pattern matching:
//let (x,y,z) = a //let a = (1,2,4.1)
//This will set x to 1, y to 2 and z to 4.1.

//Exercise 5: Modify the forloop function defined above into a for-each loop. 
//It should take a function and apply it to every value in the list.
let foreach (list: 'a list) action = // : 'a list tells F# this parameter is a list
    forloop 0 list.Length (fun i -> action list[i])
foreach [1;4;5;3;6;11] (fun x -> printfn "x is %d" x)