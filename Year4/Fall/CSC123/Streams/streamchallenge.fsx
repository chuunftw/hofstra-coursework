// CSC123 - Challenge practice: questions 6b and 8
// Name:
// Date:
// Prerequisite definitions copied from streamscopy.fsx are below.
// Challenge bodies are intentionally unfinished. Uncomment tests as you go.
// From the Year4 terminal folder:
// dotnet fsi ".\Fall\CSC123\Streams\streams_challenge_practice.fsx"

open System

type Vec<'T> = ResizeArray<'T>
type Stream<'T> = unit -> Option<'T>

// =====================================================================
// PREREQUISITE FUNCTIONS
// =====================================================================

let omap = Option.map

let obind = Option.bind

let oiter = Option.iter

let is_some = Option.isSome

let is_none = Option.isNone

let get_or = Option.defaultValue

let mutable n = 0

let evenints() = fun () -> (n <- n+2; Some(n-2))

let limit n stream =
  let mutable counter = 0
  fun () ->
    if counter >= n then None
    else
      counter <- counter + 1
      stream()

let map mapfun stream =
  fun () -> stream() |> omap mapfun

let map_oflatten mapfun stream =  fun () -> stream() |> obind mapfun

let filter predicate stream =
  let rec inner next =
    match next with
      | Some(x) when (predicate x) -> next
      | Some(x) -> inner (stream())
      | None -> None
  fun () -> inner (stream())

let filter_alt predicate stream =
  fun () ->
    let mutable next = stream()
    let notp = fun x -> not(predicate x)
    while (next |> omap notp |> get_or false) do
      next <- stream()
    next

let take_while predicate stream =
  fun () -> stream()
            |> obind (fun x -> if predicate(x) then Some(x) else None)

let flatten nested_stream =
  let mutable current_stream = nested_stream() // Option<stream>
  let rec inner next =
    match (next,current_stream) with
      | (Some x,_) -> next
      | (None,Some(stream)) ->
        current_stream <- nested_stream()
        inner (current_stream |> obind (fun s -> s()))
      | (None,None) -> None
  fun () -> inner (current_stream |> obind (fun s -> s()))

let flatten_alt nested_stream =
  let mutable current_stream = nested_stream() // Option<stream>
  fun () ->
    let mutable next = current_stream |> obind (fun strm -> strm())
    while (is_none next) && (is_some current_stream) do
      current_stream <- nested_stream() 
      next <- current_stream |> obind (fun strm -> strm())
    next

let bind binder stream = stream |> map binder |> flatten

let to_stream opt =
  match opt with
    | None -> fun() -> None
    | Some x ->
       let mutable singleton = true
       fun () ->
         if singleton then singleton <- false; Some(x)
         else None

let append stream1 stream2 =
  fun () -> 
    let next = stream1()
    match next with
      | Some(x) -> next
      | None -> stream2()

let (+++) a b = append a b      // defines an infix operator

let except stream =
  fun () ->
    try stream()
    with | _ -> None

let foreach action stream =  // apply action to each element of stream
  let rec inner next =
    match next with
      | Some x ->
        action x
        inner (stream())
      | None -> ()
  inner (stream())

let for_each action stream =
  let mutable next = stream()
  while (is_some next) do
    next |> oiter action // perform action on the option object
    next <- stream()     // get next value

let forall predicate stream =
  let rec inner next =
    match next with
      | None -> true
      | Some x when (predicate x) -> inner (stream())
      | Some x -> false
  inner (stream())

let for_all predicate stream =
  let mutable answer = true
  let mutable next = stream()
  while answer && (is_some next) do
    if not(next |> omap predicate |> get_or true) then answer <- false
    else next <- stream()
  answer

let there_exists predicate stream =
  not(for_all (fun x -> not(predicate x)) stream)

let find_first predicate stream =
  let rec inner next =
    match next with
      | Some(x) when (predicate x) -> next
      | Some(x) -> inner (stream())
      | None -> next
  inner (stream())

let nth n stream =
  let mutable cx = 0
  let mutable next = stream()
  while cx<n && (is_some next) do
    next <- stream()
    cx <- cx+1
  next

let reduce op id stream =
  let rec inner ax next =
    match next with
      | None -> ax
      | Some x -> inner (op ax x) (stream())
  inner id (stream())

let reduce_alt op id stream =
  let mutable ax = Some(id)
  let mutable next = stream()
  while (is_some next) do
    ax <- next |> obind (fun b -> ax |> omap (fun a -> op a b))
    next <- stream()
  get_or id ax

