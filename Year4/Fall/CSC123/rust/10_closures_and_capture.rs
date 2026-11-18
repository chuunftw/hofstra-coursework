// Closures, lexical scope, and move capture
// Based on Chuck Liang's CSC123 Rust transition guide.
// Compile in the VS Code terminal: rustc --edition=2021 10_closures_and_capture.rs
// Run on Windows PowerShell: .\10_closures_and_capture.exe
// Run on Linux/macOS: ./10_closures_and_capture
// Predict: Remove move from snapshot. Why does reassignment of score now conflict with its capture?

fn main() {
    let label = String::from("rust");
    let length = || label.len(); // Capture a shared borrow.
    assert_eq!(length(), 4);
    println!("Label is still usable: {label}");

    let mut score = 10;
    let snapshot = move || score; // Capture a copy because i32 is Copy.
    score = 20;
    assert_eq!(snapshot(), 10);
    println!("Current score: {score}");

    let message = String::from("owned by the closure");
    let print_message = move || println!("{message}");
    print_message();
    // println!("{message}"); // Try: String was moved into the closure.
}
