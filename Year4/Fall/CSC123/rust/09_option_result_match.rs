// Option, Result, and pattern matching
// Compile in the VS Code terminal: rustc --edition=2021 09_option_result_match.rs
// Run on Windows PowerShell: .\09_option_result_match.exe
//
// Option<T> has two cases, Some(value) and None. Result<T, E> has Ok(value)
// and Err(error). Here an integer can be absent even after parsing succeeds.
// Read the return type from the outside in. The ? operator passes an Err back
// to the caller and gives the function the inner value on success.
//
// Predict: Trace the loop. Which input matches each arm? Change 21 to 0 and predict the output.

fn positive(text: &str) -> Result<Option<u32>, std::num::ParseIntError> {
    let value = text.parse::<u32>()?; // Return early on a parse error.
    if value > 0 {
        Ok(Some(value))
    } else {
        Ok(None)
    }
}

fn main() {
    for input in ["21", "0", "oops"] {
        match positive(input) {
            Ok(Some(value)) => println!("Positive: {value}"),
            Ok(None) => println!("Zero"),
            Err(error) => println!("Could not parse {input}: {error}"),
        }
    }
}

// Pause here. What exact value reaches match when parsing succeeds but the number is zero?
