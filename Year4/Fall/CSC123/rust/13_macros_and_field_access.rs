// Macros and field-level mutation
// Compile in the VS Code terminal: rustc --edition=2021 13_macros_and_field_access.rs
// Run on Windows PowerShell: .\13_macros_and_field_access.exe
//
// The ! marks a macro invocation. macro_rules! matches Rust tokens and expands
// where you call it. Read the invocation as the assignment it expands into.
// A function taking &mut Date borrows the whole date even if its body changes
// only the day. Which fields does the expanded assignment actually touch?
//
// Predict: Replace the macro call with set_day(&mut date, 19). Why does the year borrow conflict?

struct Date {
    year: u16,
    day: u8,
}

macro_rules! set_day {
    // expr matches an expression. The packet's tt matches one token tree
    // (a single token such as 19, or a delimited group such as (18 + 1)).
    // Try changing the second expr to tt and calling with 18 + 1, then (18 + 1).
    ($date:expr, $day:expr) => {
        ($date).day = $day
    };
}

// Uncomment this function for the prediction exercise.
// fn set_day(date: &mut Date, day: u8) {
//     date.day = day;
// }

fn main() {
    let mut date = Date { year: 2026, day: 18 };
    let year = &date.year;
    set_day!(date, 19); // Expands to an assignment to the day field.
    println!("Year: {year}, day: {}", date.day);
    assert_eq!(date.day, 19);
}

// Pause here. Why can the year reference survive the macro call? Compare the function signature.
