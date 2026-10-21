// Premade functions needed by the answers and tests.
open System

type Vec<'T> = ResizeArray<'T>
type Stream<'T> = unit -> Option<'T>

let omap = Option.map

let obind = Option.bind

let oiter = Option.iter

let is_some = Option.isSome

let get_or = Option.defaultValue

let limit n stream =
  let mutable counter = 0
  fun () ->
    if counter >= n then None
    else
      counter <- counter + 1
      stream()

let map mapfun stream =
  fun () -> stream() |> omap mapfun

let filter predicate stream =
  let rec inner next =
    match next with
      | Some(x) when (predicate x) -> next
      | Some(x) -> inner (stream())
      | None -> None
  fun () -> inner (stream())

let take_while predicate stream =
  fun () -> stream()
            |> obind (fun x -> if predicate(x) then Some(x) else None)

let foreach action stream =
  let rec inner next =
    match next with
      | Some x ->
        action x
        inner (stream())
      | None -> ()
  inner (stream())

let for_all predicate stream =
  let mutable answer = true
  let mutable next = stream()
  while answer && (is_some next) do
    if not(next |> omap predicate |> get_or true) then answer <- false
    else next <- stream()
  answer

let find_first predicate stream =
  let rec inner next =
    match next with
      | Some(x) when (predicate x) -> next
      | Some(x) -> inner (stream())
      | None -> next
  inner (stream())

let finite_stream<'T> (m:'T list) =
  let mutable index = 0
  fun () ->
    if index >= m.Length then None
    else
      index <- index + 1
      Some(m[index-1])

let coinduction base_case gen_next =
  let mutable current = base_case
  fun () ->
    let previous = current;
    current <- gen_next current
    Some(previous)

let limited_coinduction base_case has_next gen_next =
  let mutable current = base_case
  fun () ->
    if not(has_next current) then None
    else
      let previous = current
      current <- gen_next current
      Some(previous)

let vector_stream<'T> (m:Vec<'T>) =
  let mutable i = 0
  fun () ->
    i <- i+1
    if i <= m.Count then Some(m[i-1]) else None

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

let limited_seeded_coinduction<'T> (m:'T list) gen =
  let vec = Vec<'T>()
  for x in m do vec.Add(x)
  limited_vec_coinduction vec gen

let next_prime (known_primes:Vec<int>) =
  if known_primes.Count < 2 then
    Some(known_primes.Count + 2)
  else
    let last_prime = known_primes.[known_primes.Count - 1]
    let candidates = limited_coinduction (last_prime+2) (fun c->c>0) (fun c -> c+2)
    candidates
      |> find_first(fun candidate ->
            vector_stream known_primes
              |> take_while(fun p -> float(p)<=1.0+Math.Sqrt(float(candidate)))
              |> for_all(fun p -> candidate % p <> 0))

let primes() = limited_seeded_coinduction [] next_prime

// Questions and answers

(*
   1. The first exercise just asks you to practice creating a mutable
      closure.  A "toggle" is a function that alternates between returning
      true and false.  Write a function maketoggle() that has the following
      behavior:

*)
let maketoggle () : (unit -> bool) =
    let mutable value = true
    fun () ->
      let result = value
      value <- not value
      result

printfn "\n--- Mutable closure question 1: maketoggle ---"
let toggle1 = maketoggle()
let toggle2 = maketoggle()
printfn "%A" (toggle1())   // prints true
printfn "%A" (toggle1())   // prints false
printfn "%A" (toggle1())   // prints true
printfn "%A" (toggle2())   // prints true

(*
   1. until predicate stream   (let until predicate stream = ... )

    This operation is similar to take_while but will INCLUDE the
    first value for which the predicate returns true.  For example,

    primes() |> until (fun p -> p > 10) should stop at 11, the first
    prime greater than 10.  Notice that

    primes() |> take_while (fun p -> p<=10) will stop at 7

    So until is not just the inverse of take_while.
*)
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

printfn "\n--- Stream question 1: until ---"
printfn "Primes through the first value above 10:"
primes() |> until (fun p -> p > 10) |> foreach (printfn "%d")
// Expected: 2,3,5,7,11
printfn "Match on the first value:"
finite_stream [2;4;6] |> until (fun x -> x = 2) |> foreach (printfn "%d") // 2
printfn "No matching value:"
finite_stream [1;2] |> until (fun x -> x > 10) |> foreach (printfn "%d") // 1,2
printfn "Empty stream:"
let empty_until = finite_stream ([]: int list) |> until (fun x -> x > 0)
printfn "%A" (empty_until()) // None

