# Wiring design

This is a connection guide, not the required Fritzing/Tinkercad design file.
Disconnect USB power before changing wiring. Connect Uno GND to the breadboard
ground rail; verify continuity if the rail is split.

| Choice | LED pin | Button pin | Tone |
| --- | --- | --- | --- |
| Red (0) | D8 | D2 | 262 Hz |
| Blue (1) | D9 | D3 | 330 Hz |
| Green (2) | D10 | D4 | 392 Hz |
| Yellow (3) | D11 | D5 | 523 Hz |
| Passive piezo | D6 | -- | All tones and effects |

## Connections

Each LED: digital output -> its own 330-ohm resistor -> LED anode (+);
LED cathode (-) -> GND. The long leg is normally the anode; the flat side of
the LED body normally marks the cathode. Check the component if legs were cut.

Each button: assigned digital input -> switch -> GND. Use `INPUT_PULLUP`:
released = HIGH, pressed = LOW. No external pull-down resistor is used.
Four-legged tactile switches contain internally connected pairs. Use two
contacts that are disconnected when released and connected when pressed;
confirm the pairs with a continuity check or the switch's pin diagram.

Sound: the reference expects a small passive piezo element suitable for direct
Arduino GPIO drive. Once identified, connect positive to D6 and negative to
GND if its specifications permit this. A two-drum-looking module has not been
identified; do not assume that it is this part or connect it using this guide.
An ordinary low-impedance speaker, active buzzer, or sensor module may require
different wiring or a different part. Obtain the part marking/photo first.

Leave A0 unconnected for the reference's random seed. Leave D0/D1 available for
USB Serial. All LEDs use digital on/off control, not PWM brightness control.

## Assemble and draw in stages

1. Wire and test the red LED with a small student-written LED test.
2. Wire and test the red button with a small input test.
3. Repeat for blue, green, and yellow; verify the color/pin mapping.
4. Identify the sound part, verify its electrical requirements, and test tones.
5. Run the full game and complete `docs/testing.md`.
6. In Tinkercad Circuits, create an Uno + breadboard design using this exact map,
   four 330-ohm resistors, four LEDs, four buttons, and the verified sound part.
7. Label pins/colors, verify the design matches the real circuit, and save a
   readable export/screenshot plus the project link in this folder. Export an
   editable design if the tool supports it. Photograph the actual circuit.

If using Tinkercad's Arduino sketch editor, the reference source can be used as
the sketch; `platformio.ini` is only for PlatformIO. Simulation does not replace
testing the actual hardware.

References:
- https://docs.arduino.cc/built-in-examples/digital/InputPullupSerial/
- https://docs.arduino.cc/built-in-examples/digital/toneMelody/
