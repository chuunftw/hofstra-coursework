// Shared borrows, mutable borrows, and function parameters
// Compile in the VS Code terminal: rustc --edition=2021 03_borrowing_and_functions.rs
// Run on Windows PowerShell: .\03_borrowing_and_functions.exe
//
// Read each function's parameter before reading its body. A String parameter takes
// ownership. A shared &str lets a function read text. An &mut String also lets it
// change the caller's string. Returning an owned String transfers it to the caller.
// In the last example, compare which variable you can print after each call.
//
// Predict: Replace length(&text) with consume(text) before add_mark. Which line fails?

fn length(text: &str) -> usize { //takes an input named text, text is of type reference str then returns type usize
    text.len()
}

fn add_mark(text: &mut String) {
    text.push('!');
}

fn consume(text: String) -> usize {
    text.len()
}

fn append_owned(mut text: String) -> String {
    text.push('!');
    text
}

fn append_borrowed(text: &str) -> String {
    let mut result = text.to_owned();
    result.push('!');
    result
}

fn main() {
    let mut text = String::from("hello");
    assert_eq!(length(&text), 5); // Borrow the text as "&text", text is a string
    add_mark(&mut text); // Mutate through an exclusive borrow.
    println!("{text}");
    assert_eq!(consume(text), 6); // Transfer ownership into consume.
    // println!("{text}"); // Try: text has moved.

    let source = String::from("rust");
    let owned = append_owned(source);
    let another = append_borrowed(&owned);
    println!("Returned owner: {owned}, new string: {another}");
}

// Pause here. Which call lets its caller keep using the original String binding afterward?
