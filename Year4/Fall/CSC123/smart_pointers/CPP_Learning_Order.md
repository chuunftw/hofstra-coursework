# Smart pointers learning order

This follows the numbered, standalone lesson format in the neighboring [memory folder](../memory/CPP_Learning_Order.md). It is based on the professor's **Critical Notes on Memory Management in Modern C++**, with corrections explained in the lessons.

Start with one topic. Read the corresponding [study guide](studyguideMD.md) section and the code comments, predict the labeled output, then compile and run. Each file has its own main(). Incorrect examples stay commented out. Assertions check the ownership/value facts while you experiment; an assertion failure means a stated expectation no longer holds.

| Section | File | Topic |
| --- | --- | --- |
| 1 | [01_raw_pointer_review.cpp](01_raw_pointer_review.cpp) | Raw pointers and memory errors |
| 2 | [02_unique_ptr_basics.cpp](02_unique_ptr_basics.cpp) | unique_ptr and make_unique |
| 3 | [03_unique_arrays.cpp](03_unique_arrays.cpp) | Smart pointers to arrays |
| 4 | [04_lifetimes_and_cleanup.cpp](04_lifetimes_and_cleanup.cpp) | Lifetime and automatic cleanup |
| 5 | [05_move_ownership.cpp](05_move_ownership.cpp) | Moving ownership |
| 6 | [06_function_parameters_and_returns.cpp](06_function_parameters_and_returns.cpp) | Functions: borrow or take ownership |
| 7 | [07_structs_and_rule_of_zero.cpp](07_structs_and_rule_of_zero.cpp) | Smart pointer members and the Rule of Zero |
| 8 | [08_raii_and_raw_observers.cpp](08_raii_and_raw_observers.cpp) | RAII and raw observers |
| 9 | [09_references_and_borrowing.cpp](09_references_and_borrowing.cpp) | Borrowing the owner versus borrowing the target |
| 10 | [10_reference_wrappers.cpp](10_reference_wrappers.cpp) | Reseatable borrowing |
| 11 | [11_vectors_and_linked_lists.cpp](11_vectors_and_linked_lists.cpp) | Traversing owned structures |
| 12 | [12_mutation_and_remaining_hazards.cpp](12_mutation_and_remaining_hazards.cpp) | Mutation and remaining hazards |
| 13 | [13_shared_ptr_and_counts.cpp](13_shared_ptr_and_counts.cpp) | Shared ownership and reference counts |
| 14 | [14_weak_ptr_and_cycles.cpp](14_weak_ptr_and_cycles.cpp) | Weak pointers and ownership cycles |
| 15 | [15_lvalues_rvalues_and_move.cpp](15_lvalues_rvalues_and_move.cpp) | References and what move actually does |
| 16 | [16_custom_move_operations.cpp](16_custom_move_operations.cpp) | Custom move constructors and assignment |
| 17 | [17_build_a_managed_pointer.cpp](17_build_a_managed_pointer.cpp) | Inside a teaching smart pointer |
| 18 | [18_packet_corrections_and_trace.cpp](18_packet_corrections_and_trace.cpp) | Packet corrections and a final ownership trace |

## Compile and run one topic

Open a PowerShell terminal in this folder:

```powershell
g++ -std=c++17 -Wall -Wextra -pedantic 02_unique_ptr_basics.cpp -o 02_unique_ptr_basics.exe
.\02_unique_ptr_basics.exe
```

Replace both filenames for another lesson. Recompile after edits. Do not link all .cpp files together: each has its own main(). C++17 matches the memory folder; most examples use C++11/14 features.

## Check all examples

```powershell
.\run_all.ps1
```

The script compiles each lesson separately with warnings, runs it, and stops on failure. Executables go into the ignored build folder. It requires g++ on PATH. Run assertions enabled (do not add -DNDEBUG).

## Suggested pace

- 1–4: basics and automatic cleanup.
- 5–10: moving, functions, structs, RAII, and borrowing.
- 11–14: containers, mutation, shared ownership, and weak links.
- 15–18: why move works, custom operations, and a final trace.

After each topic, answer its prediction question before opening [quizAns.md](quizAns.md). Section 17 is the advanced implementation exercise. These examples are small learning programs, not general-purpose container implementations.
