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
// rec b/c function calls itself again like in like 159 
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
    // Handle reversed combinations by swapping the arguments.
    |(x,y) -> multiply y x

printfn "%A" (multiply (Integer 10) (Rational(1,3))) 


// %d → int
// %f → float
// %s → string
// %A → almost any F# value

//Exercise 6b: Write a function that returns a string representation for each type of Number
let numToStr num =
    match num with 
    | Integer x -> string x
    | Rational(a,b) -> sprintf  "%d/%d" a b
    | Real x -> string x 
    | Complex(a,b) -> sprintf "%f+%fi" a b 


// User Defined linked list
// F# already has lists, but we can also define our own linked list
// "'T" means the list can hold any one "generic" type T
type LList<'T> =
    | Nil
    | Cons of 'T * LList<'T>

// Nil is an empty list
// Cons stores the head (first) and tail (rest of the list) 
//cons ≡ λx.λy.λz.zxy
let customList = Cons( 2, Cons(4, Cons(6, Cons(8, Nil))))
//custom list = [2 → 4 → 6 → 8 → Nil]

// Cons constructs a list when it is on the right side of =
// Cons deconstructs a list when it is used in a pattern
match customList with
| Cons(firstValue, restOfList) ->
    printfn "first: %A rest: %A" firstValue restOfList
| Nil ->
    printfn "empty list"

// function is a shorter way to match directly on the function argument
// _ is a wildcard, meaning we do not need that value
let car = function
    | Cons(a,_) -> a
    | Nil -> failwith "cannot take car of an empty list"
// car returns a lists head node, error if list is nil 

let cdr = function
    | Cons(_,b) -> b
    | Nil -> Nil
// returns tail, list without the head 


let empty = function
    | Nil -> true
    | _ -> false
//checks if list is empty, true if empty, false if not

// recursive length; adds 1 after each recursive call returns
let rec listLength = function
    | Cons(_,b) -> 1 + listLength b
    | Nil -> 0

// tail recursive version uses cx as a counter
// tail recursive means the recursive call is the final operation
let tailListLength m =
    let rec inner current cx =
        match current with
        | Nil -> cx
        | Cons(_,rest) -> inner rest (cx + 1)
    inner m 0

// Exercise 7:
// Write doubleup so every value in an LList is repeated.
// Example input: Cons(2, Cons(4, Cons(7, Nil)))
// Expected values: 2, 2, 4, 4, 7, 7
// The final version should be recursive as required by the exercise.
let rec doubleup list = 
    match list with 
    | Nil -> Nil 
    | Cons(head, tail) -> Cons(head, Cons(head, doubleup tail))

let linked = Cons( 2, Cons(4, Cons(6, Cons(8, Nil))))
printfn "double linked: %A" (doubleup linked)


// map applies function f to every value and returns a new LList
// stack is an accumulator that stores the results
// this version produces the values in reverse order
// Cons adds each new result to the front of stack.
// Example: if stack is [4], adding 16 makes [16; 4], not [4; 16].
let map f m =
    let rec inner current stack =
        match current with
        | Nil -> stack
        | Cons(a,b) -> inner b (Cons(f a, stack))
    inner m Nil

// using the identity function with map reverses the list
let reverse m = map (fun x -> x) m

// apply x*x to each value, then reverse to restore the original order
let squares m = reverse (map (fun x -> x*x) m)


// reduce combines all list values into one result
// op is the function used to combine values
// id is the starting value/accumulator
let rec reduce op id m =
    match m with
    | Nil -> id
    | Cons(a,b) -> reduce op (op id a) b

// (+) and (*) turn the operators into functions
let sumExample = reduce (+) 0 customList
let productExample = reduce (*) 1 customList

// this op keeps the larger positive value
let largestExample =
    reduce (fun x y -> if x > y then x else y) 0 customList

// reduce above is left-associative
// it combines from the left using the updated id value

// Exercise 7b (optional challenge):
// Write a right-associative version of reduce that is still tail recursive.
let foldRight op id list =
    let reversed = reverse list
    let rec inner remaining accumulator =
        match remaining with 
        | Nil -> accumulator
        | Cons(head, tail) ->  inner tail (op head accumulator)
// ngl didnt really understand but its optional ig 
    inner reversed id

// predicate is a function that returns bool
// forall is true only if the predicate is true for every value
let rec forall predicate m =
    match m with
    | Nil -> true
    | Cons(a,b) -> predicate a && forall predicate b

