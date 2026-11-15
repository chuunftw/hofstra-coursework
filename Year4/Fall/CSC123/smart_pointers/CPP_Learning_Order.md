# Smart pointers learning order

These **13 C++ files match the 13 topics in our overview**. The learning format follows the neighboring [memory folder](../memory/CPP_Learning_Order.md): explanations in comments, labeled demonstrations, predicted results, and incorrect examples commented out. Related demonstrations are sections inside one topic file.

Read the matching [study guide](studyguideMD.md) topic, predict the output, then run that file. Assertions check the stated results. Each file is a separate program with one main().

| Topic | File | Sections |
| --- | --- | --- |
| 1. Raw pointer review and memory errors | [01_raw_pointers_and_memory_errors.cpp](01_raw_pointers_and_memory_errors.cpp) | Raw pointers and memory errors |
| 2. unique_ptr and make_unique | [02_unique_ptr_and_make_unique.cpp](02_unique_ptr_and_make_unique.cpp) | unique_ptr and make_unique; Smart pointers to arrays |
| 3. Lifetime and ownership | [03_lifetime_and_ownership.cpp](03_lifetime_and_ownership.cpp) | Lifetime and automatic cleanup |
| 4. Moving and transferring ownership | [04_moving_and_transferring_ownership.cpp](04_moving_and_transferring_ownership.cpp) | Moving ownership; Functions: borrow or take ownership |
| 5. Smart pointers inside structs | [05_smart_pointers_inside_structs.cpp](05_smart_pointers_inside_structs.cpp) | Smart pointer members and the Rule of Zero |
| 6. RAII | [06_raii.cpp](06_raii.cpp) | RAII and raw observers |
| 7. References and borrowing | [07_references_and_borrowing.cpp](07_references_and_borrowing.cpp) | Borrowing the owner versus borrowing the target; Reseatable borrowing; Traversing owned structures |
| 8. Remaining memory hazards | [08_remaining_memory_hazards.cpp](08_remaining_memory_hazards.cpp) | Mutation and remaining hazards |
| 9. shared_ptr and make_shared | [09_shared_ptr_and_make_shared.cpp](09_shared_ptr_and_make_shared.cpp) | Shared ownership and reference counts |
| 10. weak_ptr | [10_weak_ptr.cpp](10_weak_ptr.cpp) | Weak pointers and ownership cycles |
| 11. Custom move operations and rvalue references | [11_custom_moves_and_rvalue_references.cpp](11_custom_moves_and_rvalue_references.cpp) | References and what move actually does; Custom move constructors and assignment |
| 12. Rules of Three, Five, and Zero | [12_rules_of_three_five_and_zero.cpp](12_rules_of_three_five_and_zero.cpp) | Rules of Three, Five, and Zero |
| 13. Building a custom smart pointer | [13_building_a_custom_smart_pointer.cpp](13_building_a_custom_smart_pointer.cpp) | Inside a teaching smart pointer; Packet corrections and a final ownership trace |

## Compile and run one topic

Open a PowerShell terminal in this folder:

```powershell
g++ -std=c++17 -Wall -Wextra -pedantic 02_unique_ptr_and_make_unique.cpp -o 02_unique_ptr_and_make_unique.exe
.\02_unique_ptr_and_make_unique.exe
```

Replace both filenames for another topic and recompile after edits. Do not link all .cpp files together. C++17 matches the memory folder; most examples use C++11/14 features.

## Check all topics

```powershell
.\run_all.ps1
```

Requires g++ on PATH. Compiles each file separately with warnings treated as errors, then runs it. Stops on a failed compilation or assertion. Executables go into the ignored build folder. Keep assertions enabled: do not add -DNDEBUG.

## Study rhythm

Read and run one section at a time, even when a topic has several sections. Answer the topic's [prediction questions](pracQuiz.md) before checking [the answers](quizAns.md). Topic 13 is the advanced implementation exercise and finishes with a trace combining ownership types. These are small learning programs, not general-purpose containers.
