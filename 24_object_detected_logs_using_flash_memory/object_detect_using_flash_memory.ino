#include <SPI.h>
#include <SPIMemory.h>

// Ultrasonic sensor pins
const int trigPin = 2;
const int echoPin = 3;

// RGB LED pins
const int redPin   = 8;
const int greenPin = 9;
const int bluePin  = 10;

// W25Qxx Flash chip select pin
const int chipSelect = 4;

// Flash object
SPIFlash flash(chipSelect);  

long duration;
int distance;
bool objectPresent = false;
uint32_t logAddress = 0; // memory pointer

void setup() {
  Serial.begin(9600);

  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);

  // Initialize flash
  if (!flash.begin()) {
    Serial.println("Flash initialization failed!");
    while (1);
  }
  Serial.println("Flash initialized.");
  logEvent("System started");
}

void loop() {
  distance = getDistance();

  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" cm");

  if (distance > 0 && distance <= 15) {
    setColor(255, 0, 0); // Red - close
  } else if (distance > 15 && distance <= 40) {
    setColor(0, 0, 255); // Blue - medium
  } else if (distance > 40 && distance < 100) {
    setColor(0, 255, 0); // Green - far
  } else {
    setColor(0, 0, 0);   // Off - out of range
  }

  // Log entry/exit 
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

//to get distance from ultrasonic sensor
int getDistance() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);

  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  duration = pulseIn(echoPin, HIGH, 30000);

  if (duration == 0) return -1;

  return duration * 0.034 / 2;
}

//set RGB LED color
void setColor(int r, int g, int b) {
  analogWrite(redPin, r);
  analogWrite(greenPin, g);
  analogWrite(bluePin, b);
}

//log events into flash memory
void logEvent(String text) {
  String entry = "[" + String(millis()) + " ms] " + text + "\n";
  Serial.print("Logged: ");
  Serial.println(entry);

  // Write log entry into flash sequentially
  flash.writeStr(logAddress, entry);
  logAddress += entry.length();
}
