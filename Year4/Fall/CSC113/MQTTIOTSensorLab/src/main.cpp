// CSC113: DHT11 environmental monitoring over MQTT.
// Combines the class MQTT example and the local senseingMQTT DHT example.
#include <Arduino.h>
#include <WiFi.h>
#include <PubSubClient.h>
#include <ArduinoJson.h>
#include <DHT.h>
#include <cstring>

// Check these Wi-Fi settings before uploading at school.
const char* ssid = "CSC113";
const char* password = "IOTRules";

// Use a different ID for each ESP32. Commands must contain this exact ID.
const char* DEVICE_ID = "Rc";
const char* LOCATION = "classroom";
constexpr uint8_t DHT_PIN = 22;  // DHT11 DATA wire; matches senseingMQTT.
constexpr uint8_t DHT_TYPE = DHT11;

const char* MQTT_SERVER = "broker.hivemq.com";
constexpr uint16_t MQTT_PORT = 1883;
const char* PUBLISH_TOPIC = "csc113/ambientenv/publish";
const char* SUBSCRIBE_TOPIC = "csc113/ambientenv/listen";
constexpr unsigned long PUBLISH_INTERVAL_MS = 2000;
constexpr unsigned long RECONNECT_INTERVAL_MS = 5000;

WiFiClient wifiClient;
PubSubClient client(wifiClient);
DHT dht(DHT_PIN, DHT_TYPE);
String mqttClientId;
bool monitoring = true;  // Start monitoring on boot; STOP pauses readings.
unsigned long lastPublish = 0;
unsigned long lastMqttAttempt = 0;
unsigned long lastWifiAttempt = 0;
bool subscribed = false;

// Runs when a command arrives from the broker.
void callback(char* topic, byte* payload, unsigned int length) {
    if (strcmp(topic, SUBSCRIBE_TOPIC) != 0) {
        return;
    }

    JsonDocument doc;
    DeserializationError error = deserializeJson(
        doc, reinterpret_cast<const char*>(payload), length);
    if (error) {
        Serial.print("Invalid command JSON: ");
        Serial.println(error.c_str());
        return;
    }

    if (!doc["ID"].is<const char*>() || !doc["cmd"].is<const char*>()) {
        Serial.println("Command needs string fields ID and cmd.");
        return;
    }
    const char* id = doc["ID"];
    const char* command = doc["cmd"];
    if (strcmp(id, DEVICE_ID) != 0) {
        return;  // Other students share this topic; only handle our own ID.
    }

    if (strcmp(command, "STOP") == 0) {
        monitoring = false;
        Serial.println("Monitoring STOPPED. Still listening for START.");
    } else if (strcmp(command, "START") == 0) {
        monitoring = true;
        Serial.println("Monitoring STARTED.");
    } else {
        Serial.println("Unknown command. Use START or STOP.");
    }
}

// Retry failed connections periodically instead of waiting in a retry loop.
void maintainConnection() {
    unsigned long now = millis();
    if (WiFi.status() != WL_CONNECTED) {
        subscribed = false;
        if (client.connected()) {
            client.disconnect();
        }
        if (now - lastWifiAttempt >= RECONNECT_INTERVAL_MS) {
            lastWifiAttempt = now;
            Serial.println("Waiting for Wi-Fi; retrying...");
            WiFi.reconnect();
        }
        return;
    }

    if (!client.connected()) {
        subscribed = false;
        if (now - lastMqttAttempt < RECONNECT_INTERVAL_MS) {
            return;
        }
        lastMqttAttempt = now;
        Serial.print("Connecting to MQTT... ");
        if (!client.connect(mqttClientId.c_str())) {
            Serial.print("failed, state=");
            Serial.println(client.state());
            return;
        }
        Serial.println("connected.");
        Serial.print("Wi-Fi IP: ");
        Serial.println(WiFi.localIP());
    }

    if (!subscribed) {
        subscribed = client.subscribe(SUBSCRIBE_TOPIC);
        Serial.println(subscribed ? "Listening for START/STOP commands."
                                  : "Subscription failed; will retry.");
    }
}

void publishReadings() {
    float humidity = dht.readHumidity();
    float temperature = dht.readTemperature();  // Celsius.
    if (isnan(humidity) || isnan(temperature)) {
        Serial.println("DHT11 read failed. Check sensor power, DATA pin and wiring.");
        return;
    }

    JsonDocument doc;
    doc["ID"] = DEVICE_ID;
    doc["humidity"] = humidity;       // Relative humidity (%).
    doc["temp"] = temperature;        // Degrees Celsius.
    doc["location"] = LOCATION;

    String message;
    serializeJson(doc, message);
    if (client.publish(PUBLISH_TOPIC, message.c_str())) {
        Serial.print("Published: ");
        Serial.println(message);
    } else {
        Serial.println("Publish failed; will retry at the next interval.");
    }
}

void setup() {
    Serial.begin(115200);
    dht.begin();
    WiFi.mode(WIFI_STA);
    WiFi.begin(ssid, password);
    mqttClientId = "ESP32-" + WiFi.macAddress();

    client.setServer(MQTT_SERVER, MQTT_PORT);
    client.setCallback(callback);
    client.setBufferSize(512);
    client.setSocketTimeout(2);
    lastMqttAttempt = millis() - RECONNECT_INTERVAL_MS;
    lastWifiAttempt = millis();
    lastPublish = millis();

    Serial.print("Device ID: ");
    Serial.println(DEVICE_ID);
    Serial.println("Connecting to Wi-Fi. Monitoring starts automatically.");
}

void loop() {
    maintainConnection();
    if (!client.connected()) {
        return;
    }

    client.loop();  // Keep receiving commands even while monitoring is stopped.
    if (!monitoring || !subscribed || !client.connected()) {
        return;
    }

    unsigned long now = millis();
    if (now - lastPublish >= PUBLISH_INTERVAL_MS) {
        lastPublish = now;
        publishReadings();
    }
}
