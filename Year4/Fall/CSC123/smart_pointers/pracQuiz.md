# Smart pointers prediction questions

13 topic sections, matching the C++ files. Explain ownership and lifetime as well as output. Check [quizAns.md](quizAns.md) after trying each topic.

## 1. Raw pointer review and memory errors

1. Why would assigning heap = &local before delete heap cause two different problems?

## 2. unique_ptr and make_unique

1. Why is auto second = number rejected, while int copy = *number works?
2. What are the initial contents of make_unique<int[]>(4)?

## 3. Lifetime and ownership

1. When does target 2 disappear below: at reset or at the closing brace?

## 4. Moving and transferring ownership

1. After b = move(a), which old object is destroyed, and which owner is empty?
2. Which call leaves the caller's pointer empty: inspect(*p), increment(*p), or consume(move(p))?

## 5. Smart pointers inside structs

1. Why can a moved-from Buffer have empty cells but a size of 3?

## 6. RAII

1. Why must you never call delete on the result of owner.get() while owner still owns it?

## 7. References and borrowing

1. After the move below, why is value_ref usable while *owner_ref is invalid?
2. What does r = b change: the old integer a, or which integer r observes?
3. Why would for (auto p : values) fail when values holds unique_ptr objects?

## 8. Remaining memory hazards

1. Why is reserving capacity alone insufficient to make the commented range-for safe?

## 9. shared_ptr and make_shared

1. What are the counts after p1 = other, p2 = p3, and p2 = move(p3)?

## 10. weak_ptr

1. Why does the previous link below not prevent cleanup?

## 11. Custom move operations and rvalue references

1. Why does binding candidate = move(owner) below leave owner nonempty?
2. Which operation runs for Buffer b(move(a)), and which runs for c = move(b)?

## 12. Rules of Three, Five, and Zero

1. Why is copying ValueBuffer safe while copying OwnerBuffer is disabled?

## 13. Building a custom smart pointer

1. Why must a rejected move leave both pointers unchanged?
2. Trace every owner and strong count below before running it.
