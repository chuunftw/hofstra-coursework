# GitLab and submission checklist

## Version control

Inspection found this folder inside a larger existing Git repository. No
separate SimonGame GitLab repository or instructor access has been verified.
Do not point the larger coursework repository at a new SimonGame remote.

Create a private SimonGame project on Hofstra GitLab, clone it into a separate
folder outside the existing coursework repository, and copy the student project
files there (exclude `.pio/` and `.vscode/`). Continue development in that clone.
Include the source, PlatformIO configuration, docs, and design files. Keep the
AI reference outside the final submission unless the instructor permits it;
if retained in development history, clearly label its provenance.

Commit real milestones: initial setup, LED/button tests, sound, playback, input
checking, complete rounds, and final docs/design. Do not manufacture history for
work that was not performed. Push regularly and give the instructor Reporter
access using their actual account. Verify the project remains private.

## Final package

- Finish and test the student-authored `src/main.cpp`.
- Include `platformio.ini`, source, required local libraries if any, report, and
  schematic/design exports. Keep folders organized as code/docs/design.
- Exclude `.pio/`, `.git/`, `.vscode/`, and the study `reference/` folder from the
  submission ZIP. Retain the PlatformIO project structure for reproducibility.
- Extract the ZIP into a new folder and build that copy.
- Upload the ZIP to Blackboard and verify the submitted filename/confirmation.
- Demonstrate the project to the instructor using the testing checklist.

These external and physical tasks remain pending; a reference build is not a
finished student submission. No final ZIP has been created at this stage.
