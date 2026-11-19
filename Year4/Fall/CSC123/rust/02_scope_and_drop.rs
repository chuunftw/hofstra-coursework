// Scope and automatic cleanup
// Based on Chuck Liang's CSC123 Rust transition guide.
// Compile in the VS Code terminal: rustc --edition=2021 02_scope_and_drop.rs
// Run on Windows PowerShell: .\02_scope_and_drop.exe
// Run on Linux/macOS: ./02_scope_and_drop
//
// A block introduces a scope. Follow the value named "inner" across the move.
// When its final owner leaves the block, Rust runs its destructor (Drop).
// This is how owned resources get cleaned up without a tracing garbage collector.
// The drop function lets you choose an earlier cleanup point by taking ownership.
// Each file here is a standalone Rust program with a main function. Larger
// projects commonly use Cargo to build crates. The packet's #![allow(...)]
// attribute silences named warnings for a crate. Borrow errors still stop a build.
//
// Predict: Which cleanup message appears first? Move early into drop() and trace the remaining owners.

struct Tracked(&'static str);

impl Drop for Tracked {
    fn drop(&mut self) {
        println!("Cleaning up {}", self.0);
    }
}

fn main() {
    let early = Tracked("early");
    let outer = Tracked("outer");
    {
        let inner = Tracked("inner");
        let moved = inner;
        println!("Inside: {}", moved.0);
    } // moved owns the inner value at this point.
    drop(early); // Give ownership to drop for immediate cleanup.
    println!("Still alive: {}", outer.0);
}

// Pause here. Why is there only one cleanup message for the value moved from inner?
