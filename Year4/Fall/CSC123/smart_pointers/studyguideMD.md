# Smart pointers study guide

The 13 numbered sections match the 13 C++ files and our topic overview. The professor's packet supplies the material; corrections appear where relevant. Ask: who owns the target, who observes it, and what operation destroys it?

## 1. Raw pointer review and memory errors

**Run:** [01_raw_pointers_and_memory_errors.cpp](01_raw_pointers_and_memory_errors.cpp)

### 1. Raw pointers and memory errors

A raw pointer holds an address. It may point to a local object or to heap storage. Copying the pointer copies the address; it does not copy the object. With manual allocation, one designated owner must delete each allocation exactly once, after its last use. Losing the only owning address leaks memory.

**Check yourself:** Why would assigning heap = &local before delete heap cause two different problems?

## 2. unique_ptr and make_unique

**Run:** [02_unique_ptr_and_make_unique.cpp](02_unique_ptr_and_make_unique.cpp)

### 1. unique_ptr and make_unique

A unique_ptr is an object that manages a pointer. make_unique creates the heap object and returns its owner. Use * to access a value, -> to access an object's members, and a boolean check to test for a target. Ordinary copying is disabled because it would create competing owners.

**Check yourself:** Why is auto second = number rejected, while int copy = *number works?

### 2. Smart pointers to arrays

make_unique<int>(3) creates one integer with value 3. make_unique<int[]>(3) creates three value-initialized integers (all zero). unique_ptr<T[]> uses delete[] automatically. It does not remember the array length or check indices; keep the length separately or use vector.

**Check yourself:** What are the initial contents of make_unique<int[]>(4)?

## 3. Lifetime and ownership

**Run:** [03_lifetime_and_ownership.cpp](03_lifetime_and_ownership.cpp)

### 1. Lifetime and automatic cleanup

An owner object and its target are separate objects. Destroying a unique_ptr deletes the object it still owns. Scope exit and reset can trigger cleanup. reset() deletes the current target and leaves the owner empty. A destructor message lets you see exactly when cleanup happens.

**Check yourself:** When does target 2 disappear below: at reset or at the closing brace?

## 4. Moving and transferring ownership

**Run:** [04_moving_and_transferring_ownership.cpp](04_moving_and_transferring_ownership.cpp)

### 1. Moving ownership

Move construction initializes a new owner. Move assignment replaces an existing owner's target, cleaning up its old target first. After a transfer between distinct unique_ptr objects, the source is empty but remains a live, reusable object. The heap object itself stays at the same address.

**Check yourself:** After b = move(a), which old object is destroyed, and which owner is empty?

### 2. Functions: borrow or take ownership

A parameter of type unique_ptr<T> receives ownership by value. Passing a named owner requires move. A T& or const T& parameter can borrow the target without transferring ownership. Return an owner by value to hand ownership to the caller; return a local owner normally, without adding move.

**Check yourself:** Which call leaves the caller's pointer empty: inspect(*p), increment(*p), or consume(move(p))?

## 5. Smart pointers inside structs

**Run:** [05_smart_pointers_inside_structs.cpp](05_smart_pointers_inside_structs.cpp)

### 1. Smart pointer members and the Rule of Zero

A class whose members manage their own resources usually needs no custom destructor, copy constructor, copy assignment, move constructor, or move assignment. This is the Rule of Zero. With a unique_ptr member, default copying is unavailable but default moving can work. Scalar members are copied during a default move; they do not automatically become zero.

**Check yourself:** Why can a moved-from Buffer have empty cells but a size of 3?

## 6. RAII

**Run:** [06_raii.cpp](06_raii.cpp)

### 1. RAII and raw observers

RAII ties resource cleanup to an owning object's destruction, including stack unwinding after an exception. Prefer make_unique for normal allocation. get() returns a non-owning raw pointer and DOES NOT release ownership. release() does relinquish ownership without deleting, so avoid it unless responsibility is explicitly passed elsewhere.

**Check yourself:** Why must you never call delete on the result of owner.get() while owner still owns it?

## 7. References and borrowing

**Run:** [07_references_and_borrowing.cpp](07_references_and_borrowing.cpp)

### 1. Borrowing the owner versus borrowing the target

unique_ptr<int>& aliases the owner object. int& bound to *owner aliases the heap integer. Moving ownership empties the source owner but does not move the integer, so a reference to the integer can remain valid while the new owner keeps it alive. Neither reference extends its referent's lifetime.

**Check yourself:** After the move below, why is value_ref usable while *owner_ref is invalid?

### 2. Reseatable borrowing

An ordinary reference stays bound to the same object. reference_wrapper holds a non-owning reference-like handle that can be reassigned. Its get() returns a reference. The professor's borrow class illustrates the same basic idea with a private raw pointer. Neither wrapper keeps the target alive.

**Check yourself:** What does r = b change: the old integer a, or which integer r observes?

### 3. Traversing owned structures

A vector can hold unique_ptr elements. Iterate by reference to avoid copying owners. A linked list can also use unique_ptr links; a non-owning pointer can traverse it without transferring ownership. Recursion with reference parameters is another approach, but C++ does not guarantee tail-call optimization.

**Check yourself:** Why would for (auto p : values) fail when values holds unique_ptr objects?

## 8. Remaining memory hazards

