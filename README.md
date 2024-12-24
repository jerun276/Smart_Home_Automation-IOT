# Smart Home Automation System

Welcome to the Smart Home Automation System project! This repository contains the code and documentation for a feature-rich IoT project that automates various aspects of home control, offering convenience, security, and energy efficiency.

---

## Features
- **Device Control:** Remotely control lights, fans, and other appliances.
- **Sensors Integration:**
  - DHT11 Sensor for temperature and humidity monitoring.
  - Ultrasonic Sensor for distance measurement.
  - IR Sensor for door lock status monitoring.
  - Sound Sensor for sound detection.
- **Security Enhancements:**
  - Fingerprint authentication using the R307 Fingerprint Reader Sensor.
  - Solenoid Door Lock integration for smart locking.
- **Wireless Connectivity:**
  - ESP8266 WiFi module for remote operation via the Blynk application.
  - **Relay Module:** Four-channel relay module for controlling multiple devices.
  - **Expandability:** Compatible with additional sensors like the Soil Humidity Sensor.

---

## Components
- **Microcontrollers:** Arduino Uno and Arduino Mega
- **Sensors:**
  - DHT11 (Temperature & Humidity)
  - Ultrasonic Sensor (HC-SR04)
  - IR Sensor
  - Sound Detection MIC
- **Modules:**
  - ESP8266 ESP-01S WiFi Module
  - 4-Channel Relay Module
- **Security Features:**
  - R307 Fingerprint Reader Sensor
  - Solenoid Door Lock (12VDC)
- **Additional Components:**
  - Analog Servo Motor (ES08MA-II)
  - MB-102 Breadboard

---

## Architecture
This project integrates various sensors and modules with the Arduino platform to create an interactive smart home system. The ESP8266 module handles communication with the Blynk app for remote control, while the relay module facilitates the switching of electrical appliances.

---

### Prerequisites
- Arduino IDE
- Blynk App
- Components listed above

## Author
- **Jerun Kingston**

For questions or feedback, feel free to reach out!

