// What Kind of Mutations are Safe? (packet section)
// Based on Chuck Liang's CSC123 Rust transition guide.
// Compile in the VS Code terminal: rustc --edition=2021 17_evaluation_order_and_safe_mutation.rs
// Run on Windows PowerShell: .\17_evaluation_order_and_safe_mutation.exe
// Run on Linux/macOS: ./17_evaluation_order_and_safe_mutation
//
// Church-Rosser says that two reductions from the same lambda term can be joined.
// If a normal form exists, it is unique. Shared mutable state can make the final
// observable value depend on the order of evaluation.
//
// Trace the packet's lambda7b example starting with x = 2:
//     define f = lambda y: (x = x*0; y;);
//     define g = lambda y: (x = x+1; y;);
//     g(f(1));
//     x;
// Call-by-value evaluates f(1) before entering g. Call-by-name delays f(1)
// until g needs y. The two Rust traces below model those orders explicitly.
//
// The packet also rewrites "let x = v in E" as "(lambda x. E) v". An inner let
// can bind a fresh x using the old x + 1. Reusing storage gives the same result
// if nobody will need the old value again. A loop can similarly reuse a frame
// when a tail call has no further work to do. Rust does not guarantee tail-call
// optimization. A loop makes that reuse explicit.
//
// Predict the two final values of x, then predict what move does in the last example.

fn zero(x: &mut i32) {
    *x *= 0;
}

fn increment(x: &mut i32) {
    *x += 1;
}

fn main() {
    let mut by_value = 2;
    zero(&mut by_value);
    increment(&mut by_value);
    println!("Call-by-value trace: {by_value}");

    let mut by_name = 2;
    increment(&mut by_name);
    zero(&mut by_name);
    println!("Call-by-name trace: {by_name}");
    assert_eq!((by_value, by_name), (1, 0));

    // Try these four lines together. Both closures would hold &mut x.
    // let mut x = 2;
    // let mut f = |y: i32| { x *= 0; y };
    // let mut g = |_y: i32| { x += 1; x };
    // println!("{}", g(f(1)));

    let mut x = 2;
    let mut f = move || {
        x *= 0;
        x
    };
    let mut g = move || {
        x += 1;
        x
    };
    println!("Separate captures: f = {}, g = {}, outer x = {}", f(), g(), x);
    assert_eq!(x, 2);
}

// Pause here. Why can both move closures run? Which copy of x does each update?