**Run:** [08_remaining_memory_hazards.cpp](08_remaining_memory_hazards.cpp)

### 1. Mutation and remaining hazards

Smart pointers automate deletion; they do not prevent every invalid access or ownership cycle. Appending to a vector during a range-for invalidates the cached end iterator, and reallocation can invalidate all iterators/references. Read the original data in a separate stage. Do not move a list's root owner into one of its own descendants.

**Check yourself:** Why is reserving capacity alone insufficient to make the commented range-for safe?

## 9. shared_ptr and make_shared

**Run:** [09_shared_ptr_and_make_shared.cpp](09_shared_ptr_and_make_shared.cpp)

### 1. Shared ownership and reference counts

shared_ptr lets several owners keep one object alive. Copying adds an owner; destroying or resetting an owner removes one. The last strong owner destroys the object. A reference parameter does not add an owner. Moving transfers a handle; its effect on counts depends on what the destination owned before.

**Check yourself:** What are the counts after p1 = other, p2 = p3, and p2 = move(p3)?

## 10. weak_ptr

**Run:** [10_weak_ptr.cpp](10_weak_ptr.cpp)

### 1. Weak pointers and ownership cycles

weak_ptr observes a shared ownership group without adding a strong owner. lock() returns a shared_ptr if the object is still alive, or an empty shared_ptr otherwise; always check it. Strong ownership cycles can keep counts above zero forever. Use a weak link where the relationship should not keep an object alive.

**Check yourself:** Why does the previous link below not prevent cleanup?

## 11. Custom move operations and rvalue references

**Run:** [11_custom_moves_and_rvalue_references.cpp](11_custom_moves_and_rvalue_references.cpp)

### 1. References and what move actually does

An lvalue identifies an object; a named variable expression is an lvalue even when its declared type is T&&. An rvalue reference can bind to a temporary or to an xvalue produced by move. std::move is a cast that enables move operations; the receiving constructor or assignment performs the transfer. It does not transfer anything merely by binding a reference.

**Check yourself:** Why does binding candidate = move(owner) below leave owner nonempty?

### 2. Custom move constructors and assignment

Sometimes a moved-from object must preserve a relationship between members, such as empty storage implying size zero. Define move operations to maintain that relationship. A move constructor creates a new object; move assignment updates an existing one. Return *this by lvalue reference from assignment. Rule of Five means consider all five special operations; they may be defaulted or deleted.

**Check yourself:** Which operation runs for Buffer b(move(a)), and which runs for c = move(b)?

## 12. Rules of Three, Five, and Zero

**Run:** [12_rules_of_three_five_and_zero.cpp](12_rules_of_three_five_and_zero.cpp)

### 1. Rules of Three, Five, and Zero

The Rule of Three concerns a destructor, copy constructor, and copy assignment when a class directly owns resources. The Rule of Five adds move construction and move assignment to that design decision. Default or delete operations as appropriate. The Rule of Zero means letting resource-managing members handle those operations for you. vector<int> gives value copying; unique_ptr gives exclusive ownership and moving. A virtual base destructor is needed when deleting derived objects through that base.

**Check yourself:** Why is copying ValueBuffer safe while copying OwnerBuffer is disabled?

## 13. Building a custom smart pointer

**Run:** [13_building_a_custom_smart_pointer.cpp](13_building_a_custom_smart_pointer.cpp)

### 1. Inside a teaching smart pointer

This small managed pointer follows the professor's idea: private raw pointer, private adoption constructor, factory friend, destructor, disabled copies, move operations, and a runtime lock. It handles single objects of the same type only. The lock is an educational policy, not thread synchronization or a general memory-safety guarantee. Unlike the packet example, this version checks both source and destination before move assignment.

**Check yourself:** Why must a rejected move leave both pointers unchanged?

### 2. Packet corrections and a final ownership trace

Use the packet for its learning sequence, with these corrections: get() retains ownership; moved-from unique_ptr objects remain alive and reusable; move itself is a cast; unique_ptr can transfer into shared_ptr; four shared handles mean count four. Raw observers can coexist with one unique owner. The packet's assignment operators should conventionally return the destination as T&. Generic moved-from objects are not all guaranteed empty.

**Check yourself:** Trace every owner and strong count below before running it.

## Reference checks for packet corrections

- [C++ working draft: unique_ptr observers](https://eel.is/c++draft/unique.ptr.single.observers): get() returns the stored pointer; it does not release it.
- [C++ working draft: unique_ptr assignment](https://eel.is/c++draft/unique.ptr.single.asgn): moving between distinct owners empties the source and returns the destination by reference.
- [C++ working draft: shared_ptr constructors](https://eel.is/c++draft/util.smartptr.shared.const): construction from a compatible unique_ptr transfers ownership.
- [C++ working draft: move and forward](https://eel.is/c++draft/forward): these helpers cast; constructors and assignment operators implement resource transfers.

Additional distinctions: a reference does not keep its referent alive; const unique_ptr<T>& does not make T const; use const T& for read-only access to the target. A base class needs a virtual destructor when objects will be deleted polymorphically through that base. make_unique is a useful default, but constructing a unique_ptr from a legitimately transferred raw allocation can also be valid RAII. A teaching lock is unrelated to weak_ptr::lock(), and neither provides general thread synchronization.
