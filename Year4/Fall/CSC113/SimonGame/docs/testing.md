# Verification record

The student reported that the original PlatformIO Uno starter built successfully.
Reference build and software checks: PASSED on 2026-10-21.
Physical circuit, buzzer, and Tinkercad simulation: NOT TESTED.

## Reference verification performed

- PlatformIO Uno build succeeded with the installed atmelavr 5.3.0 platform:
  5,582 bytes flash (17.3%) and 254 bytes static RAM (12.4%).
- A temporary host C++ harness compiled the actual reference source with mocked
  Arduino input, output, time, and randomness. It passed with compiler flags
  `-std=c++11 -Wall -Wextra -Werror`.
- Checks passed for 25-ms debounce, held presses, release bounce, simultaneous
  buttons, unsigned timer rollover, start/playback release gating, no timeout,
  playback order and timing, repeated colors, sequence preservation, lengths
  1 through 4, final victory, failure at each of four answer positions, and
  restarting after win/loss. A further 100 consecutive complete games passed.
- The temporary harness is in `reference/.pio/host-check/` (ignored build
  artifacts). Its deterministic random source supplies red, blue, blue, yellow;
  production source still calls Arduino `random()`.
- These checks verify software behavior, not real switch bounce, audible pitches,
  electrical wiring, physical timing accuracy, or the quality of random seeding.
  The host uses its own unsigned word size for the rollover check; the Uno build
  separately verifies that the code compiles for the actual target.

## Hardware acceptance checklist

Record actual outcomes, dates, and observations. Do not mark a test passed solely
because the code compiles. Use a temporary known sequence such as red, blue,
blue, yellow while debugging, then restore random generation and rebuild.

| Test | Expected result | Actual result |
| --- | --- | --- |
| Each LED | Only its assigned LED lights | Not tested |
| Each button | Released HIGH, pressed LOW | Not tested |
| Four tones | Distinct pitch per choice, correct LED | Not tested |
| Startup | Outputs off; waits for release then one press | Not tested |
| Start press held | Starts once; does not count as an answer | Not tested |
| Playback | 500 ms per item, 250 ms dark/silent gap | Not tested |
| Correct rounds | Lengths 1, 2, 3, 4; old prefix preserved | Not tested |
| Repeated colors | Distinct flashes; requires separate presses | Not tested |
| Final success | Distinct victory effect; no fifth item | Not tested |
| Wrong first/later item | Failure lights/sound; game ends | Not tested |
| Held answer button | Counts only once | Not tested |
| Fast/bouncing input | No duplicate; under-25-ms taps may be ignored | Not tested |
| Two buttons together | Ignored until all released | Not tested |
| Button during playback | Does not become an answer; release required | Not tested |
| Restart after win/loss | Fresh one-item game; counter reset | Not tested |
| Wait 30 seconds | No timeout or spontaneous press | Not tested |
| Power/reset | Returns to waiting with outputs off | Not tested |

## Demonstration sequence

Show the wiring and explain the pin map. Start a game, demonstrate a correct
round and increasing length, deliberately make a mistake, restart, then complete
all four rounds. Explain the release rule, repeated colors, feedback differences,
and the array bound of four. Keep the GitLab history, schematic, and report ready.
