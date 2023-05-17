#include <BlynkSimpleEsp32.h>
#include <Ultrasonic.h>

// Ultrasonic sensor
const int trigPin = 12;
const int echoPin = 13;
Ultrasonic ultrasonic(trigPin, echoPin);

// PIR sensor
const int pirPin = 2;

// Buzzer
const int buzzerPin = 14;

// Blynk settings
char auth[] = "YOUR_AUTH_TOKEN";

void setup() {
  // Initialize the serial port
  Serial.begin(115200);

  // Initialize the ultrasonic sensor
  ultrasonic.begin();

  // Initialize the PIR sensor
  pinMode(pirPin, INPUT);

  // Initialize the buzzer
  pinMode(buzzerPin, OUTPUT);

  // Connect to Blynk
  Blynk.begin(auth, "YOUR_WIFI_SSID", "YOUR_WIFI_PASSWORD");
}

void loop() {
  // Read the ultrasonic sensor
  long distance = ultrasonic.read();

  // Read the PIR sensor
  int pirState = digitalRead(pirPin);

  // If the ultrasonic sensor detects an object within 50 cm, send a notification to Blynk
  if (distance < 50) {
    Blynk.notify("Motion detected!");
  }

  // If the PIR sensor detects movement, trigger the buzzer
  if (pirState == HIGH) {
    digitalWrite(buzzerPin, HIGH);
  } else {
    digitalWrite(buzzerPin, LOW);
  }

  // Update Blynk
  Blynk.run();
}