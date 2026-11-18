// Returning references and lifetime annotations
// Based on Chuck Liang's CSC123 Rust transition guide.
// Compile in the VS Code terminal: rustc --edition=2021 07_lifetimes.rs
// Run on Windows PowerShell: .\07_lifetimes.exe
// Run on Linux/macOS: ./07_lifetimes
// Predict: Replace the body of first with the second argument. What lifetime would its type and the return type need?

fn first<'a>(left: &'a str, _right: &str) -> &'a str {
    left // The return value borrows from left.
}

fn longer<'a>(left: &'a str, right: &'a str) -> &'a str {
    if left.len() >= right.len() {
        left
    } else {
        right
    }
}

// fn dangling() -> &'static str {
//     let local = String::from("temporary");
//     &local // Try: the owner is dropped when the function returns.
// }

fn main() {
    let outside = String::from("outside");
    let selected;
    {
        let inside = String::from("inside");
        selected = first(&outside, &inside);
        println!("Longer: {}", longer(&outside, &inside));
    }
    assert_eq!(selected, "outside");
}
