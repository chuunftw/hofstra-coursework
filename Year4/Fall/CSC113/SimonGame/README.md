# CSC113 Simon game

The parent PlatformIO project (`src/main.cpp`) is the student's practice version.
The completed AI-generated study reference is a separate project in `reference/`.
It is supplied to compare behavior and discuss code, rather than as a claim of
student-authored work. The original requirement says the student must write the
submitted code and make the design.

## Open and build

- To work on your own code, open this folder in PlatformIO.
- To inspect/build the reference, open `reference/` as its own PlatformIO project.
- From the PlatformIO terminal in this folder, run `pio run -d reference` to build
  the reference without uploading it.
- After verifying the wiring, `pio run -d reference -t upload` uploads the reference;
  `pio device monitor -b 9600` opens its debug output. Close the monitor before uploading.
- Building the parent project does not build the reference. PlatformIO only
  compiles that project's `src/` directory.

## Game rules

Release all buttons, then press any single button to start. Watch/listen, release
the buttons, and repeat the sequence. Each correct round adds one item, preserving
the previous items. Complete lengths 1, 2, 3, and 4 to win. A wrong answer ends the
game. After either outcome, release and press a button to restart.

One held button counts once. Simultaneous presses are ignored until all buttons
are released. Input is inactive during playback and feedback. Press and release
must each be stable for 25 ms; very short taps can be ignored. Serial is optional
and is not used to select difficulty. There is no answer time limit.

## Project materials

- `reference/src/main.cpp`: complete, commented reference implementation.
- `design/wiring.md`: pin map, wiring instructions, and Tinkercad checklist.
- `docs/testing.md`: verification record and hardware test checklist.
- `docs/report-outline.md`: prompts for the student's report; no fabricated results.
- `docs/submission.md`: GitLab, ZIP, and demonstration steps.

Hardware operation is not yet verified. The user's sound component still needs
identification. No Tinkercad design, final lab report, GitLab project, Blackboard
submission, or instructor demonstration is claimed as completed.
