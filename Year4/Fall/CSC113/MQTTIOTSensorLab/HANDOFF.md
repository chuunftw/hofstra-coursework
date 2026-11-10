# CSC113 ESP32 MQTT sensor lab handoff

Date: November 10, 2026

## Goal and current situation

Prepare an ESP32 to publish DHT11 temperature/humidity readings and receive
remote START/STOP commands. Ryan is at home; the ESP32 and sensor are at school.
The code is implemented, but upload and hardware/network testing remain.
Ryan wants to use MQTTX in a browser; installing the desktop app is optional.

Project: `C:\Users\Ryan\Desktop\senior\senior\Year4\Fall\CSC113\MQTTIOTSensorLab`

Assignment: `C:\Users\Ryan\Downloads\MQTTIOTSesnsorLab-1.pdf`

The PDF requires publishing ID, location, temperature and humidity, receiving
start/stop monitoring commands, using class examples, and using GitLab for code.
The exact topics and JSON field names below came from Ryan's pasted class notes.
No GitLab commit or push has been performed in this session.

## Files and implemented behavior

- `src/main.cpp`: combines the original MQTT example with the neighboring
  `senseingMQTT` DHT11 example. Publishes actual readings, handles commands,
  retries connections and skips failed sensor reads.
- `platformio.ini`: selects `esp32doit-devkit-v1` and includes PubSubClient,
  ArduinoJson 7, Adafruit DHT sensor library and Adafruit Unified Sensor.
- `start.json` / `stop.json`: optional payload examples to paste into MQTTX.
  The ESP32 does not load these files. One editable payload or directly typed
  JSON in MQTTX would also work.
- `README.md`: setup and test notes; its connection table describes the desktop
  TCP connection. Use the browser settings below for MQTTX Web.
- `json.txt`: older class notes mentioning `csc113/ambientenv`. This file is
  not read by the program; use the two current topics below instead.

## Current settings

| Setting | Value |
| --- | --- |
| JSON device ID | `Rc` (case-sensitive, explicitly requested by Ryan) |
| Location | `classroom` (placeholder to confirm/change) |
| Sensor | DHT11 |
| Sensor DATA pin | GPIO 22, taken from the local DHT example; wiring unverified |
| Temperature unit | Celsius |
| Publish interval | 2 seconds |
| Startup state | Monitoring enabled |
| Broker | `broker.hivemq.com` |
| ESP32 transport / port | MQTT over TCP, `1883` |
| Publish topic | `csc113/ambientenv/publish` |
| Command subscription | `csc113/ambientenv/listen` |
| Serial Monitor speed | `115200` baud |

The existing active Wi-Fi settings in `main.cpp` were preserved. Check them at
school; do not copy the password into a handoff or chat. The code uses ordinary
SSID/password Wi-Fi login; campus enterprise or captive-portal login is not
implemented. Confirm whether the professor expects a different broker.

The startup state, location placeholder and Celsius unit are implementation
choices, not explicit requirements from the supplied class notes.

## MQTTX Web connection

Open <https://mqttx.app/web-client>.

Connection settings previously supplied in this conversation:

- Protocol: `wss://` (secure WebSocket).
- Host: `broker.hivemq.com`.
- Port: `8884`.
- Path: `/mqtt`.
- Full endpoint: `wss://broker.hivemq.com:8884/mqtt`.
- MQTT version: `3.1.1`.
- Client ID: a unique browser client name, for example `Rc-Web`.
- Username/password: empty.

This browser connection has not been tested in this session. The ESP32 keeps
port 1883: the browser and ESP32 use different transports to reach the same
broker. Do not replace the ESP32's port with the browser WebSocket port.

## Messages and expected result

Subscribe in MQTTX to `csc113/ambientenv/publish`. Example reading:

```json
{
  "ID": "Rc",
  "humidity": 57,
  "temp": 22.1,
  "location": "classroom"
}
```

These numbers are illustrative. The firmware fills in actual sensor readings.
Other students may publish to the same topic; identify this board by `Rc`.
The classmate's top screenshot matched these four fields. Extra fields shown
in the other classmate's message are not needed for the supplied format.

To pause readings, publish to `csc113/ambientenv/listen`:

```json
{"ID":"Rc","cmd":"STOP"}
```

To resume, publish to that same topic:

```json
{"ID":"Rc","cmd":"START"}
```

Use QoS 0 and Retain off for commands. STOP pauses sensor reading/publishing
while the board stays connected and listens for START. Commands for other IDs
are ignored. Malformed commands are logged and ignored. Restarting the board
enables monitoring again; STOP is not stored across reboots.

## Next steps at school

1. Confirm DHT11 wiring and GPIO 22, Wi-Fi settings, location, and broker.
2. Connect the ESP32 by USB and use PlatformIO Upload.
3. Open Serial Monitor at 115200 baud and check Wi-Fi/MQTT connection logs.
4. Connect MQTTX Web and subscribe to the publish topic.
5. Confirm messages with ID `Rc` and real readings arrive about every 2 seconds.
6. Send STOP, confirm readings pause, then send START and confirm they resume.
7. Send a command with another ID and confirm this board ignores it.

If there are no readings, inspect Serial Monitor first: Wi-Fi retries, MQTT
failure state, or DHT11 read failures identify different problems. A missing or
failed sensor intentionally produces no reading messages.

## Verification and limits

- The full project previously compiled successfully for `esp32doit-devkit-v1`.
- Both command files were parsed and validated as JSON with ID `Rc`.
- The code's `DEVICE_ID` was checked to match those command files.
- Rebuilt the current code with ID `Rc` on November 10, 2026: **SUCCESS**
  (19.73 seconds). RAM: 47,200 / 327,680 bytes; flash: 998,420 / 1,310,720 bytes.
- No firmware upload, live MQTT connection or physical sensor test was done.
  A successful build does not prove school Wi-Fi, wiring, readings or commands.

Build command (PowerShell):

```powershell
& 'C:\Users\Ryan\.platformio\penv\Scripts\platformio.exe' run -d 'C:\Users\Ryan\Desktop\senior\senior\Year4\Fall\CSC113\MQTTIOTSensorLab'
```

In this restricted session, the build needed elevated tool execution to access
the existing PlatformIO cache (`C:\Users\Ryan\.platformio\platforms.lock`).
That was a sandbox access issue; no cache deletion or ownership change was used.

## Continuing assistance

Ryan is learning the MQTT workflow. Keep explanations short and take one step
at a time. Explain the ESP32, broker and MQTTX roles clearly. Keep compilation
evidence separate from hardware verification. The user authorized preparing
completed code; the remaining work is configuration confirmation and live
testing at school.

## Project folder rename

The project folder is now `MQTTIOTSensorLab` (previously `MQTTExp`). Git tracks
the moved files at the new paths; existing staged work was preserved. Open the
new folder in VS Code. Windows refused to rename the original root directory,
so the contents were moved individually. Any remaining old directory is empty.
The successful build recorded above was performed before the folder move.
