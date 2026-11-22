// Box and recursive nodes
// Compile in the VS Code terminal: rustc --edition=2021 11_box_and_linked_nodes.rs
// Run on Windows PowerShell: .\11_box_and_linked_nodes.exe
//
// Box<T> uniquely owns a T on the heap, like C++ unique_ptr<T>. Box::new plays
// the role of make_unique. A node containing another Node directly would need
// infinite space. Option<Box<Node>> has a fixed size and None marks the end.
// Watch which step moves the tail and which steps only borrow its nodes.
//
// Predict: What does next.as_deref() let the loop read while head still owns the list?

struct Node {
    value: i32,
    next: Option<Box<Node>>,
}

fn read_node(node: &Node) -> i32 {
    node.value
}

fn main() {
    let tail = Box::new(Node { value: 2, next: None });
    println!("Tail: {}", read_node(&tail)); // &Box<Node> coerces to &Node.
    // Separate experiment: insert these two lines together before constructing head.
    // Compare the packet's C++ p->next = move(p): the node can wind up owning
    // itself with no outside owner left to free it. Box ownership alone forms a
    // tree in safe Rust. Lesson 16 shows what changes with shared ownership.
    // let mut p = Box::new(Node { value: 3, next: None });
    // p.next = Some(p); // RHS moves p. Writing its next field then needs p again.
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

// Pause here. Why can a loop read every node while head continues to own the list?
