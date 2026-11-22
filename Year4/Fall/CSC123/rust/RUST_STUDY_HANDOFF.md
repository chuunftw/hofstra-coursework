# CSC123 Rust study handoff

## Resume in file 10

Files **01–05** are covered. We just started [10 — Closures and capture](10_closures_and_capture.rs). We covered that `|| x` creates a closure with no arguments, that it captures `x` from its surrounding scope, and that `read_x()` calls it.

```rust
let x = 1;
let read_x = || x;
```

**Pending check:** What would `read_x()` return right here?

After the check, trace the inner block's `let x = 2` and ask which `x` the closure sees. Then use the `snapshot` example to show why `move` lets the closure keep its own copy of an integer. These are the file 10 examples to focus on for page 8.

## What we covered

| File | Study checkpoint |
| --- | --- |
| [01 — Copy, move, clone](01_copy_move_clone.rs) | Explained why `i32` stays usable after copying, why a moved `String` binding can't be read, and why `.clone()` gives a separate string. Predicted `"rust!"` and `"rust"` correctly. |
| [02 — Scope and drop](02_scope_and_drop.rs) | Traced cleanup at the inner closing brace, at `drop(early)`, and at the end of `main`. The custom `Drop` exercise is extra. |
| [03 — Borrowing and functions](03_borrowing_and_functions.rs) | Worked through reading with `&str`, changing a caller's string through `&mut String`, taking ownership with `String`, and returning a `String` to the caller. |
| [04 — Borrow checker](04_borrow_checker.rs) | Picked the fresh borrow after `Vec::push` in the quiz. A reference used after the push would stay live through the push, which needs exclusive access. The vector's buffer may move as it grows. |
| [05 — Arrays, vectors, slices](05_arrays_vectors_slices.rs) | Predicted the copied array, read the correct values from `&array[1..3]`, and explained why `sum` can take a borrowed array with five elements. |

## Remaining files in order

1. [10 — Closures and capture](10_closures_and_capture.rs). Finish the examples above.
2. [11 — Box and linked nodes](11_box_and_linked_nodes.rs). Focus on `Box` ownership and deref coercion. The self-link and linked-list traversal can wait.
3. [14 — Reference bindings](14_reference_bindings.rs). Compare `let mut r = &x` with `let r = &mut x`. The longer `String` exercise can wait.
4. [16 — Rc, Weak, RefCell](16_rc_weak_refcell.rs). Cover shared ownership, why strong cycles can leak, why back-links can be weak, and what `RefCell` lets you do.
5. [17 — Evaluation order and safe mutation](17_evaluation_order_and_safe_mutation.rs). Cover call-by-value versus call-by-name, the `lambda7b` example, and why separate `move` captures avoid conflicting borrows.

Work through one short code excerpt at a time. Give one prediction question at a time. If Ryan says to move on, continue from the next example.
