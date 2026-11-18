// Borrow conflicts and last use
// Based on Chuck Liang's CSC123 Rust transition guide.
// Compile in the VS Code terminal: rustc --edition=2021 04_borrow_checker.rs
// Run on Windows PowerShell: .\04_borrow_checker.exe
// Run on Linux/macOS: ./04_borrow_checker
// Predict: Uncomment the last print. Which shared borrow now overlaps the push, and how could you fix it?

fn main() {
    let mut numbers = vec![10, 20, 30];
    let first = &numbers[0];
    let second = &numbers[1];
    println!("{first} and {second}"); // Final use of both shared borrows.
    numbers.push(40); // push needs a mutable borrow and may reallocate.
    assert_eq!(numbers.len(), 4);
    // println!("{first}"); // Try: makes first stay live across push.
}
