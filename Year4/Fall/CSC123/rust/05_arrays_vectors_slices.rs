// Arrays, vectors, and slices
// Based on Chuck Liang's CSC123 Rust transition guide.
// Compile in the VS Code terminal: rustc --edition=2021 05_arrays_vectors_slices.rs
// Run on Windows PowerShell: .\05_arrays_vectors_slices.exe
// Run on Linux/macOS: ./05_arrays_vectors_slices
// Predict: Change &array[1..3] to &array[1..2]. What does the first sum become?

fn sum(items: &[i32]) -> i32 {
    items.iter().sum()
}

fn main() {
    let mut array: [i32; 3] = [10, 20, 30];
    let copied = array; // A fixed-size array of Copy elements is Copy.
    array[1] = 40;

    let part: &[i32] = &array[1..3]; // Indices 1 and 2.
    assert_eq!(sum(part), 70);
    assert_eq!(sum(&copied), 60);

    let mut vector = vec![10, 20, 30];
    vector.push(40);
    println!("Array slice: {}; full vector: {}", sum(part), sum(&vector));
}
