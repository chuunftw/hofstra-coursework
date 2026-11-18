// Box and recursive nodes
// Based on Chuck Liang's CSC123 Rust transition guide.
// Compile in the VS Code terminal: rustc --edition=2021 11_box_and_linked_nodes.rs
// Run on Windows PowerShell: .\11_box_and_linked_nodes.exe
// Run on Linux/macOS: ./11_box_and_linked_nodes
// Predict: What does next.as_deref() let the loop read while head still owns the list?

struct Node {
    value: i32,
    next: Option<Box<Node>>,
}

fn main() {
    let tail = Box::new(Node { value: 2, next: None });
    let head = Node {
        value: 1,
        next: Some(tail), // Move ownership of the boxed node into head.
    };

    // Each step borrows a node. The loop never takes ownership of a Box.
    let mut current = Some(&head);
    let mut total = 0;
    while let Some(node) = current {
        println!("{}", node.value);
        total += node.value;
        current = node.next.as_deref(); // Option<&Node>
    }
    assert_eq!(total, 3);
} // Dropping head also drops the Box it owns.
