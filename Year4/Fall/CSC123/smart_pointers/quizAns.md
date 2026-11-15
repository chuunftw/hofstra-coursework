# Smart pointers answers

## 1. Raw pointers and memory errors

Reassigning heap loses the only address of its original allocation (leak). Deleting the reassigned pointer then attempts to delete a local object (invalid deallocation).

## 2. unique_ptr and make_unique

second would copy the unique_ptr owner, which is disabled. *number accesses the integer, whose value is copyable.

## 3. Smart pointers to arrays

Four zero-initialized integers. By contrast, make_unique<int>(4) creates one integer containing 4.

## 4. Lifetime and automatic cleanup

At reset(). The owner remains alive but empty until scope exit.

## 5. Moving ownership

Object 2, formerly owned by b, is destroyed. b takes object 1 and a becomes empty.

## 6. Functions: borrow or take ownership

consume(move(p)) empties p. The other two calls borrow its integer.

## 7. Smart pointer members and the Rule of Zero

The compiler moves the unique_ptr member but copies the int member. A default move does not enforce size == 0 for the source.

## 8. RAII and raw observers

get() returns an observer. Deleting through it leaves owner responsible for an already-destroyed object, causing invalid access or double deletion later.

## 9. Borrowing the owner versus borrowing the target

value_ref refers to the heap integer that destination still owns. owner_ref refers to the now-empty source owner; dereferencing that empty smart pointer is invalid.

## 10. Reseatable borrowing

It changes which integer the wrapper observes. a remains 2; the later increment changes b from 5 to 6.

## 11. Traversing owned structures

A by-value loop tries to copy each owner. const auto& borrows each owner instead. A raw observer for list traversal likewise does not create another owner.

## 12. Mutation and remaining hazards

push_back invalidates the previous end iterator even without reallocation. Range-for caches that end. Iterating over a snapshot avoids modifying the iterated container.

## 13. Shared ownership and reference counts

origin's count starts at 4. It becomes 3, stays 3, then becomes 2. Moving into a new empty handle instead would preserve the count.

## 14. Weak pointers and ownership cycles

previous is weak and adds no strong owner. When external owners disappear, first and then its owned next node can be destroyed. lock() temporarily adds ownership only when it succeeds.

## 15. References and what move actually does

move(owner) is a cast, and candidate is only a reference to owner. Initializing destination by value from move(candidate) invokes a move constructor.

## 16. Custom move constructors and assignment

b uses the move constructor; c uses move assignment. The custom operations also zero the source size and assignment returns the destination.

## 17. Inside a teaching smart pointer

The checks run before deletion or transfer. A rejected operation throws while both original ownership relationships are intact. The lock is just this teaching class's runtime policy.

## 18. Packet corrections and a final ownership trace

a owns 10, then b owns 10; observer only observes. Conversion to shared transfers ownership and leaves b empty. Strong count: 1, then 2 with copy, then 3 with locked, then 1 at scope exit. reset deletes 10 and weak expires. a is reusable and later owns 99.
