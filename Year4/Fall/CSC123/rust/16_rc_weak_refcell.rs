// Who owns a node when two links point to it?
// Based on Chuck Liang's CSC123 Rust transition guide.
// Compile in the VS Code terminal: rustc --edition=2021 16_rc_weak_refcell.rs
// Run on Windows PowerShell: .\16_rc_weak_refcell.exe
// Run on Linux/macOS: ./16_rc_weak_refcell
//
// Rc<T> shares ownership on one thread. Rc::clone increments the strong count in
// constant time. The value is dropped when its last strong owner goes away.
// Weak<T> can observe the allocation. upgrade() returns Some(owner) while the
// value lives and None afterward. In C++, shared_ptr and weak_ptr play these roles.
//
// In a doubly linked list, a strong next link and a weak previous link let the
// nodes be released. Two strong links in opposite directions could keep both counts
// above zero after the external owners disappear. Rust has no tracing collector to
// find and reclaim such a cycle. Observer relationships can use the same weak backlink.
//
// RefCell<T> allows a change through a shared reference. Its borrow checks happen
// at runtime. Predict what happens to the parent's strong count when the back link
// is created, and what the surviving child sees after the parent is dropped.

use std::cell::RefCell;
use std::rc::{Rc, Weak};

#[derive(Default)]
struct Node {
    next: RefCell<Option<Rc<Node>>>,
    previous: RefCell<Weak<Node>>,
}

fn main() {
    let parent = Rc::new(Node::default());
    let child = Rc::new(Node::default());
    *parent.next.borrow_mut() = Some(Rc::clone(&child));
    *child.previous.borrow_mut() = Rc::downgrade(&parent);

    println!("Strong owners: parent {}, child {}", Rc::strong_count(&parent),
             Rc::strong_count(&child));
    assert!(child.previous.borrow().upgrade().is_some());

    {
        let reader = parent.next.borrow();
        println!("Parent has a next node: {}", reader.is_some());
        assert!(parent.next.try_borrow_mut().is_err());
        // let writer = parent.next.borrow_mut(); // Try: runtime panic while reader lives.
    }

    drop(parent);
    println!("Child can reach parent: {}", child.previous.borrow().upgrade().is_some());
    assert!(child.previous.borrow().upgrade().is_none());
    assert_eq!(Rc::strong_count(&child), 1);
}

// Pause here. If previous owned an Rc and both external owners went away,
// which two links would keep the strong counts above zero?
