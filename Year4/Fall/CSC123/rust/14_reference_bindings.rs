// What can change in a reference binding?
// Based on Chuck Liang's CSC123 Rust transition guide.
// Compile in the VS Code terminal: rustc --edition=2021 14_reference_bindings.rs
// Run on Windows PowerShell: .\14_reference_bindings.exe
// Run on Linux/macOS: ./14_reference_bindings
//
// The two places you can write mut answer different questions. In "let mut r = &x",
// you can reassign r. In "let r = &mut x", you can write through r with *r.
// A shared reference is Copy. A mutable reference can be reborrowed temporarily.
// Moving the mutable reference into a new binding transfers exclusive access.
// Safe references always point to live data. They cannot be null or do pointer arithmetic.
//
// Predict which of the two integers changes after each write through r.

fn main() {
    let mut x = 1;
    let mut y = 10;

    let r1 = &x;
    // The pattern "let ref r1 = x" also borrows x. "ref mut" borrows mutably.
    let mut r2 = r1;
    println!("Both read x: {r1}, {r2}");
    r2 = &y;
    println!("Reassigned shared reference: {r2}");

    let r3 = &mut x;
    *r3 += 1;
    let mut r4 = r3;
    // println!("{}", *r3); // Try: r3 moved into r4.
    println!("Through r4 before reassignment: {r4}");
    r4 = &mut y;
    *r4 += 1;
    println!("After both writes: x = {x}, y = {y}");

    let mut original = String::from("abcd");
    let mut view = &original;
    println!("Before move: {view}");
    let mut owner = original;
    // println!("{view}"); // Try: keeps the original borrow live across the move.
    view = &owner;
    println!("After borrowing again: {view}");
    // let taken = *view; // Try: cannot move a String out through a shared reference.
    original = "hello world".to_owned(); // A moved binding can be initialized again.
    let edit = &mut owner;
    *edit = String::from("aaabbb");
    // while owner.len() < 10 { edit.push('x'); } // Try: competing access to owner.
    while edit.len() < 10 {
        edit.push('x');
    }
    println!("Original binding: {original}, edited owner: {owner}");
}

// Pause here. Which mut lets you redirect a reference? Which lets you change its target?
