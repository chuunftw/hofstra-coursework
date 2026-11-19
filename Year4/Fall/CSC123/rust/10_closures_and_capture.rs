// Closures, lexical scope, and move capture
// Based on Chuck Liang's CSC123 Rust transition guide.
// Compile in the VS Code terminal: rustc --edition=2021 10_closures_and_capture.rs
// Run on Windows PowerShell: .\10_closures_and_capture.exe
// Run on Linux/macOS: ./10_closures_and_capture
//
// A closure can use a variable from its surrounding scope. Identify each capture,
// then ask whether the closure borrows it or owns it. With move, an integer
// is copied into the closure and an owned String moves into it. The code also
// tests lexical scope: a name refers to the binding visible where the closure
// was defined, even if a different binding has the same name when you call it.
//
// Predict: Remove move from snapshot. Why does reassignment of score now conflict with its capture?

fn main() {
    let x = 1;
    let read_x = || x;
    {
        let x = 2;
        println!("Inner x: {x}, captured x: {}", read_x());
    }

    let label = String::from("rust");
    let length = || label.len(); // Capture a shared borrow.
    assert_eq!(length(), 4);
    println!("Label is still usable: {label}");

    let mut score = 10;
    let snapshot = move || score; // Capture a copy because i32 is Copy.
    score = 20;
    // In the packet's F# example a closure reads a mutable variable after a
    // temporary change. Here the move closure captured 10. Without move, its
    // later call would keep a borrow live across the assignment above.
    println!("Captured score: {}", snapshot());
    assert_eq!(snapshot(), 10);
    println!("Current score: {score}");

    let message = String::from("owned by the closure");
    let print_message = move || println!("{message}");
    print_message();
    // println!("{message}"); // Try: String was moved into the closure.
}

// Pause here. If you remove move from snapshot, which later use keeps score borrowed?
