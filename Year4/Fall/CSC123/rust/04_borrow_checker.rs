// Borrow conflicts and last use
// Based on Chuck Liang's CSC123 Rust transition guide.
// Compile in the VS Code terminal: rustc --edition=2021 04_borrow_checker.rs
// Run on Windows PowerShell: .\04_borrow_checker.exe
// Run on Linux/macOS: ./04_borrow_checker
//
// Shared references can coexist. A mutable borrow requires exclusive access to
// the part being borrowed. Trace from each borrow to its last use in this code.
// A vector can move its elements to a new allocation when it grows. C++ can leave
// an element reference dangling here. Safe Rust checks the overlap at compile time.
// This illustrates the packet's "zero overhead" point: checking this rule
// requires no runtime tracking of element references. push implicitly borrows
// the vector mutably. Creating a fresh borrow after push is safe.
//
// Predict: Uncomment the last print. Which shared borrow now overlaps the push, and how could you fix it?

fn main() {
    let mut numbers = vec![10, 20, 30];
    let first = &numbers[0];
    let second = &numbers[1];
    println!("{first} and {second}"); // Final use of both shared borrows.
    numbers.push(40); // push needs a mutable borrow and may reallocate.
    assert_eq!(numbers.len(), 4);
    println!("Fresh borrow after push: {}", &numbers[0]);
    // println!("{first}"); // Try: makes first stay live across push.
}

// Pause here. If you move the final print above push, which borrow ends before the vector grows?