// there_exists is true if at least one value passes the predicate
// it says: it is not true that every value fails the predicate
let thereExists predicate m =
    not (forall (fun x -> not (predicate x)) m)

// Exercise 8:
// Write howmany, which takes a predicate and an LList.
// Return how many values make the predicate true.
// Example question: how many odd values are in 2, 3, 5, 6, 9?
let rec howmany predicate ll1 = 
    match ll1 with 
    | Nil -> 0 
    | Cons(head, tail) -> 
        if predicate head then 
            1 + howmany predicate tail 
        else
            howmany predicate tail 
let numbers = Cons(2, Cons(3, Cons(5, Cons(6, Cons(9, Nil)))))

printfn "%d" (howmany (fun x -> x % 2 = 1) numbers)

// Exercise 9:
// Write filter, which takes a predicate and an LList.
// Return an LList containing only values that make the predicate true.
// The order of the returned values does not matter for this exercise.
let rec filter predicate list = 
    match list with 
    | Nil -> Nil 
    | Cons(head, tail) -> 
        if predicate head then 
            Cons(head, filter predicate tail)
        else
            filter predicate tail 
//recursivily checks if fits the predicate, new head, if fails chops head off and repeats testing new head 

// Exercise 9b:
// Write until, which takes a predicate and an LList.
// Return the list up to and including the first value that passes the predicate.
// Return the entire list when no value passes the predicate.
let rec until predicate list = 
    match list with 
    | Nil -> Nil 
    | Cons(head, tail) -> 
        if predicate head then 
            Cons(head, Nil)
        else
            Cons(head, until predicate tail) 

// Exercise 10:
// Write subset to check if every value in the first LList appears in the second.
// Order and the number of repeated values do not matter.
// Think: for every x in A, there exists a y in B where x = y.
let subset firstList secondList =
    forall
        (fun x -> thereExists (fun y -> x = y) secondList)
        firstList
//example test 
let first = Cons(2, Cons(4, Nil))
let second = Cons(4, Cons(2, Cons(3, Cons(4, Nil))))

printfn "subset:%A" (subset first second)

// Native Lists
// [2;3;4;5] is the same structure as 2::3::4::5::[]
// [] is the empty native list, like Nil in LList
// :: adds one value to the front, like Cons
// :: associates to the right, so a::b::c means a::(b::c)

let nativeList = [2;3;4;5]
let sameNativeList = 2::3::4::5::[]

// converts a native list into our LList type
let toLList m =
    let rec inner current stack =
        match current with
        | [] -> stack
        | a::b -> inner b (Cons(a,stack))
    reverse (inner m Nil)

// Exercise 11:
// Write the opposite conversion: convert an LList<'T> into a native F# list.
let rec toNativeList list =
    match list with
    | Nil -> []
    | Cons(head, tail) ->
        head :: toNativeList tail

// native lists have built-in functions in the List module
let allEven = List.forall (fun x -> x % 2 = 0) [2;4;6;8]


// More on Pattern Matching
// list patterns can check the size, values, and remaining part of a list
let explainList values =
    match values with
    | [] -> "none"
    | [y] -> sprintf "exactly one: %A" y
    | a::b::_ when a = b -> "the first two values are the same"
    | (a::b::c::rest) as wholeList ->
        sprintf "%A has at least three values" wholeList
    | _ -> "two different values"

// patterns are checked from top to bottom
// only the first matching pattern runs
// when adds another condition to a pattern
// as gives a name to the entire matched value
// _ is the wildcard and matches anything not already handled
// the same variable name cannot appear twice in one pattern

// PART II: Imperative F#
// imperative code can change values stored in memory


// Mutation
// variables are immutable by default
// mutable allows the value to change later
let mutable mutableNumber = 1

// <- changes the value stored in a mutable variable
mutableNumber <- mutableNumber + 1

// = checks equality when it is used outside a let definition
printfn "mutableNumber is 2: %A" (mutableNumber = 2)

// function parameters are immutable
// this means a function cannot use <- to change its parameter directly

// Exercise II.1:
// Fix the function below by adding one line.
// Do not use references.
//
let countdown x =
    let mutable x = x
    while x > 0 do
        printfn "%d" x
        x <- x - 1


// Loops
let mutable whileCounter = 0