(*
   2. skip n stream

      This operation should take a stream and skip the first n values,
      returning the modified stream.  Be sure to call stream() |> ignore
      to ignore values returned by the stream
*)
let skip (n: int) (stream: Stream<'T>) : Stream<'T> =
    for i in 1 .. n do // 1 through n inclusive
      stream() |> ignore
    stream

printfn "\n--- Stream question 2: skip ---"
printfn "Skip 2 values:"
finite_stream [10;20;30;40] |> skip 2 |> foreach (printfn "%d")
// Expected: 30,40
printfn "Skip 0 values:"
finite_stream [10;20] |> skip 0 |> foreach (printfn "%d") // 10,20
printfn "Skip past the end:"
let skipped = finite_stream [10;20] |> skip 5
printfn "%A" (skipped()) // None

(*
   3. find_last predicate stream

      This operation works like find_first but returns the last value
      for which the predicate holds.  This function should return Some(value)
      or None.
*)
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

printfn "\n--- Stream question 3: find_last ---"
printfn "Last even value:"
finite_stream [1;2;3;4] |> find_last (fun x -> x % 2 = 0) |> printfn "%A"
// Expected: Some 4
printfn "No matching value:"
finite_stream [1;3] |> find_last (fun x -> x % 2 = 0) |> printfn "%A"
// Expected: None
printfn "Empty stream:"
finite_stream ([]: int list) |> find_last (fun x -> x % 2 = 0) |> printfn "%A" // None

(*
   4. get_last stream
      This operation should return the last value generated by a stream.
      This should be easy given find_last.  Think of what predicate to
      pass to find_last.  Note that since the entire stream may be empty,
      this function must still return an option.
*)
let get_last (stream: Stream<'T>) : 'T option =
    stream |> find_last (fun x -> true)

printfn "\n--- Stream question 4: get_last ---"
printfn "Last value of [10;20;30]:"
finite_stream [10;20;30] |> get_last |> printfn "%A" // Some 30
printfn "Empty stream:"
finite_stream ([]: int list) |> get_last |> printfn "%A" // None

(*
   5.  Use coinduction to define all powers of two: 1 2 4 8 16 32 64 128 ...
*)
let powers_of_two () : Stream<int> =
    coinduction 1 (fun x -> x * 2)

printfn "\n--- Stream question 5: powers of two ---"
printfn "First 8 powers of two:"
powers_of_two() |> limit 8 |> foreach (printfn "%d")
// Expected: 1,2,4,8,16,32,64,128

(*
   6.  Using the stream of primes, write a procedure that prints all
       prime factors of a number n.  (a prime factor of n is a prime p
       such that n%p==0).  Use a combination of take_while, filter,
       etc...

       For example:  primefactors 10001 should print 73 and 137
*)
let primefactors (n: int) : unit =
    primes()
    |> take_while (fun p -> p <= n)
    |> filter (fun p -> n % p = 0)
    |> foreach (printfn "%d")

printfn "\n--- Stream question 6: primefactors ---"
printfn "Prime factors of 10001:"
primefactors 10001 // 73,137

(*
   7. The binary factors of a number, such as 45, can be computed with
      the following sequence of pairs

      (1,45) -> (2,22) -> (4,11) -> (8,5) -> (16,2) -> (32,1)

      The binary factors are extracted from those pairs (factor,m)
      where m is odd.  Thus the binary factors of 45 are 1+4+8+32.
      Given n, we can define the sequence with

        coinduction (1,n) (fun (f,m) -> (f*2, m/2))

      Use this sequence to write a function that prints all the binary
      factors of n.  You will need a combination of take_while, filter
      and map.
*)
let binaryfactors (n: int) : unit =
    coinduction (1,n) (fun (f,m) -> (f*2, m/2))
    |> take_while (fun (f,m) -> m > 0)
    |> filter (fun (f,m) -> m % 2 = 1)
    |> map (fun (f,m) -> f)
    |> foreach (printfn "%d")

printfn "\n--- Stream question 7: binaryfactors ---"
printfn "Binary factors of 45:"
binaryfactors 45   // 1,4,8,32

