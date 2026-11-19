// Why does reversing an assignment change whether it compiles?
// Based on Chuck Liang's CSC123 Rust transition guide.
// Compile in the VS Code terminal: rustc --edition=2021 15_indexing_and_mutable_borrows.rs
// Run on Windows PowerShell: .\15_indexing_and_mutable_borrows.exe
// Run on Linux/macOS: ./15_indexing_and_mutable_borrows
//
// Indexing hides borrows. On the right, v[i] reads an element. On the left,
// indexing a Vec to write an element needs a mutable borrow. In this example
// the assignment evaluates the right side first. Trace the uses of v on each side.
//
// Predict the contents of v after each assignment. Then try the commented line.

fn main() {
    let mut v = vec![1, 2, 3, 4, 5];
    v[0] = v[v.len() - 1]; // The reads finish before the write.
    println!("Last copied to first: {v:?}");

    v[0] = 9; // Make the next write visible.
    // v[v.len() - 1] = v[0]; // Try: len() reads v during mutable indexing.
    let last_index = v.len() - 1;
    v[last_index] = v[0];
    println!("First copied to last: {v:?}");
    assert_eq!(v, [9, 2, 3, 4, 9]);
}

// Pause here. Which borrow disappears from the left side when you save last_index?
