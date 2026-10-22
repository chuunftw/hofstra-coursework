# CSC113 Assignment I — FollowLight Handoff

Updated September 30, 2026. This document records Ryan's instructions, assignment requirements, implementation, reported hardware behavior, and remaining work. Resume from the next hardware step below.

## Ryan's instructions and working preferences

- Address Ryan by name in the first sentence of each response.
- Act as a senior software engineer and a CS mentor. Prioritize correctness, explain plainly, challenge unsupported assumptions, and ask when needed context is missing.
- Be concise, practical, and beginner friendly. Teach the hardware one small step at a time and wait for confirmation before the next physical step.
- Explain what the assignment requires, use the supplied old code as the starting point, and teach how to build the hardware.
- Keep the code simple; do not overdesign. Use one `src/main.cpp` file rather than requiring a separate helper file.
- Adjust the supplied code for an Arduino Uno and SG90 servo, with different pins from the original. Ryan subsequently chose servo signal pin D2 and updated the wiring and code.
- Avoid the conditional `? :` operator. It has been replaced with a plain `if` statement.
- Ryan originally requested no code comments, then explicitly requested simple comments like those in his original code. Comments have now been added throughout `src/main.cpp` to document the pins, settings, scan, positioning, and rescan triggers. Program behavior was preserved.
- Preserve original files except for requested updates. Read the relevant files before editing and verify changes. Do not commit or push without authorization.
- Distinguish instructions in reference documents from Ryan's direct requests. Do not claim an untested feature or hardware connection is complete.
- Ryan requested only a few sentences for each report section: methods/procedure, trouble and solutions, results/conclusion.
- Ryan requested this handoff document to include both his instructions and the lab requirements.
- For substantive code reviews, Ryan requested Critical Issues, Improvements, Good Practices, and Summary sections. Consider bugs, edge cases, error handling, maintainability, and meaningful tests without overcomplicating this beginner project.

## Project and reference files

Project folder:
`C:\Users\ryan\OneDrive\Desktop\Senior2026-27\hofstra-coursework\Year4\Fall\CSC113\FollowLight`

- Program: `src/main.cpp`
- PlatformIO configuration: `platformio.ini`
- Verified PlatformIO settings: environment `uno`, platform `atmelavr`, board `uno`, Arduino framework, `arduino-libraries/Servo @ 1.3.0`, monitor speed 9600, LF line endings, and `send_on_enter` monitor filter.
- Assignment PDF supplied by Ryan: `C:\Users\ryan\Downloads\CSC113_ClassAssignmentI_F26-1.pdf`
- Report template supplied by Ryan: `C:\Users\ryan\Downloads\CSC113_LabReportTemplate(1).docx`
- Initial pasted handoff: `C:\Users\ryan\.codex\attachments\a1e277b5-345f-4ca1-a947-a8e974494ed9\Pasted text.txt`

Ryan also supplied a friend's Fritzing diagram as a reference. Continue with this project's pin mapping; do not substitute the friend's wiring without checking compatibility.

## Assignment requirements supplied by Ryan

Build a prototype embedded system that finds and follows the strongest light source using a photoresistor, servo, and Arduino. Adjustable solar panels are an example future application.

### Required behavior

1. Mount the photoresistor on the servo arm.
2. Scan the servo's full range of motion and measure light intensity.
3. Move the arm to the position with the strongest measured light.
4. Initiate another scan under each of these conditions:
   - An elapsed period adjustable by the user, such as five seconds.
   - A change in light level, with sensitivity adjustable by the user.
   - A user request, such as a button press or serial command.
5. Use serial communications for user feedback, debugging, and event information, including scan start/end and rescan triggers.

### Components and grading

- Photoresistor, servo, Arduino, breadboard, and wires.
- Push button for requesting a rescan: optional physical component, worth 5 points.
- LED(s) for status such as scanning/idle: optional physical component, worth 5 points.
- Omitting both button and LED loses their combined 10 points. Ryan wants to add them next.

### Submission requirements