let finite_stream<'T> (m:'T list) =
  let mutable index = 0
  fun () ->
    if index >= m.Length then None
    else
      index <- index + 1
      Some(m[index-1])

let empty_stream() = fun () -> None

let input_stream() = fun () ->
  let input = Console.ReadLine()
  if input="" then None else Some(input)

let coinduction base_case gen_next =  
  let mutable current = base_case
  fun () ->
    let previous = current;
    current <- gen_next current  // generates the next value
    Some(previous)

let factorial(n) =
  coinduction (0,1) (fun (n,nf) -> (n+1, (n+1)*nf))
    |> map (fun (x,y) -> y)
    |> nth n |> Option.get

let limited_coinduction base_case has_next gen_next =
  let mutable current = base_case
  fun () ->
    if not(has_next current) then None
    else 
      let previous = current
      current <- gen_next current
      Some(previous)

let n_factorial(n) =
  limited_coinduction (0,1) (fun (_,n) -> n>0) (fun (n,nf) -> (n+1,(n+1)*nf))
  |> map (fun (_,y) -> y)
  |> nth n

let vector_stream<'T> (m:Vec<'T>) =  // stream a vector as opposed to list
  let mutable i = 0
  fun () ->
    i <- i+1
    if i <= m.Count then Some(m[i-1]) else None

let vector_coinduction<'T> (seeds:Vec<'T>) gen_next =
  let mutable index = 0
  fun () ->
    if index < seeds.Count then
      index <- index + 1
      Some(seeds[index-1])
    else
      index <- index + 1 
      let next = gen_next seeds 
      seeds.Add(next)
      Some(next)

let limited_vec_coinduction<'T> (seeds:Vec<'T>) gen_next =
  let mutable index = 0
  fun () ->
    if index < seeds.Count then
      index <- index + 1
      Some(seeds[index-1])
    else
      index <- index + 1 
      let next = gen_next seeds
      next |> oiter (fun x -> seeds.Add(x))
      next

let seeded_coinduction<'T> (m:'T list) gen =  // use list to initialize vector
  let vec = Vec<'T>()
  for x in m do vec.Add(x)
  vector_coinduction vec gen

let limited_seeded_coinduction<'T> (m:'T list) gen =
  let vec = Vec<'T>()
  for x in m do vec.Add(x)
  limited_vec_coinduction vec gen

let next_prime (known_primes:Vec<int>) =
  if known_primes.Count < 2 then
    Some(known_primes.Count + 2)  //returns 2 or 3
  else
    let last_prime = known_primes.[known_primes.Count - 1]
    let candidates = limited_coinduction (last_prime+2) (fun c->c>0) (fun c -> c+2)
    candidates
      |> find_first(fun candidate ->
            vector_stream known_primes
              |> take_while(fun p -> float(p)<=1.0+Math.Sqrt(float(candidate)))
              |> for_all(fun p -> candidate % p <> 0))

let primes() = limited_seeded_coinduction [] next_prime

// Previously completed stream helpers needed for question 8.
let until (predicate: 'T -> bool) (stream: Stream<'T>) : Stream<'T> =
    let mutable finished = false 
    fun () -> 
      if finished then 
        None 
      else 
        match stream() with 
        | None -> 
          finished <- true 
          None 
        | Some(x) -> 
          if predicate x then 
            finished <- true 
          Some(x)

let find_last (predicate: 'T -> bool) (stream: Stream<'T>) : 'T option =
    let mutable last = None 
    let mutable next = stream()
    while is_some next do 
      match next with 
      | Some(x) -> 
        if predicate x then 
            last <- Some(x)
      | None -> () 

      next <- stream() 
    last

