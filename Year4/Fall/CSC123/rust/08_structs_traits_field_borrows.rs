// Structs, derived traits, and disjoint field borrows
// Based on Chuck Liang's CSC123 Rust transition guide.
// Compile in the VS Code terminal: rustc --edition=2021 08_structs_traits_field_borrows.rs
// Run on Windows PowerShell: .\08_structs_traits_field_borrows.exe
// Run on Linux/macOS: ./08_structs_traits_field_borrows
//
// A trait describes behavior a type supports. derive asks Rust to generate an
// implementation from the fields. Eq compares for equality, Ord orders dates by
// year, then month, then day. Hash lets a date serve as a hash key. Debug supplies
// {:?}. Display supplies {} through the formatting code you write.
// Follow exactly which field set_day receives while year is still borrowed.
// Rust also supports dynamic dispatch through trait objects (dyn Trait).
// To reuse data or behavior across structs, Rust uses composition and traits.
// Java-style class inheritance is a separate mechanism.
//
// Predict: Why does passing &mut date.year conflict with the borrow of year while passing &mut date.day works?

#[derive(Debug, Clone, Copy, PartialEq, Eq, PartialOrd, Ord, Hash)]
struct Date {
    year: u16,
    month: u8,
    day: u8,
}

impl std::fmt::Display for Date {
    fn fmt(&self, out: &mut std::fmt::Formatter<'_>) -> std::fmt::Result {
        write!(out, "{:04}-{:02}-{:02}", self.year, self.month, self.day)
    }
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
    println!("{date}");
}

// Pause here. Which pair of dates would make the order of the fields matter?
