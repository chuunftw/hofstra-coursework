# Smart pointers answers

## 1. Raw pointer review and memory errors

1. Reassigning heap loses the only address of its original allocation (leak). Deleting the reassigned pointer then attempts to delete a local object (invalid deallocation).

## 2. unique_ptr and make_unique

1. second would copy the unique_ptr owner, which is disabled. *number accesses the integer, whose value is copyable.
2. Four zero-initialized integers. By contrast, make_unique<int>(4) creates one integer containing 4.

## 3. Lifetime and ownership

1. At reset(). The owner remains alive but empty until scope exit.

## 4. Moving and transferring ownership

1. Object 2, formerly owned by b, is destroyed. b takes object 1 and a becomes empty.
2. consume(move(p)) empties p. The other two calls borrow its integer.

## 5. Smart pointers inside structs

1. The compiler moves the unique_ptr member but copies the int member. A default move does not enforce size == 0 for the source.

## 6. RAII

1. get() returns an observer. Deleting through it leaves owner responsible for an already-destroyed object, causing invalid access or double deletion later.

## 7. References and borrowing

1. value_ref refers to the heap integer that destination still owns. owner_ref refers to the now-empty source owner; dereferencing that empty smart pointer is invalid.
2. It changes which integer the wrapper observes. a remains 2; the later increment changes b from 5 to 6.
3. A by-value loop tries to copy each owner. const auto& borrows each owner instead. A raw observer for list traversal likewise does not create another owner.

## 8. Remaining memory hazards

1. push_back invalidates the previous end iterator even without reallocation. Range-for caches that end. Iterating over a snapshot avoids modifying the iterated container.

## 9. shared_ptr and make_shared

1. origin's count starts at 4. It becomes 3, stays 3, then becomes 2. Moving into a new empty handle instead would preserve the count.

## 10. weak_ptr

1. previous is weak and adds no strong owner. When external owners disappear, first and then its owned next node can be destroyed. lock() temporarily adds ownership only when it succeeds.

## 11. Custom move operations and rvalue references

1. move(owner) is a cast, and candidate is only a reference to owner. Initializing destination by value from move(candidate) invokes a move constructor.
2. b uses the move constructor; c uses move assignment. The custom operations also zero the source size and assignment returns the destination.

## 12. Rules of Three, Five, and Zero

1. ValueBuffer delegates to vector, whose copying makes independent element storage. OwnerBuffer delegates to unique_ptr, which disables copying and transfers ownership on a move. Neither class has to implement resource cleanup itself. The virtual base destructor ensures the derived destructor runs when deleted through Base.

## 13. Building a custom smart pointer

1. The checks run before deletion or transfer. A rejected operation throws while both original ownership relationships are intact. The lock is just this teaching class's runtime policy.
2. a owns 10, then b owns 10; observer only observes. Conversion to shared transfers ownership and leaves b empty. Strong count: 1, then 2 with copy, then 3 with locked, then 1 at scope exit. reset deletes 10 and weak expires. a is reusable and later owns 99.
