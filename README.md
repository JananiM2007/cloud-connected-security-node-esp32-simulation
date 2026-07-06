# Cloud Connected Security Node

## Overview

This project demonstrates a cloud-connected IoT security node using an ESP32 and an HC-SR04 ultrasonic sensor. The ESP32 continuously measures the distance to nearby objects and publishes the sensor data to Adafruit IO using the MQTT protocol for real-time cloud monitoring.

## Features

- Real-time distance measurement
- Wi-Fi connectivity using ESP32
- MQTT communication
- Cloud monitoring with Adafruit IO
- LED indication when an object is detected within a threshold
- Developed and tested using the Wokwi simulator

---

## Components Used

- ESP32 Development Board
- HC-SR04 Ultrasonic Sensor
- LED
- 220Ω Resistor
- Jumper Wires

---

## Software Used

- Arduino IDE
- Wokwi Simulator
- Adafruit IO
- MQTT Protocol

---

## Circuit Connections

| HC-SR04 | ESP32 |
|---------|-------|
| VCC | 5V |
| GND | GND |
| TRIG | GPIO 5 |
| ECHO | GPIO 18 |

| LED | ESP32 |
|------|-------|
| Anode | GPIO 2 (through 220Ω resistor) |
| Cathode | GND |

---

## Working Principle

1. The ESP32 connects to the Wi-Fi network.
2. It establishes an MQTT connection with Adafruit IO.
3. The HC-SR04 measures the distance to nearby objects.
4. If the object is within the threshold distance, the LED turns ON.
5. The measured distance is published to the Adafruit IO cloud dashboard every few seconds.

---

## Technologies Used

- ESP32
- Arduino C++
- MQTT
- Adafruit IO
- Wokwi Simulator

---


## Future Improvements

- Buzzer alerts
- Push notifications
- Mobile application integration
- Multiple sensor support
- Data logging and analytics

---

## Author

**Janani M**
