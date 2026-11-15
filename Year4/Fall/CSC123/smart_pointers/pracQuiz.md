# Smart pointers prediction questions

Answer these after studying the matching numbered lesson. Explain who owns the data, not just the printed number. Answers are in [quizAns.md](quizAns.md).

## 1. Raw pointers and memory errors

Why would assigning heap = &local before delete heap cause two different problems?

## 2. unique_ptr and make_unique

Why is auto second = number rejected, while int copy = *number works?

## 3. Smart pointers to arrays

What are the initial contents of make_unique<int[]>(4)?

## 4. Lifetime and automatic cleanup

When does target 2 disappear below: at reset or at the closing brace?

## 5. Moving ownership

After b = move(a), which old object is destroyed, and which owner is empty?

## 6. Functions: borrow or take ownership

Which call leaves the caller's pointer empty: inspect(*p), increment(*p), or consume(move(p))?

## 7. Smart pointer members and the Rule of Zero

Why can a moved-from Buffer have empty cells but a size of 3?

## 8. RAII and raw observers

Why must you never call delete on the result of owner.get() while owner still owns it?

## 9. Borrowing the owner versus borrowing the target

After the move below, why is value_ref usable while *owner_ref is invalid?

## 10. Reseatable borrowing

What does r = b change: the old integer a, or which integer r observes?

## 11. Traversing owned structures

Why would for (auto p : values) fail when values holds unique_ptr objects?

## 12. Mutation and remaining hazards

Why is reserving capacity alone insufficient to make the commented range-for safe?

## 13. Shared ownership and reference counts

What are the counts after p1 = other, p2 = p3, and p2 = move(p3)?

## 14. Weak pointers and ownership cycles

Why does the previous link below not prevent cleanup?

## 15. References and what move actually does

Why does binding candidate = move(owner) below leave owner nonempty?

## 16. Custom move constructors and assignment

Which operation runs for Buffer b(move(a)), and which runs for c = move(b)?

## 17. Inside a teaching smart pointer

Why must a rejected move leave both pointers unchanged?

## 18. Packet corrections and a final ownership trace

Trace every owner and strong count below before running it.
