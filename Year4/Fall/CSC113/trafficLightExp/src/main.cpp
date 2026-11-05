#include <Arduino.h>
#include <WiFi.h>
#include <PubSubClient.h>
#include <cstring>

// ---------- CONFIGURATION ----------
const char* ssid = "Ryan's IPhone";
const char* password = "wigwomm87";
const char* mqtt_server = "broker.hivemq.com";
const int mqtt_port = 1883;

const char* lightTopic = "csc113/traffic/light/3";
const char* statusTopic = "csc113/traffic/light/status";

const int RED_PIN = 26;
const int YELLOW_PIN = 27;
const int GREEN_PIN = 25;

// -----------------------------------
WiFiClient espClient;
PubSubClient client(espClient);
String clientId;

void setLight(int pin) {
  digitalWrite(RED_PIN, LOW);
  digitalWrite(YELLOW_PIN, LOW);
  digitalWrite(GREEN_PIN, LOW);
  digitalWrite(pin, HIGH);
}

void callback(char* topic, byte* payload, unsigned int length) {
  if (strcmp(topic, lightTopic) != 0) return;

  Serial.println("-------new message from broker-----");
  Serial.printf("channel: %s\n", topic);
  Serial.print("data: ");
  Serial.write(payload, length);
  Serial.println();

  // MQTT payloads are not necessarily null-terminated.
  if (length == 3 && memcmp(payload, "RED", 3) == 0) {
    setLight(RED_PIN);
    Serial.println("Light: RED");
  } else if (length == 6 && memcmp(payload, "YELLOW", 6) == 0) {
    setLight(YELLOW_PIN);
    Serial.println("Light: YELLOW");
  } else if (length == 5 && memcmp(payload, "GREEN", 5) == 0) {
    setLight(GREEN_PIN);
    Serial.println("Light: GREEN");
  } else {
    Serial.println("Ignored unknown color command.");
  }
}

void setup_wifi() {
  delay(10);
  Serial.println();
  Serial.printf("Connecting to %s", ssid);
  WiFi.mode(WIFI_STA);
  WiFi.setAutoReconnect(true);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nWiFi connected!");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
}

void reconnect() {
  while (WiFi.status() == WL_CONNECTED && !client.connected()) {
    Serial.print("Attempting MQTT connection...");
    if (client.connect(clientId.c_str())) {
      Serial.println("connected.");
      if (client.subscribe(lightTopic)) {
        Serial.printf("Subscription requested: %s\n", lightTopic);
      } else {
        Serial.println("Subscription failed; retrying.");
        client.disconnect();
        delay(5000);
      }
    } else {
      Serial.print("failed, rc=");
      Serial.println(client.state());
      delay(5000);
    }
  }
}

void setup() {
  Serial.begin(9600);
  Serial.setTimeout(500);
  pinMode(RED_PIN, OUTPUT);
  pinMode(YELLOW_PIN, OUTPUT);
  pinMode(GREEN_PIN, OUTPUT);
  setLight(RED_PIN);

  setup_wifi();
  clientId = "ESP32_TrafficLight_3_" + WiFi.macAddress();
  client.setServer(mqtt_server, mqtt_port);
  client.setCallback(callback);
  reconnect();
}

void publishSerialData(const char* serialData) {
  if (!client.connected()) reconnect();

  if (client.publish(statusTopic, serialData)) {
    Serial.printf("Published to %s: %s\n", statusTopic, serialData);
  } else {
    Serial.println("Status publish failed.");
  }
}

void loop() {
  if (WiFi.status() != WL_CONNECTED) {
    setLight(RED_PIN);
    client.disconnect();
    delay(500);
    return;
  }

  if (!client.connected()) {
    setLight(RED_PIN);
    reconnect();
  }
  if (!client.loop()) setLight(RED_PIN);

  if (Serial.available()) {
    Serial.readStringUntil('\n');
    publishSerialData("CG Okay.");
  }
}
