(* F# Tutorial Exercises Addendum.

   Given the definition of Numbers:
*)

type Number =
    | Integer of int
    | Rational of int * int
    | Real of float
    | Complex of float * float

//def multiply 
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

// a. Define a function inverse that returns the inverse of the number as
// Some(inverse) if the inverse exists, or None if there's no inverse.
// Integer(0) and Rational(0,1), for example, have no inverse as the
// denominator cannot be zero. A Rational(a,b) has inverse Rational(b,a)
// if a is not zero.  A Real(r) has inverse Real(1.0/r) if r is not
// 0.0.  A complex number a+bi has an inverse if not both a and b are
// zeros, in which case the inverse is
// let d = a*a+b*b in Some(Complex(a/d, b/d));

//   I'll get you started:

let inverse num =
  match num with     // not equal
    | Integer(x) when (x<>0) -> Some(Rational(1,x))
    | Rational(a,b) when (a<>0) -> Some(Rational(b,a))
    | Real(x) when (x<>0.0) -> Some(Real(1.0/x))
    | Complex(a,b) when (a<>0.0) || (b<>0.0) -> 
        let d = a*a+b*b 
        Some(Complex(a/d , -b/d))
// Use a-bi b/c (a+bi)*(a-bi) = a*a+b*b.
// So the inverse is Complex(a/d, -b/d), where d = a*a+b*b, hence why its "-b/d"
    | _ -> None  // default case
printfn "inverse of 2 = %A" (inverse (Integer 2))

// b. Assuming you've written the multiply function from the previous exercise,
//    write a function divide that divides a by b by multiplying a with the
//    inverse of b, if it exists.  This function should also return an
//    Option<Number>, because the inverse may not exist (no divide by zero).

// Hint: try to write this function using Option.map.  If you can't do
// that, you can resort to pattern matching.

let simplify number =
    match number with
    | Rational(a,b) when b <> 0 && a % b = 0 ->
        Integer(a / b)
    | _ -> number
let divide x y =
    match inverse y with
    | Some value -> Some (simplify (multiply x value))
    | None -> None
    
printfn "6 / 2 = %A" (divide (Integer 6) (Integer 2))
