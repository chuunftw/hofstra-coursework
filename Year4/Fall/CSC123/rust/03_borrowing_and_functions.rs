// Shared borrows, mutable borrows, and function parameters
// Based on Chuck Liang's CSC123 Rust transition guide.
// Compile in the VS Code terminal: rustc --edition=2021 03_borrowing_and_functions.rs
// Run on Windows PowerShell: .\03_borrowing_and_functions.exe
// Run on Linux/macOS: ./03_borrowing_and_functions
// Predict: Replace length(&text) with consume(text) before add_mark. Which line fails?

fn length(text: &str) -> usize {
    text.len()
}

fn add_mark(text: &mut String) {
    text.push('!');
}

fn consume(text: String) -> usize {
    text.len()
}

fn main() {
    let mut text = String::from("hello");
    assert_eq!(length(&text), 5); // Borrow through a string slice.
    add_mark(&mut text); // Mutate through an exclusive borrow.
    println!("{text}");
    assert_eq!(consume(text), 6); // Transfer ownership into consume.
    // println!("{text}"); // Try: text has moved.
}
