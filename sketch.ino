/*
=============================================
DecodeLabs Project 3
ESP32 + HC-SR04 + LED + Adafruit IO MQTT
=============================================
*/

#include <WiFi.h>
#include <PubSubClient.h>

// ---------------- WiFi ----------------
const char* ssid = "Wokwi-GUEST";
const char* password = "";

// ------------ Adafruit IO -------------
#define AIO_SERVER      "io.adafruit.com"
#define AIO_PORT        1883

#define AIO_USERNAME    "Jan1"
#define AIO_KEY         "aio_MHLM34JHji0czn00WnAasRvZvb0k"

// ------------ Pins --------------------
#define TRIG_PIN 5
#define ECHO_PIN 18
#define LED_PIN 2

const float THRESHOLD = 30.0;

// ------------ MQTT --------------------
WiFiClient wifiClient;
PubSubClient client(wifiClient);

unsigned long lastPublish = 0;

void connectWiFi() {

  if (WiFi.status() == WL_CONNECTED)
    return;

  Serial.print("Connecting to WiFi");

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }

  Serial.println();
  Serial.println("WiFi Connected");
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());
}

void connectMQTT() {

  while (!client.connected()) {

    Serial.print("Connecting to Adafruit IO...");

    String clientId = "ESP32-";
    clientId += String(random(0xffff), HEX);

    if (client.connect(clientId.c_str(), AIO_USERNAME, AIO_KEY)) {

      Serial.println("Connected!");

    } else {

      Serial.print("Failed. MQTT State = ");
      Serial.println(client.state());

      delay(3000);
    }
  }
}

float readDistance() {

  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);

  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);

  digitalWrite(TRIG_PIN, LOW);

  long duration = pulseIn(ECHO_PIN, HIGH, 30000);

  if (duration == 0)
    return -1;

  return duration * 0.0343 / 2.0;
}

void setup() {

  Serial.begin(115200);

  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  pinMode(LED_PIN, OUTPUT);

  client.setServer(AIO_SERVER, AIO_PORT);

  connectWiFi();
}

void loop() {

  connectWiFi();

  if (!client.connected())
    connectMQTT();

  client.loop();

  if (millis() - lastPublish >= 2000) {

    lastPublish = millis();

    float distance = readDistance();

    if (distance < 0) {
      Serial.println("Sensor Timeout");
      return;
    }

    digitalWrite(LED_PIN, distance <= THRESHOLD);

    Serial.print("Distance: ");
    Serial.print(distance);
    Serial.println(" cm");

    char payload[15];
    dtostrf(distance, 6, 2, payload);

    bool ok = client.publish(
      AIO_USERNAME "/feeds/distance",
      payload
    );

    if (ok) {
      Serial.print("Published: ");
      Serial.println(payload);
    } else {
      Serial.print("Publish Failed. MQTT State = ");
      Serial.println(client.state());
    }

    Serial.println("-----------------------");
  }
}