# ESP32 environmental monitoring lab

This project combines the class MQTT example with the DHT11 example in the
adjacent `senseingMQTT` project. It publishes real sensor readings every two
seconds and listens for commands, including while monitoring is stopped.

## Before uploading at school

Check the settings near the top of `src/main.cpp`:

- `ssid` and `password`: the Wi-Fi network available to your ESP32. The existing
  active settings were preserved. This code uses ordinary Wi-Fi password login.
- `DEVICE_ID`: defaults to `Rc`. Use a unique ID for each board.
- `LOCATION`: defaults to `classroom`; replace it with your actual location.
- `DHT_PIN`: defaults to GPIO 22, matching the existing DHT example. Confirm that
  this is the GPIO connected to your DHT11 DATA wire. Connect the sensor to
  the board's 3.3 V and GND, and follow the lab's sensor wiring instructions.
- `MQTT_SERVER`: retains the example's `broker.hivemq.com`, port `1883`. Confirm
  whether your professor wants a different broker.

Build and Upload from PlatformIO with `esp32doit-devkit-v1` selected. Open Serial
Monitor at **115200 baud**. Monitoring starts automatically after boot. This
startup behavior and the Celsius temperature unit are implementation choices;
adjust them if your professor specifies otherwise.

## Test with MQTTX

`start.json` and `stop.json` contain ready-to-copy command payloads for device
`Rc`. Paste their contents into MQTTX and publish to
`csc113/ambientenv/listen`.

Create a connection with these settings:

| Setting | Value |
| --- | --- |
| Protocol | MQTT over TCP (`mqtt://`) |
| Host | `broker.hivemq.com` |
| Port | `1883` |
| MQTT version | `3.1.1` |
| Client ID | A unique name, such as `Ryan-MQTTX` |
| SSL/TLS | Off |
| Username / password | Empty |

Use MQTTX Desktop for this TCP connection. MQTTX Web requires the broker's
WebSocket connection settings instead.

1. Subscribe to `csc113/ambientenv/publish`. The class shares this topic, so
   identify your board using the `ID` in each message.
2. After the ESP32 connects and reads its sensor, expect messages shaped like:

   ```json
   {"ID":"Rc","humidity":45.2,"temp":23.6,"location":"classroom"}
   ```

   These are example values. `humidity` is relative humidity in percent and
   `temp` is Celsius. Failed sensor reads are logged and not published.
3. Publish this JSON to `csc113/ambientenv/listen` with QoS 0 and **Retain off**:

   ```json
   {"ID":"Rc","cmd":"STOP"}
   ```

   Your board should stop sending readings while remaining connected.
4. Send `{"ID":"Rc","cmd":"START"}` to the same topic. Readings
   should resume. ID and command matching are case-sensitive.
5. A command for a different ID should not change this board's monitoring.

The public broker is shared and unencrypted; use it for lab data only. The
message ID routes commands to the intended board; it is not authentication.

## Verification

Compilation can be checked without an ESP32. Sensor readings, school Wi-Fi,
broker connectivity, command delivery and physical wiring still require the
board at school. No upload or live MQTT connection is performed by building.