// a while loop repeats while its condition is true
while whileCounter < 3 do
    printfn "whileCounter is now %d" whileCounter
    whileCounter <- whileCounter + 1

// 0..2 is a range and includes both 0 and 2
for loopValue in 0..2 do
    printfn "loopValue is now %d" loopValue

// a for loop can visit every value in a list
for listValue in [2;4;5;6] do
    printfn "%A" listValue

// F# does not have break
// the loop condition needs to decide when the loop ends


// Arrays
// [| |] creates an array; [ ] creates a list
// arrays store values next to each other in memory and are mutable
let numberArray = [|2;3;5;7|]

// = compares the current value; it does not change it
printfn "first array value equals 4: %A" (numberArray[0] = 4)

// <- changes the element at index 0
numberArray[0] <- 4

// the variable numberArray did not change to another array
// the value stored inside the existing array changed

// Array.create makes an array with a chosen size and starting value
let letterArray : char[] = Array.create 10 'a'

// array arguments often need a type annotation
let firstArrayValue (values: 'T[]) = values[0]

// Exercise II.2:
// Devise an experiment to determine what happens when an array is passed to a function.
// Does the function receive a reference to the same array, or a complete copy?
// Change an array element inside the function, then check the original array afterward.
// Explain why changing array[0] is different from changing the variable array.


// References
// a reference cell is a separate mutable location that stores a value
let originalValue = 1
let valueReference = ref originalValue

// .Value reads or changes the contents of the reference cell
valueReference.Value <- 5
printfn "reference value: %A" valueReference.Value

// originalValue is still 1 because ref copied its value into a new cell
printfn "original value: %A" originalValue

// two names can refer to the same reference cell
let referenceAlias = valueReference
referenceAlias.Value <- 6

// both names now read 6 because they point to the same cell
printfn "first reference: %A alias: %A" valueReference.Value referenceAlias.Value


// Records
// a record groups named fields and is stored on the heap
// records can also have members like a lightweight class
type Stack<'T> =
    {
        Values : 'T[]
        mutable Top : int
    }
    member this.Push value =
        if this.Top < 0 || this.Top >= this.Values.Length then
            false
        else
            this.Values[this.Top] <- value
            this.Top <- this.Top + 1
            true

    member this.Pop () =
        if this.Top > 0 then
            this.Top <- this.Top - 1
            Some(this.Values[this.Top])
        else
            None

    member this.Size () = this.Top

// generic function that creates a Stack containing any one type
let makeStack<'T> size : Stack<'T> =
    {
        Values = Array.create size Unchecked.defaultof<'T>
        Top = 0
    }

let integerStack = makeStack<int> 10

// Push returns bool, but ignore changes that result into unit
integerStack.Push 2 |> ignore
integerStack.Push 4 |> ignore

// Option prevents an invalid value from being returned when the stack is empty
match integerStack.Pop() with
| Some value -> printfn "popped %A" value
| None -> ()

// records are reference types
// passing a record gives the function access to the same record object


// Structs
// a struct is normally stored directly as a value
// passing a struct normally passes a copy of that value
[<Struct>]
type KVPair<'Key,'Value> =
    val mutable Key : 'Key
    val mutable Value : 'Value

    new(key, value) =
        {
            Key = key
            Value = value
        }

    override this.ToString() =
        sprintf "%A:%A" this.Key this.Value

let mutable pair = KVPair("B", 4)
printfn "pair: %A" pair

// structs are useful for small groups of data
// they cannot be used to create recursive structures like linked lists


// .NET Integration
// F# can use classes and collections from C# and the rest of .NET
open System.Collections.Generic

// Dictionary works like a hash map
let studentIds = Dictionary<string,int>()
studentIds["Mary"] <- 703345126
studentIds["Larz"] <- 703555667
printfn "Larz ID: %d" studentIds["Larz"]

// TryGetValue returns whether the key exists and the value it found
let foundMary, maryId = studentIds.TryGetValue("Mary")
printfn "found Mary: %A ID: %d" foundMary maryId

// arrays have a fixed size
// ResizeArray can grow and is .NET's List<'T>
let vector = ResizeArray<int>()
vector.Add(4)
printfn "vector count: %d" vector.Count
vector[0] <- 5

// .NET projects can contain code from both F# and C#
// a C# class library is built into a .dll file
// the F# project can reference that .dll in its .fsproj file
// after referencing it, F# can open the C# namespace and call its public members
