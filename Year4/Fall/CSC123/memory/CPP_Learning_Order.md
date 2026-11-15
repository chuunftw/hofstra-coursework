# C++ learning order

These examples follow `References_and_Heap_Study_Guide.md`. File numbers match the guide's section numbers. Your original `ptrVSref.cpp` is now named `02_pointers_and_references.cpp`, with its examples preserved. It also reviews the basic pointer symbols from section 1.

Each C++ file is a separate program with its own `main()`. Read the comments, predict the labeled output, and then run that file. Invalid examples are commented out so you can study the mistake while running the corrected version.

| Guide section | File | What to watch |
| --- | --- | --- |
| 1, extra example | [01_pointer_to_pointer.cpp](01_pointer_to_pointer.cpp) | `pp -> p -> x`; one `*` per step |
| 2 (also reviews section 1) | [02_pointers_and_references.cpp](02_pointers_and_references.cpp) | Addresses, dereferencing, and fixed reference targets |
| 3 | [03_function_parameters.cpp](03_function_parameters.cpp) | Copies versus changes to the caller's object |
| 4 | [04_loops_and_pointer_arithmetic.cpp](04_loops_and_pointer_arithmetic.cpp) | Element copies, references, and pointer movement |
| 5 | [05_lvalues_and_rvalues.cpp](05_lvalues_and_rvalues.cpp) | `int&`, `const int&`, and `int&&` |
| 6 | [06_stack_and_heap.cpp](06_stack_and_heap.cpp) | The pointer and its target have separate lifetimes |
| 7 | [07_new_and_delete.cpp](07_new_and_delete.cpp) | Match `new`/`delete` and `new[]`/`delete[]` |
| 8 | [08_memory_leaks.cpp](08_memory_leaks.cpp) | Release storage before losing its address |
| 9 | [09_double_free.cpp](09_double_free.cpp) | Two pointers can share one allocation |
| 10 | [10_use_after_free.cpp](10_use_after_free.cpp) | Finish access before releasing storage |
| 11 | [11_return_values_and_lifetimes.cpp](11_return_values_and_lifetimes.cpp) | Which returned results survive a function call |
| 12 | [12_arrays_of_pointers.cpp](12_arrays_of_pointers.cpp) | Release the integers, then the pointer array |
| 13 | [13_structs_and_destructors.cpp](13_structs_and_destructors.cpp) | Member access and cleanup when objects die |
| 14 | [14_resizing_arrays.cpp](14_resizing_arrays.cpp) | Allocate, copy, release, adopt |
| 15 | [15_shallow_copy.cpp](15_shallow_copy.cpp) | Copying an address shares a target |
| 16 | [16_deep_copy_rule_of_three.cpp](16_deep_copy_rule_of_three.cpp) | Independent copies and three ownership operations |
| 17 | [17_packet_corrections.cpp](17_packet_corrections.cpp) | Corrected traces and interpretation reminders |
| 18 | [18_tracing_memory.cpp](18_tracing_memory.cpp) | Track allocations, aliases, and releases together |

## Compile and run one topic

Open a PowerShell terminal in this folder. Save your edits, then run:

```powershell
g++ -std=c++17 -Wall -Wextra -pedantic 03_function_parameters.cpp -o 03_function_parameters.exe
.\03_function_parameters.exe
```

Replace both filenames with the topic you want. Compile again after edits. Do not compile `*.cpp` into one executable: each file has its own `main()`.

The heap lessons use small fixed examples. As in the practice quiz, multi-allocation traces assume allocations succeed; they are teaching examples rather than general-purpose containers. File 16 demonstrates allocating replacement storage before releasing the old storage during copy assignment.
