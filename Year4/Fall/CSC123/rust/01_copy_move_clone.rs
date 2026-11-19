// Copy, move, and clone
// Based on Chuck Liang's CSC123 Rust transition guide.
// Compile in the VS Code terminal: rustc --edition=2021 01_copy_move_clone.rs
// Run on Windows PowerShell: .\01_copy_move_clone.exe
// Run on Linux/macOS: ./01_copy_move_clone
//
// For each lesson, read the opening comments, predict the result, then run main.
// Pause at the question at the bottom. Try one commented experiment at a time.
//
// An owner is responsible for a value. Read "let y = x" by asking what type x has.
// An i32 implements Copy, so y gets its own integer. A String owns a heap buffer.
// Moving the String transfers that responsibility. Cloning a String copies its bytes,
// so the cost grows with its length. Borrow when you only need to read the text.
// Rust fixes what Copy and move mean. Clone can have type-specific behavior.
// In C++, assigning a std::vector can copy its elements. Rust's Vec moves on assignment.
// C++'s "rule of zero" means relying on members to handle copying, moving and
// cleanup. In Rust, a type can customize Clone but Copy always duplicates bits.
// Heap location alone doesn't decide this: an &str can be copied even when its
// bytes belong to a heap allocation. The reference owns none of those bytes.
//
// Predict: What happens if you print original after the move?

fn main() {
    // let introduces a binding. mut permits reassignment. Rust infers i32 here.
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

// Pause here. After the run, which binding owns the original buffer? Which owns a second buffer?
