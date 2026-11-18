// Macros and field-level mutation
// Based on Chuck Liang's CSC123 Rust transition guide.
// Compile in the VS Code terminal: rustc --edition=2021 13_macros_and_field_access.rs
// Run on Windows PowerShell: .\13_macros_and_field_access.exe
// Run on Linux/macOS: ./13_macros_and_field_access
// Predict: Replace the macro call with set_day(&mut date, 19). Why does the year borrow conflict?

struct Date {
    year: u16,
    day: u8,
}

macro_rules! set_day {
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
