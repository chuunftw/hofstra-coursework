// Structs, derived traits, and disjoint field borrows
// Based on Chuck Liang's CSC123 Rust transition guide.
// Compile in the VS Code terminal: rustc --edition=2021 08_structs_traits_field_borrows.rs
// Run on Windows PowerShell: .\08_structs_traits_field_borrows.exe
// Run on Linux/macOS: ./08_structs_traits_field_borrows
// Predict: Why does passing &mut date.year conflict with the borrow of year while passing &mut date.day works?

#[derive(Debug, Clone, Copy, PartialEq, Eq, PartialOrd, Ord)]
struct Date {
    year: u16,
    month: u8,
    day: u8,
}

fn set_day(day: &mut u8, new_day: u8) {
    *day = new_day;
}

fn main() {
    let mut date = Date { year: 2026, month: 11, day: 18 };
    let earlier = date; // The derived Copy trait allows this copy.
    let year = &date.year;
    set_day(&mut date.day, 19); // Only the day field is borrowed mutably.
    println!("Year: {year}");
    assert!(earlier < date); // Derived Ord compares fields in declaration order.
    println!("{date:?}");
}
