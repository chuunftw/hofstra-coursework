#include <Arduino.h>
#include "DHT.h"
#include <WiFi.h>
#include <PubSubClient.h>
#include <ArduinoJson.h>

const char* ssid = "Ryan's IPhone";
const char* password = "wigwomm87";
const char* mqtt_server = "broker.hivemq.com";
const char* publishTopic = "csc113/ambientenv/publish";
const char* subscribeTopic = "csc113/ambientenv/listen";
const char* sensorID = "RC";
const char* location = "RC desk";

WiFiClient wifiClient;
PubSubClient client(wifiClient);
bool publishingEnabled = true;
unsigned long lastMeasurement = 0;
unsigned long lastMqttAttempt = 0;
unsigned long lastWiFiAttempt = 0;
unsigned long lastLedChange = 0;
bool ledOn = false;

void callback(char* topic, byte* payload, unsigned int length) {
  JsonDocument doc;
  DeserializationError error = deserializeJson(doc, payload, length);
  if (error) {
    Serial.print("Invalid command JSON: ");
    Serial.println(error.c_str());
    return;
  }
  if (!doc["ID"].is<const char*>() ||
      strcmp(doc["ID"].as<const char*>(), sensorID) != 0) {
    return;
  }
  const char* command = doc["cmd"] | "";
  if (strcmp(command, "STOP") == 0) {
    publishingEnabled = false;
    Serial.println("RC: publishing stopped");
  } else if (strcmp(command, "START") == 0) {
    publishingEnabled = true;
    Serial.println("RC: publishing started");
  } else {
    Serial.println("Unknown command; use STOP or START");
  }
}

void maintainConnection() {
  unsigned long now = millis();
  if (WiFi.status() != WL_CONNECTED) {
    if (now - lastWiFiAttempt >= 10000) {
      lastWiFiAttempt = now;
      Serial.println("Retrying Wi-Fi...");
      WiFi.reconnect();
    }
    return;
  }
  if (!client.connected() && now - lastMqttAttempt >= 5000) {
    lastMqttAttempt = now;
    String clientID = "ESP32-RC-" + WiFi.macAddress();
    Serial.println("Connecting to MQTT...");
    if (client.connect(clientID.c_str())) {
      if (client.subscribe(subscribeTopic)) {
        Serial.println("MQTT connected and subscribed");
      } else {
        Serial.println("MQTT subscription failed; retrying");
        client.disconnect();
      }
    } else {
      Serial.print("MQTT connection failed, rc=");
      Serial.println(client.state());
    }
  }
}

#define LED_PIN 32
#define VOUT_PIN 25

#define DHTPIN 22     // Digital pin connected to the DHT sensor
// Feather HUZZAH ESP8266 note: use pins 3, 4, 5, 12, 13 or 14 --
// Pin 15 can work but DHT must be disconnected during program upload.

// Uncomment whatever type you're using!
#define DHTTYPE DHT11   // DHT 11
//#define DHTTYPE DHT22   // DHT 22  (AM2302), AM2321
//#define DHTTYPE DHT21   // DHT 21 (AM2301)

// Connect pin 1 (on the left) of the sensor to +5V
// NOTE: If using a board with 3.3V logic like an Arduino Due connect pin 1
// to 3.3V instead of 5V!
// Connect pin 2 of the sensor to whatever your DHTPIN is
// Connect pin 4 (on the right) of the sensor to GROUND
// Connect a 10K resistor from pin 2 (data) to pin 1 (power) of the sensor

// Initialize DHT sensor.
// Note that older versions of this library took an optional third parameter to
// tweak the timings for faster processors.  This parameter is no longer needed
// as the current DHT reading algorithm adjusts itself to work on faster procs.
DHT dht(DHTPIN, DHTTYPE);

void setup() 
{
  // put your setup code here, to run once:
  Serial.begin(115200);
  pinMode(LED_PIN,OUTPUT);
  //pinMode(VOUT_PIN,OUTPUT);
  //digitalWrite(VOUT_PIN,HIGH);
  Serial.println("before dht begin");
  dht.begin();
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  Serial.println("Connecting to CSC113 Wi-Fi...");
  client.setServer(mqtt_server, 1883);
  client.setCallback(callback);
}

void measureTemp() {
  // Wait a few seconds between measurements.
  //delay(2000);

  // Reading temperature or humidity takes about 250 milliseconds!
  // Sensor readings may also be up to 2 seconds 'old' (its a very slow sensor)
  float h = dht.readHumidity();
  // Read temperature as Celsius (the default)
  float t = dht.readTemperature();
  // Read temperature as Fahrenheit (isFahrenheit = true)
  float f = dht.readTemperature(true);

  // Check if any reads failed and exit early (to try again).
  if (isnan(h) || isnan(t) || isnan(f)) {
    Serial.println(F("Failed to read from DHT sensor!"));
    return;
  }

  // else print info
  // Compute heat index in Fahrenheit (the default)
  float hif = dht.computeHeatIndex(f, h);
  // Compute heat index in Celsius (isFahreheit = false)
  float hic = dht.computeHeatIndex(t, h, false);

  Serial.print(F("Humidity: "));
  Serial.print(h);
  Serial.print(F("%  Temperature: "));
  Serial.print(t);
  Serial.print(F("°C "));
  Serial.print(f);
  Serial.print(F("°F  Heat index: "));
  Serial.print(hic);
  Serial.print(F("°C "));
  Serial.print(hif);
  Serial.println(F("°F"));

  if (publishingEnabled && client.connected()) {
    JsonDocument doc;
    doc["ID"] = sensorID;
    doc["humidity"] = h;
    doc["temp"] = t; // Celsius
    doc["location"] = location;
    String json;
    serializeJson(doc, json);
    if (client.publish(publishTopic, json.c_str())) {
      Serial.print("Published: ");
      Serial.println(json);
    } else {
      Serial.println("MQTT publish failed");
    }
  }
}

void loop() 
{
  // put your main code here, to run repeatedly:
  maintainConnection();
  if (client.connected()) {
    client.loop();
  }
  unsigned long now = millis();
  if (now - lastLedChange >= 1000) {
    lastLedChange = now;
    ledOn = !ledOn;
    digitalWrite(LED_PIN, ledOn ? HIGH : LOW);
  }
  if (now - lastMeasurement >= 2000) {
    lastMeasurement = now;
    measureTemp();
  }

}