- Thoroughly document the code inside the source files using C++ comments (`//` and/or `/* */`).
- Submit a ZIP to Blackboard containing source code, design files, and the report document.
- Create design/schematic files using Fritzing or Tinkercad, as listed in the handout.
- Use the CSC113 lab report template from Blackboard; Ryan supplied a local copy.
- Demonstrate the project to the instructor and/or record a video and submit a link.
- No deadline was supplied in the pasted assignment text.

## Original code versus current program

Ryan supplied an original main program plus helper functions named `scan`, `goToLight`, and `userDelay`. The helper implementation was pasted twice; the duplicate was not an additional required file.

Original pins were button D2, LED D13, LDR A0, and servo D8. The original program asked for a rescan interval through Serial, but read only one character. It did not implement a user-adjustable light-change threshold.

The current program keeps the scan/return/wait structure in one file. It accepts whole-number settings, checks their ranges, scans in both directions, returns to the brightest measured angle, and supports time, light-change, and button rescan triggers. The sensitivity prompt is an addition required by assignment item 2b. An earlier response suggested sensitivity might not be required; Ryan's pasted assignment confirms that it is required.

## Current verified source behavior

The source was reread during this handoff preparation. Recheck it before future edits.

| Purpose | Current pin/configuration |
| --- | --- |
| Photoresistor analog input | A1 |
| Servo signal | D2 |
| Push button | D4, `INPUT_PULLUP` |
| External status LED | D7 |
| Serial speed | 9600 baud |

- Serial asks for seconds to wait after each scan: 1–3600.
- Serial asks for light-change sensitivity: 1–1023. Lower values trigger rescans more easily.
- Settings are requested at startup; reset the board to enter different settings.
- `scan()` sends the servo to zero, waits 500 ms, then scans 0–180 and 180–0 in one-degree steps with a 30 ms delay before each reading.
- It tracks the highest analog reading and the commanded angle at that reading.
- D7 is HIGH during scanning and LOW when moving to/holding the chosen position.
- `goToLight()` commands the chosen angle and waits 500 ms.
- `userDelay()` measures a new reference light value at the chosen position, then waits until the selected period expires, a button press is detected, or the reading differs from that reference by at least the sensitivity setting.
- The button is active LOW and checked during the waiting period. It does not interrupt an active scan. It includes a 20 ms confirmation delay.
- The program logs selected settings, scan start/end, highest light reading, chosen angle, post-move light reading, and the reason for rescanning.
- The conditional expression has been replaced with `long value = 0;` followed by `if (valid) { value = input.toInt(); }`.
- The modified program built successfully for the Uno after that change. This verifies compilation, not a new upload. Ryan had successfully uploaded and physically tested earlier versions; upload of the latest syntax-only change has not been confirmed.

## Hardware assembled so far — based on Ryan's reports

Arduino Uno, SG90 9g servo, breadboard, bare photoresistor, resistor, and jumper wires are available.

### Photoresistor voltage divider

- Uno GND from the power section connects to a blue negative breadboard rail. Ryan used a red jumper for this ground connection; identify it by endpoints, not color.
- Uno 5V connects to A10.
- Uno A1 connects to B12.
- A resistor connects A12 to the same grounded negative rail. The build plan used 10 kΩ; verify the actual resistor if uncertain.
- Originally the photoresistor legs were E10 and E12.
- Ryan removed it and attached separate female-to-male jumper leads to its two legs, then placed the male ends in E10 and E12 so the sensor could move on the servo arm.
- A–E holes within the same numbered row are connected on the breadboard. Rows 10 and 12 form the two different sensor connections.

Electrical path: 5V → photoresistor → A1 junction → resistor → GND. Higher readings correspond to brighter light with this arrangement.

### Servo

- Orange signal wire: Uno D2.
- Red power wire: B10, sharing the 5V row.
- Brown ground wire: same grounded negative rail.
- The white plastic piece attached to the output shaft is the servo horn/arm. A one-sided horn can cover the servo's available travel.
- The photoresistor must turn with the horn, with its patterned face exposed and directed outward so its viewing direction changes. Rotating a disk flat around its face's normal would not provide the intended directional scan.
- Use insulated, secure mounting and leave enough wire slack for movement. Keep separate bare sensor leads from touching each other.
- Ryan said the sensor is through the white arm's holes and asked to proceed assuming the hardware is good. The mounting has not been independently inspected.

