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

//Exercise 4: devise an experiment to verify that F# uses static as opposed to dynamic scoping
// Static scoping means a function finds its variables based on where the function was defined
let integer = 1
let addInt () = integer + 1
let main ()= 
    let integer = 2
    printfn "Exercise 4: %A" (addInt ())
main()
//returns 2 b/c takes 1 from scope of where function was created rather than 2 in the main


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

// Data Structures 

//discriminated unions 
type Direction =
    | North
    | East
    | South
    | West
// Number can represent numbers in diff ways 
type Number =
    | Integer of int
    | Rational of int*int
    | Real of float
    | Complex of float*float;;

// constructs a Number representing 1/3 fraction, pattern matching in a nutshell
let n = Rational(1, 3)
// deconstructs the value: a receieves 1 and b receives 3
match n with
| Rational(a, b) -> printfn "numerator: %d denominator: %d" a b
| _ -> printfn "another kind of number"

// Pattern match two Number values at once 
let equals first second =
    match (first, second) with
    | (Integer x, Integer y) -> x = y
    | _ -> false
//if called with this,  the pattern assigns x =4 and y =4
equals (Integer 4) (Integer 4)

// Checks whether two Number values are equal using pattern matching
let rec equals1 a b =
    match (a,b) with
      | (Integer x, Integer y) -> x = y
      | (Integer x, Rational(a,b)) -> x*b = a
      | (Integer x, Real a) -> float(x) = a
      | (Integer x, Complex(a,i)) -> i=0.0 && float(x) = a
      | (Rational(a,b), Rational(c,d)) -> a*d = b*c
      | (Rational(a,b), Real c) -> float(a) = float(b)*c
      | (Rational(a,b), Complex(r,i)) -> i=0.0 && float(a) = float(b)*r
      | (Real a, Real b) -> a = b
      | (Real a, Complex(r,i)) -> i=0.0 && a = r
      | (Complex(a,b), Complex(c,d)) -> a=c && b=d
      | (x,y) -> equals1 y x

equals1 (Rational (2,4)) (Rational (1,2))  // evaluates to true

//Exercise 6: Write a function that multiplies any two numbers. 
//You must also keep precision as much as possible. For example, Integer(2) multiplied by Rational(1,3) should not be a Real but a Rational(2,3). 
//Only when an Integer (or Rational) is multiplied by a Real should the result be a Real

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

    | (Real a, Real b) ->
        Real(a * b)

    | (Real a, Complex(r,i)) ->
        Complex(a * r, a * i)

    | (Complex(a,b), Complex(c,d)) ->
        Complex(a*c - b*d, a*d + b*c)

    // Handle reversed combinations by swapping the arguments.
    | (x,y) ->
        multiply y x

printfn "%A" (multiply (Integer 10) (Rational(1,3)))