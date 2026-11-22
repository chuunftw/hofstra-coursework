// String, &str, and UTF-8
// Compile in the VS Code terminal: rustc --edition=2021 06_strings_and_utf8.rs
// Run on Windows PowerShell: .\06_strings_and_utf8.exe
//
// A String owns UTF-8 bytes. An &str borrows a range of valid UTF-8 text.
// len() counts bytes. A character such as é spans two bytes, so slicing through
// its middle causes a runtime panic. from_utf8 checks a byte slice and returns
// Ok(text) or Err(error). The final match lets you see both paths.
//
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
    for sample in [&bytes[..], &[0xff][..]] {
        match from_utf8(sample) {
            Ok(word) => println!("Valid text: {word}"),
            Err(error) => println!("Invalid UTF-8: {error}"),
        }
        println!("With fallback: {}", from_utf8(sample).unwrap_or("unreadable"));
    }
    // println!("{}", &text[..1]); // Try: this splits a UTF-8 character.
}

// Pause here. Which experiment returns Err, and which experiment panics?
