#include <SD.h>
#include <SPI.h>

// Ultrasonic sensor pins
const int trigPin = 2;
const int echoPin = 3;

// RGB LED pins
const int redPin   = 8;
const int greenPin = 9;
const int bluePin  = 10;

// SD card chip select pin
const int chipSelect = 4;

// Variables
long duration;
int distance;
bool objectPresent = false;

void setup() {
  Serial.begin(9600);

  // Setup pins
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);

  // Initialize SD card
  if (!SD.begin(chipSelect)) {
    Serial.println("SD card initialization failed!");
    while (1); // Halt if SD card not found
  }
  Serial.println("SD card initialized.");
  logEvent("System started");
}

void loop() {
  distance = getDistance();

  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" cm");

  // RGB LED color based on distance
  if (distance > 0 && distance <= 15) {
    setColor(255, 0, 0); // Red - close
  } else if (distance > 15 && distance <= 40) {
    setColor(0, 0, 255); // Blue - medium
  } else if (distance > 40 && distance < 100) {
    setColor(0, 255, 0); // Green - far
  } else {
    setColor(0, 0, 0);   // Off - out of range
  }

  // Log entry/exit events
  if (distance > 0 && distance < 100) {
    if (!objectPresent) {
      logEvent("Object ENTERED at distance " + String(distance) + " cm");
      objectPresent = true;
    }
  } else {
    if (objectPresent) {
      logEvent("Object EXITED");
      objectPresent = false;
    }
  }

  delay(500);
}

// Function to get distance from ultrasonic sensor
int getDistance() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);

  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  // Wait for echo, timeout at 30 ms (30000 us)
  duration = pulseIn(echoPin, HIGH, 30000);

  // If no echo received, duration will be 0
  if (duration == 0) {
    return -1; // no object detected
  }

  // Calculate distance in cm
  int dist = duration * 0.034 / 2;
  return dist;
}

// Function to set RGB LED color (values 0-255)
void setColor(int r, int g, int b) {
  analogWrite(redPin, r);
  analogWrite(greenPin, g);
  analogWrite(bluePin, b);
}

// Function to log text to SD card with timestamp (millis)
void logEvent(String text) {
  File logFile = SD.open("log.txt", FILE_WRITE);
  if (logFile) {
    logFile.print("[");
    logFile.print(millis());
    logFile.print(" ms] ");
    logFile.println(text);
    logFile.close();
    Serial.print("Logged: ");
    Serial.println(text);
  } else {
    Serial.println("Error opening log.txt");
  }
}
