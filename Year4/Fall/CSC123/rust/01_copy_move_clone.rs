// Copy, move, and clone
// Based on Chuck Liang's CSC123 Rust transition guide.
// Compile in the VS Code terminal: rustc --edition=2021 01_copy_move_clone.rs
// Run on Windows PowerShell: .\01_copy_move_clone.exe
// Run on Linux/macOS: ./01_copy_move_clone
// Predict: What happens if you print original after the move?

fn main() {
    let x = 7;
    let y = x; // i32 implements Copy. Both bindings remain usable.
    println!("Copied integers: {x}, {y}");

    let original = String::from("rust");
    let mut owner = original; // Transfer ownership of the string.
    let duplicate = owner.clone(); // Make a separate String.
    owner.push('!');
    assert_eq!(duplicate, "rust");
    println!("Owner: {owner}, clone: {duplicate}");

    // println!("{original}"); // Try: use of a moved value.
}
