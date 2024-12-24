#include <Adafruit_Fingerprint.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <Servo.h>

Adafruit_Fingerprint finger = Adafruit_Fingerprint(&Serial1);
Servo myServo;
#define BUZZER_PIN 3
#define SERVO_PIN 9
#define TRIG_PIN 5
#define ECHO_PIN 6
LiquidCrystal_I2C lcd(0x27, 16, 2);

// Melody for access alert
int melody[] = {
  262, 294, 330, 349, 392, 440, 494, 523
};

int noteDurations[] = {
  4, 4, 4, 4, 4, 4, 4, 2
};

void setup() {
  Serial.begin(9600);
  Serial.println("Initializing...");

  Serial1.begin(57600);
  if (finger.verifyPassword()) {
    Serial.println("Fingerprint sensor detected.");
  } else {
    Serial.println("Fingerprint sensor not detected or wrong password.");
    while (1)
      ;
  }
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  myServo.attach(SERVO_PIN);
  myServo.write(0);
  pinMode(BUZZER_PIN, OUTPUT);
  digitalWrite(BUZZER_PIN, LOW);
  lcd.init();
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("Smart Home");
  lcd.setCursor(0, 1);
  lcd.print("Place Finger");
}

void loop() {
  lcd.setCursor(0, 0);
  lcd.print("Smart Home");
  lcd.setCursor(0, 1);
  lcd.print("Place Finger");

  int fingerprintID = getFingerPrint();
  if (fingerprintID != -1) {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("ID: ");
    lcd.print(fingerprintID);
    lcd.setCursor(0, 1);
    lcd.print("Access Granted");
    myServo.write(90);
    playMelody();  // Play the alert melody for fingerprint scan
    delay(2000);   // Show message for 5 seconds
    myServo.write(0);
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Smart Home");
    lcd.setCursor(0, 1);
    lcd.print("Place Finger");
  }

  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);

  long duration = pulseIn(ECHO_PIN, HIGH);
  int distance = duration * 0.034 / 2;
  if (distance < 26 && distance > 0) {
    Serial.print("Distance: ");
    Serial.print(distance);
    Serial.println(" cm Stop!!!!!!!!");
    for (int i = 0; i < 3; i++) {
      digitalWrite(BUZZER_PIN, HIGH);
      delay(200);
      digitalWrite(BUZZER_PIN, LOW);
      delay(200);
    }
  }
  delay(500);
}

int getFingerPrint() {
  int p = finger.getImage();
  if (p != FINGERPRINT_OK) return -1;

  p = finger.image2Tz();
  if (p != FINGERPRINT_OK) return -1;

  p = finger.fingerFastSearch();
  if (p != FINGERPRINT_OK) return -1;

  return finger.fingerID;
}

void playMelody() {
  // Play the fingerprint access melody
  for (int thisNote = 0; thisNote < 8; thisNote++) {
    int noteDuration = 1000 / noteDurations[thisNote];
    tone(BUZZER_PIN, melody[thisNote], noteDuration);
    
    int pauseBetweenNotes = noteDuration * 1.30;
    delay(pauseBetweenNotes);

    noTone(BUZZER_PIN);
  }
}
