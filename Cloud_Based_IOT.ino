#define BLYNK_TEMPLATE_ID "**********"
#define BLYNK_TEMPLATE_NAME "FC Project"
#define BLYNK_AUTH_TOKEN "*********"

#define BLYNK_PRINT Serial
#define DHTTYPE DHT11
const int relayPin3 = 4;
const int soundSensorPin = 11;
int soundSensorValue = 0;

#include <ESP8266_Lib.h>
#include <BlynkSimpleShieldEsp8266.h>
#include <DHT.h>
#include <SoftwareSerial.h>

char ssid[] = "jk";
char pass[] = "00000000";

SoftwareSerial EspSerial(2, 3);
ESP8266 wifi(&EspSerial);
DHT dht(10, DHT11);
BlynkTimer timer;

void sendSensor() {
  float t = dht.readTemperature();
  if (t > 30) {
    digitalWrite(relayPin3, LOW);
  } else {
    digitalWrite(relayPin3, HIGH);
  }
  Blynk.virtualWrite(V1, t);
}

void setup() {
  Serial.begin(115200);
  pinMode(relayPin3, OUTPUT);
  pinMode(9, INPUT);
  pinMode(soundSensorPin, INPUT);
  digitalWrite(relayPin3, HIGH);
  EspSerial.begin(38400);
  delay(5);
  Blynk.begin(BLYNK_AUTH_TOKEN, wifi, ssid, pass, "blynk.cloud", 80);
  dht.begin();
  timer.setInterval(2000L, sendSensor);
}

void loop() {
  Blynk.run();
  timer.run();
  int irSensorValue = digitalRead(9);
  soundSensorValue = digitalRead(soundSensorPin);
  String status;
  if (irSensorValue == LOW) {
    status = "DOOR IS CLOSED";
    Blynk.virtualWrite(V3, status);
  } else {
    status = "DOOR IS OPENED";
    Blynk.virtualWrite(V3, status);
  }
  if (soundSensorValue == HIGH && irSensorValue == LOW) {
    Blynk.logEvent("door_alert", "Someone is Trying to unlock the Door!!!!!!!");
  }
}
