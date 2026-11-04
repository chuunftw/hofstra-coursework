module MidtermStudyGuide

(*
Sample Solutions to Practice Problems on Midterm Study Guide

1. Explain what is meant by "covariance" and by "contravariance".  Under
   what circumstances is each principle valid?  Give an example of each.

   Covariance means that the codomain (return type) of a function can become
   more specific (smaller). Contravariance means the domain can become
   more general (larger).  The domain cannot become smaller and the codomain
   cannot become larger.  For example, a function of type string -> object
   can be replaced by a function of type object -> string but not vice versa.

2. What's the difference between the following two lines in Java. Will
   either compile and run?

    i. Object[] A = new String[10];
   ii. ArrayList<Object> B = new ArrayList<String>();


   The first line will compile but the second will not.  This is
   because arrays were allowed to be covariant in order to support
   polymorphism, which they shouldn't be, as it results in the
   following inconsistency:

     A[0] = "abc";
     A[1] = new Integer(2);

   This will compile but shouldn't.  The rules of type variance are
   properly observed with generics.


3. Explain the difference between the following functions:

   a. let f(x,y) = x+y
   b. let g x y = x+y

   Give an example of the functions behaving differently

   Function f is not Curried but the function g is.  One can call
   g 1, which returns a function expecting another argument but one
   can only call f with both arguments in a pair, as in f(2,3).


4. Determine if the following function is tail-recursive and if not,
   write a tail-recursive version

     let rec fib n = if (n<3) then 1 else fib(n-1) + fib(n-2)

   This function is not tail recursive.  The following one is:

     let fib n =
       let rec fibiter n a b =  // this is tail recursive
         if (n<3) then b else fib (n-1) b (a+b)
       fibter n 1 1  // body of outer function


5. Is the following function tail-recursive?

     let rec forall predicate m =
       match m with
         | [] -> true
	 | a::b -> (predicate a) && forall predicate b

   It is, even though the && appears to be the last operation.  But it isn't:
   the && is shortcircuited: the recursive call is only made if (predicate a)
   returns true.


6. Rewrite the following to use the Option monad instead of raising exceptions

     let safediv a b =
       if b<>0 then a/b else raise(Exception "div by zero")

     let safediv a b =
       if b<>0 then Some(a/b) else None

6b. Write a function 'howmany' that takes a list and a predicate, and
    returns how many values x in the list are such that predicate(x) evaluates
    to true.  The function must be tail-recursive

   let howmany m predicate =
     let rec iter m counter =  // this is tail-recursive
       match m with
         | [] -> counter
	 | a::b when (predicate a) -> iter b (counter+1)
	 | a::b -> iter b counter
     iter m 0

6c. Write a function 'find_first' that takes a predicate and returns as
    an Option the first value in the list that satisfy the predicate, if
    it exists.  The function must be tail-recursive.

    let rec find_first predicate m =
      match m with
        | [] -> None
	| a::b when (predicate a) -> Some(a)
	| a::b -> find_first predicate b

6d. Given
  open Option
  let a = Some 8
  let b = Some 4
  
  what is the value of
  b |> bind (fun y -> if y=0 then None else a |> map (fun x -> x/y))

  Some(2)

7. Determine the output of the following program and explain why:

     let x = 1
     let f y = x+y
     let g() =
       let x = 2
       printfn "f(1) is %d"  (f 1)

     F# will output 2 because it's statically scoped.
   
7b. Show how to emulate dynamic scoping in a programming language that
   only allows static scoping

   Requires mutation:

   let mutable x = 1
   let f y = x+y
   let g() =
     let savex = x
     x <- 2
     printfn "f(1) is %d"  (f 1)  // prints 3
     x <- savex

   Dynamic scoping is simulated by temporarily replacing the value of a global

8. Given

 type expr =
   | Num of int
   | Plus of expr*expr
   | Times of expr*expr
   | Divide of expr*expr
   | RuntimeError

Write a function 'eval' that evaluates an expr to an expr.  A
Num or RuntimeError should be evaluated to itself (normal form).
Division by zero should evaluate to a runtime error.  For example,
eval (Plus(Num 2, Times(Num 2, Num 3))) should return (Num 8).  and
eval (Divide(Num 2, Num 0)) should return RuntimeError.

let rec eval e =
  match e with
    | Num n -> e
    | RuntimeError -> e
    | Plus(a,b) ->
      match (eval a, eval b) with
        |(Num x, Num y) -> Num(x+y)
	| _ -> RuntimeError
    | Times(a,b) ->
      match (eval a, eval b) with
        |(Num x, Num y) -> Num(x*y)
	| _ -> RuntimeError      
    | Divide(a,b) ->
      match (eval a, eval b) with
        | (Num x, Num 0) -> RuntimeError
	| (Num x, Num y) -> Num(x/y)
        | _ -> RuntimeError

Alternatively, to be more efficient, the last clause can be written as

    | Divide(a,b) ->
      match (eval b) with
        | Num 0 -> RuntimeError
	| Num y ->
	  match (eval a) with
	    | Num x -> Num (x/y)
	    | ee -> ee
        | _ -> e	    

9. Determine the output of the following program:

     let make n =
       let mutable x = n
       fun y ->
         x <- x+y
	 x
	 
     let mutable a1 = make 0
     let mutable a2 = make 0
     a1 2  // 2
     a1 2  // 4
     a1 2  // 6
     a2 2  // 2


10. Concerning templates (generics), explain the differences between how
    they're implemented in C++ compared to Java.
     
    C++ templates are instantiated at compile time and carries zero
    runtime overhead. However, template code is not type-checked, which
    they are in Java.  Java uses "type erasure" to implement templates
    (generics).  For each generic class C<T>, java creates a non-generic
    class C where T is replaced by Object, or the closest supertype that
    T is declared to extend. (i.e, in class C<T extends Comparable<T>>,
    T will be replaced by Comparable.)


11. C++20 introduced "concepts", illustrated in

      template<typename T> requires std::totally_ordered<T>

    Explain whether the program will still compile if the "requires"
    clause is dropped.

    The requirement is checked against instantiations of T at compile time.
    But it will still compile: the joke is that "the requirement is optional."
    

12. Explain why advanced object oriented programming requires dynamic
    memory allocation.  Why is stack allocation not enough?

      Because the compiler doesn't know the exact type and
      therefore the size of the object.

12b.  Explain what is meant by "dynamic dispatch" and "dynamic typing"

      Dynamic typing means that the exact type of objects is only known
      at runtime and is carried by the objects.  Dynamic dispatch means
      when a function a.f() is invoked, the dynamic type of a is used to
      determine which version of f to call.
    

13. What's the difference between "overloading" and "overriding"?
    Give an example of each.

    Both concern resolving functions that share the same name.
    Overloading happens at compile time while overriding happens at
    runtime using dynamic dispatch.

    struct A {
      virtual int f() { return 1; }
    };
    struct B {
      int f() override { return 2; }
    };
    
    int g(A x) { return 1; }
    int g(B x) { return 2; }

    int main() {
      A* n = new B(); // static type A, dynamic type B
      int x = n.f();  // returns 2 because of overriding (dynamic dispatch)
      x = g(n);   // returns 1 because of overloading (static type used)
    }


14. Give an example of a "pure virtual function" in the context of
    the shapes example in C++.

    class shape {
      virtual double area() = 0;
    };  // one cannot create an instance of such a class

15. Explain if the following compiles in Java:

    interface I {
      Object f();
    }
    class A implements I {
      public String f() { return "abc"; }
    }

    Yes, it compiles because Java recognizes this kind of covariance.

15b. How about the following:

    class A<T> {
      T x;
      static T y;
    }

    No, this will not compile because of type erasure.  The type of y
    would be Object, and there would be no way to distinguish the y in
    A<String> with A<Integer>, for example.


16. (maybe on exam) Determine if the following C++ code contain any memory errors, and if so,
    what type of errors:

    int* px = new int(3);
    int* qx = new int(4);
    px = qx;
    delete px;
    delete qx;

    px = qx; causes a memory leak: the int(3) is still on the heap
    with no live pointer pointing to it.  There is also a double free
    at the end.  Both are runtime errors.

17. (maybe on exam) Explain what's meant by the "lifetime" of a value in memory.  When does
    lifetime end?

    The lifetime of a value is how long it's guaranteed to stay at the same
    location in memory.  Lifetime ends with mutation: either by being assigned
    to a different value or being popped from the stack or freed from the heap.
    It also ends following a "transfer of ownership" or "move".

18. Concerning streams in F# such as the following (infinite odd numbers):

    let mutable x = 1
    let oddstream = fun () ->
      x <- x+2
      Some(x-2)
      
    Show how to define a stream modifier `limit` that would limit the
    stream to a certain number, i.e oddstream |> limit 10, should limit
    the stream to the first 10 odds.

    let limit n stream =
      let mutable cx = 0
      fun () ->
        cx <- cx+1
	if cx<=n then stream()
	else None
	
18b. Show how to define a stream modifier take_while that would return
     values that satisfy a predicate, and None otherwise.
     
   let take_while predicate stream =
     fun () ->
       match (stream()) with
         | Some(x) when (predicate x) -> Some(x)
	 | _ -> None

   alternatively,

   let take_while predicate stream =
     fun () ->
       let next = stream()
       if (next |> Option.map predicate |> Option.DefaultValue false)
         then next
       else None

18c. (harder) Show how to define a stream modifier `filter` that takes
     a predicate and modifies a stream to only return values that satisfy
     the predicate.

   let filter predicate stream =
     let rec inner next =
       match next with
         | Some(x) when (predicate x) -> next
	 | Some(x) -> inner (stream())
	 | None -> None
     fun () -> inner (stream())


19.  Explain why in (Gnu) C the K combinator cannot be defined as follows:

    typedef int (*intfun)(int);
    intfun K(int x) {
       int inner(int y) { return x; }
       return inner;
    }

    Because the local variable x will get popped off the stack and will
    no longer be valid inside the inner function.

*)
