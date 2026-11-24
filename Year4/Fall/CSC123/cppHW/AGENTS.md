# CSC123 C++ Memory Assignments

Work through Bubblesort, Matrix, then Observers one step at a time. Start by explaining the original memory error, including the exact lines and why they cause it. Preserve the starter source until Ryan asks for a code change.

- `bubblesort.cpp`: Explain the original error. Convert `students` to `unique_ptr<string[]>`, allocate with `make_unique<string[]>`, and remove the destructor. Explain and fix any issue this introduces in `bubblesort`. Preserve `main` and generic sorting based on `<`.
- `matrixerror.cpp`: Put the explanation in comments in the source. Use the prescribed smart-pointer array types and references, follow the Rule of Zero, and preserve efficiency. Uncomment `operator_testing()` after fixing the program.
- `observers_problem.cpp`: Explain which lines cause the error and what kind of error it is. Fix it without cloning or changing `main`. Provide a short example of the same kind of error.

Use the assignment headers as the source of truth. The headers do not specify `answers.txt` as a submission requirement.
