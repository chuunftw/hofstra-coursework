# Repository Guidelines

## Project Structure

Coursework is grouped by year and term under `Year1/` through `Year4/`. Current fall work is under `Year4/Fall/`:

- `CSC123/` contains programming-language assignments and examples. `rust/` and `smart_pointers/` hold numbered study programs, while `cppHW/`, `javaHW/`, and `lambda7b/` hold separate assignments.
- `CSC113/` contains independent PlatformIO projects. Each project's `platformio.ini` defines its build environments, and firmware lives in `src/`.
- `CSC174/A1/code/` and `CSC174/A2/code/` contain Python assignment code and test scripts. `CSC174/finalPhase3/` contains the group project's instructions and experiment plan.
- `CSC105/` contains course logs. Keep course materials and assignment assets with the work they support.

## Build and Test

Run commands from the relevant project directory. There is no repository-wide build or test command.

- **Rust:** In `CSC123/rust/`, run `rustc --edition=2021 01_copy_move_clone.rs` and then `./01_copy_move_clone.exe` in PowerShell. Each numbered lesson is a standalone program.
- **F#:** In `CSC123/lambda7b/`, run `dotnet build` with the .NET 10 SDK. Use the accompanying `test*.7b` programs to check evaluator behavior.
- **Python:** Run `python tests.py` from the affected CSC174 assignment's `code/` directory. Follow the existing `test_*` names when extending those scripts.
- **Firmware:** Run `pio run` from the lab directory. Record board and serial-output checks separately from compilation results.

## Coding Style and Coursework

Match the surrounding file's indentation and naming. Use four spaces and `snake_case` in the numbered Rust examples, and format edited Rust files with `rustfmt --edition 2021 <file>`. Continue the `NN_topic.rs` pattern for study examples. Keep intentional compiler-error examples commented out. Treat the Rust Assignment I skeleton and the `csc_7b_fc` compiler documentation as separate assignment references. Preserve starter code and assignment signatures, and change coursework solutions only when explicitly requested.

## Commits and Pull Requests

Use a short subject that names the change. History includes both plain subjects such as “Add standalone CSC123 Rust study examples” and prefixed subjects such as `feat: …`. Keep changes focused on one course or assignment. In a pull request, identify the affected project and report validation results. Link the assignment or issue when relevant, and attach screenshots when they demonstrate a required result.
