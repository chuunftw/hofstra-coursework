// Scope and automatic cleanup
// Based on Chuck Liang's CSC123 Rust transition guide.
// Compile in the VS Code terminal: rustc --edition=2021 02_scope_and_drop.rs
// Run on Windows PowerShell: .\02_scope_and_drop.exe
// Run on Linux/macOS: ./02_scope_and_drop
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
