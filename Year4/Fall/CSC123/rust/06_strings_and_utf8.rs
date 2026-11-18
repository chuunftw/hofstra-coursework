// String, &str, and UTF-8
// Based on Chuck Liang's CSC123 Rust transition guide.
// Compile in the VS Code terminal: rustc --edition=2021 06_strings_and_utf8.rs
// Run on Windows PowerShell: .\06_strings_and_utf8.exe
// Run on Linux/macOS: ./06_strings_and_utf8
// Predict: Try &text[0..1] with the accented character. Why can this panic?

use std::str::from_utf8;

fn main() {
    let mut text = String::from("éclair");
    let first_letter: &str = &text[..2]; // é occupies two UTF-8 bytes.
    assert_eq!(first_letter, "é");
    assert_eq!(text.len(), 7); // Bytes.
    assert_eq!(text.chars().count(), 6); // Unicode scalar values.
    text.push('!');

    let bytes = [82, 117, 115, 116];
    assert_eq!(from_utf8(&bytes), Ok("Rust"));
    println!("{text}");
    // println!("{}", &text[..1]); // Try: this splits a UTF-8 character.
}