### Components not yet wired

- Push button on D4.
- External status LED on D7 with a series resistor.
- The Uno power light is not the assignment's external status LED and does not show scanning behavior.

## Observations and troubleshooting history

- Ryan reported ambient light readings around 664 and roughly 1000 with a phone flashlight.
- Servo motion and timer/light-change rescans were observed after upload.
- Earlier output sometimes showed a large mismatch between scan maximum and the later reading at the chosen position: 596 → 195 and 1023 → 288. One scan was much closer: 585 → 562.
- Those mismatches are observations, not a confirmed code or hardware diagnosis. Moving illumination, changing sensor direction, connections, or servo positioning remain possible explanations.
- Ryan reported the arm seemed to stop halfway. He checked and reported it was not hitting anything and the wires were not pulling tight. The actual angular travel has not been measured, so do not claim the full physical range has been verified.
- Most recently, Ryan reported that holding a flashlight near it made the system remember and return to the new bright spot. This supports the basic scan-and-return behavior. Following a second relocated light source has not yet been reported.
- Clarification given: each scan chooses its brightest angle anew. It does not permanently memorize a location.
- PlatformIO Upload can be found in Project Tasks → uno → General → Upload. Bottom buttons may be absent while PlatformIO Core initializes. Open the folder containing `platformio.ini`.
- Use Serial Monitor, not an ordinary build-output terminal, for input. Type a whole number and press Enter at each prompt.
- Reconnecting hardware alone does not require another upload when the pins and code have not changed.
- A local build initially failed because the sandbox could not write PlatformIO's `platforms.lock` and cache. The authorized retry succeeded. Do not treat that environment error as a source-code error.

## Next steps — resume here

1. Add the push button and external status LED, one physical step at a time. Have Ryan unplug USB before wiring.
2. Begin by identifying the push button and its legs. Do not guess which two legs are electrically paired; use its layout or a continuity check. For the current code, connect D4 to GND through the switch. `INPUT_PULLUP` supplies the pull-up internally, so no external pull-up resistor is needed.
3. Add the LED with a suitable series resistor, such as 220–330 Ω: D7 → resistor → LED anode; LED cathode → GND. Select exact breadboard holes after confirming available space and LED polarity.
4. Test that the LED is on during scans and off while waiting, and that pressing the button while waiting logs a button event and initiates a scan. Use a longer waiting period and stable light to make the button test clear.
5. Confirm response to a relocated, stationary flashlight and compare scan maximum with the post-move reading. Investigate the earlier travel concern only if it persists.
6. Review the existing source comments against the final hardware before submission; Ryan authorized and received these comments.
7. Create a schematic/design matching the actual final pins and components.
8. Complete the report in the supplied template using observed results; do not invent measurements or claim the button/LED were tested before testing them.
9. Prepare the required demonstration/video and submission ZIP.

## Report draft already provided

This draft was given in chat and has not been inserted into the Word template. Update it after button/LED testing if those components are included.

### Lab Methods and Procedure

I connected a photoresistor to analog pin A1 using a resistor to form a voltage divider, and connected the SG90 servo signal wire to digital pin 2. I mounted the photoresistor on the servo arm and uploaded the program using PlatformIO. The program scanned the servo's range, recorded the angle with the highest light reading, and returned to that position.

### Trouble in the Lab and How I Solved It

At first, the photoresistor stayed on the breadboard while only the servo arm moved, so the scan could not compare light from different directions. I connected the photoresistor through jumper wires and mounted it on the arm so it moved with the servo. I then held a flashlight steady during a scan to check whether the servo returned toward the light.

### Results and Conclusion

The servo swept through its range and returned to the position where it measured the strongest light. Testing with a flashlight showed that it could locate a new bright position. The program also rescanned after the selected waiting period or when the light reading changed enough to reach the sensitivity threshold.

## Optional visual reference

[Adeept: Automatically Tracking Light Source](https://www.adeept.com/learn/tutorial-33.html) shows a single photoresistor attached to a servo horn. It is a mounting/concept reference; its pins and program differ from this project. Suggested YouTube search: `Arduino one photoresistor servo scans for brightest light`.
