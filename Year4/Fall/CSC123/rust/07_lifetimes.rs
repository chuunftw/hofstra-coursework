// Returning references and lifetime annotations
// Compile in the VS Code terminal: rustc --edition=2021 07_lifetimes.rs
// Run on Windows PowerShell: .\07_lifetimes.exe
//
// A returned reference needs an owner that will still be alive when you use it.
// Lifetime annotations describe relationships the compiler checks. Rust can infer
// many of them. With two borrowed inputs, the signature must say which inputs
// can supply the output. Trace first and longer with the inner block in main.
//
// Predict: Replace the body of first with the second argument. What lifetime would its type and the return type need?

fn first<'a>(left: &'a str, _right: &str) -> &'a str {
    left // The return value borrows from left.
}

fn longer<'a>(left: &'a str, right: &'a str) -> &'a str {
    if left.len() >= right.len() {
        left
    } else {
        right
    }
}

// fn dangling() -> &'static str {
//     let local = String::from("temporary");
//     &local // Try: the owner is dropped when the function returns.
// }

// Packet quiz: try each signature separately. Which owner would the result borrow?
// fn d(x: i32) -> &i32 { &x }           // Missing output lifetime.
// fn d(x: i32) -> &'static i32 { &x }   // x is dropped on return.

fn literal() -> &'static str {
    "the bytes of this literal live for the whole program"
}

// 'long: 'short means 'long lasts at least as long as 'short.
// Either input can therefore supply a reference valid for 'short.
fn smaller<'short, 'long: 'short>(x: &'long i32, y: &'short i32) -> &'short i32 {
    if x < y { x } else { y }
}

fn main() {
    println!("{}", literal());
    let outer_number = 10;
    {
        let inner_number = 5;
        println!("Smaller: {}", smaller(&outer_number, &inner_number));
    }
    let outside = String::from("outside");
    let selected;
    {
        let inside = String::from("inside");
        selected = first(&outside, &inside);
        println!("Longer: {}", longer(&outside, &inside));
    }
    assert_eq!(selected, "outside");
}

// Pause here. Could you use longer's result after inside is dropped? What about first's result?