let get_last (stream: Stream<'T>) : 'T option =
    find_last (fun x -> true) stream

// Provided in the updated assignment: option-to-stream helpers.
let singleton_stream x = finite_stream [x]

let opt_to_stream = function
    | None -> empty_stream()
    | Some(x) -> finite_stream [x]

// =====================================================================
// YOUR PRACTICE QUESTIONS
// =====================================================================

// Stream exercise 6b: prime factorization (optional challenge)
(*
   The prime factors of both 10 and 20 are 2 and 5. However, for 20
   it takes 2*2*5 - it may take multiple occurrences of a prime.
   Create a stream that represents the prime factorization of a number
   that includes such multiple occurrences.

   Hint from the document: write a recursive function to create streams.
   Use append and bind on streams. Also use opt_to_stream, defined above.
*)
// TODO: Return a stream of prime factors, including repeated occurrences.
// Practice function name chosen here: primefactorization.
// The examples below use positive integers.
let rec primefactorization (n: int) : Stream<int> =
    if n = 1 then // stop when all prime factors have been divided out
        empty_stream() // no factors left to return
    else // find a factor of the remaining number
        let factor = // save the first factor as an option
            primes() // create a stream of primes to check
            |> find_first (fun x -> n % x = 0) // find the first prime dividing n evenly
        factor
        |> opt_to_stream // turn Some factor into a stream containing that factor
        |> bind (fun x -> // use the factor x to create a stream of factors
            append // join the current factor with the remaining factors
                (singleton_stream x) // a stream containing just x
                (primefactorization (n/x))) // recursively factorize what remains


primefactorization 10 |> foreach (printf "%d ")
printfn ""
// Expected: 2 5

primefactorization 20 |> foreach (printf "%d ")
printfn ""
// Expected: 2 2 5

primefactorization 12 |> foreach (printf "%d ")
printfn ""
// Expected: 2 2 3

primefactorization 13 |> foreach (printf "%d ")
printfn ""
// Expected: 13

primefactorization 1 |> foreach (printf "%d ")
printfn ""
// Expected: blank line (empty stream)

// Stream exercise 8: power using coinduction (challenge)
(*
   The following function computes m to the nth power in log(n) steps
   by binary factorization on n:

   let power m n multiplier identity =
       let rec inner ax factor n =
           if n > 0 then
               let newfactor = multiplier factor factor
               if n%2 = 1 then
                   inner (multiplier ax factor) newfactor (n/2)
               else
                   inner ax newfactor (n/2)
           else
               ax
       inner identity m n

   power 2 8 (*) 1 returns 256 in the recursive version above.

   Rewrite the function using coinduction (you will need until and get_last).
   Hint from the document: first write an inner function next that takes
   the tuple (ax,factor,n) to the next (ax,factor,n) based on n%2.

   Source typo corrected above: "identify" should be "identity".
*)
// TODO: Implement the coinduction version. The provided Fib example expects
// an option result, so this starter uses 'T option as the return type.
// Practice tests below use nonnegative exponents.
let power (m: 'T) (n: int) (multiplier: 'T -> 'T -> 'T) (identity: 'T) : 'T option =
    let next (ax, factor, remaining) = // update the result, current factor and exponent
        let newax = // calculate the next accumulated result
            if remaining % 2 = 1 then multiplier ax factor // include this factor if the exponent is odd
            else ax // keep the result unchanged if the exponent is even

        (newax, multiplier factor factor, remaining / 2) // square the factor and halve the exponent

    coinduction (identity, m, n) next // start with the identity, base and exponent; generate states
    |> until (fun (_, _, remaining) -> remaining = 0) // include the final state with exponent zero
    |> get_last // get that final state as an option
    |> Option.map (fun (ax, _, _) -> ax) // extract the accumulated result from the tuple

// printfn "2^8: %A" (power 2 8 (*) 1)
// Expected: Some 256

// printfn "3^5: %A" (power 3 5 (*) 1)
// Expected: Some 243

// printfn "7^0: %A" (power 7 0 (*) 1)
// Expected: Some 1

// printfn "7^1: %A" (power 7 1 (*) 1)
// Expected: Some 7

// Provided challenge support: matrix multiplication and Fibonacci example.
// These definitions come from the assignment; you do not need to rewrite them.
type M2x2 = (int64 * int64 * int64 * int64)

let mmult (A: M2x2) (B: M2x2) =
    let ((a, b, c, d), (q, r, s, t)) = (A, B)
    (a*q+b*s, a*r+b*t,
     c*q+d*s, c*r+d*t)

let IDM = (1L, 0L,
           0L, 1L)

let FIBM = (1L, 1L,
            1L, 0L)

let Fib n =
    match power FIBM (n-1) mmult IDM with
    | Some(a,_,_,_) when a > 0L -> Some(a)
    | _ -> None

// printfn "Fib 1: %A" (Fib 1)  // Expected: Some 1L
// printfn "Fib 2: %A" (Fib 2)  // Expected: Some 1L
// printfn "Fib 10: %A" (Fib 10) // Expected: Some 55L

// TODO: Add your own tests as you finish each challenge.


