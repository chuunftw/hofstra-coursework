// Generic bounds and mutable slices
// Based on Chuck Liang's CSC123 Rust transition guide.
// Compile in the VS Code terminal: rustc --edition=2021 12_generics_and_bubble_sort.rs
// Run on Windows PowerShell: .\12_generics_and_bubble_sort.exe
// Run on Linux/macOS: ./12_generics_and_bubble_sort
//
// T: Ord promises comparison. The compiler checks the generic body with that
// promise and generates code for the concrete types used. String supports Ord
// and owns its bytes. Moving one out of a borrowed slice would leave a hole.
// swap exchanges two elements in one operation while keeping the slice initialized.
//
// Predict: Why can the function sort both integers and strings? What does swap borrow?

fn bubble_sort<T: Ord>(values: &mut [T]) {
    for end in (1..values.len()).rev() {
        for left in 0..end {
            let right = left + 1;
            if values[left] > values[right] {
                // swap borrows the slice once and works for non-Copy items.
                // let temp = values[left]; // Try: T: Ord does not imply T: Copy.
                values.swap(left, right);
            }
        }
    }
}

fn main() {
    let mut numbers = [4, 1, 3, 2];
    bubble_sort(&mut numbers);
    assert_eq!(numbers, [1, 2, 3, 4]);

    let mut words = [String::from("zebra"), String::from("ant")];
    bubble_sort(&mut words);
    assert_eq!(words[0], "ant");
    println!("{numbers:?} {words:?}");
}

// Pause here. Would adding T: Copy allow this function to sort the array of owned strings?
