#include <SPI.h>
#include <SD.h>
#include <SoftwareSerial.h>

SoftwareSerial esp(8, 9);   // RX, TX for ESP-01

// Ultrasonic pins
const int trigPin = 2;
const int echoPin = 3;

// SD card CS pin
const int chipSelect = 10;

// RGB LED pins
const int redPin = 6;
const int greenPin = 5;
const int bluePin = 4;

// WiFi credentials
String ssid = "Mounika";
String password = "Mounika@1";

// Variables
long duration;
int distance;
bool objectPresent = false;
File logFile;

void setup() {
  Serial.begin(9600);     
  esp.begin(115200);      // ESP-01 default baud rate

  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);

  // Initialize SD
  if (!SD.begin(chipSelect)) {
    Serial.println("SD init failed!");
    while (1);
  }
  Serial.println("SD card ready.");

  // Reset ESP
  sendESPCommand("AT+RST", 2000);
  sendESPCommand("ATE0", 1000); // echo off

  // Set WiFi mode = STA
  sendESPCommand("AT+CWMODE=1", 1000);

  // Join WiFi
  sendESPCommand("AT+CWJAP=\"" + ssid + "\",\"" + password + "\"", 8000);

  // Check IP
  sendESPCommand("AT+CIFSR", 2000);
  Serial.println("ESP WiFi init complete.");
}

void loop() {
  // Measure ultrasonic distance
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  duration = pulseIn(echoPin, HIGH, 30000);
  distance = duration * 0.034 / 2;

  String currentTime = getTimeFromAPI();   // Get current time

  if (distance > 0 && distance < 15 && !objectPresent) {
    objectPresent = true;
    logEvent("ENTERED", distance, currentTime);
  } 
  else if ((distance >= 15 || distance == 0) && objectPresent) {
    objectPresent = false;
    logEvent("EXITED", distance, currentTime);
  }

  blinkRGB(distance);
  delay(1000);
}

// ---- Functions ----
void sendESPCommand(String cmd, int waitTime) {
  esp.println(cmd);
  long start = millis();
  while ((millis() - start) < waitTime) {
    while (esp.available()) {
      char c = esp.read();
      Serial.write(c);   // Print ESP response
    }
  }
}

// Get time from worldtimeapi.org
String getTimeFromAPI() {
  String response = "";
  sendESPCommand("AT+CIPSTART=\"TCP\",\"worldtimeapi.org\",80", 4000);
  esp.println("AT+CIPSEND=75");   // Length of HTTP GET below
  delay(100);
  esp.print("GET /api/timezone/Asia/Kolkata HTTP/1.1\r\nHost: worldtimeapi.org\r\n\r\n");

  long start = millis();
  while ((millis() - start) < 4000) {
    while (esp.available()) {
      char c = esp.read();
      response += c;
    }
  }
  sendESPCommand("AT+CIPCLOSE", 1000);

  // Extract datetime
  int idx = response.indexOf("\"datetime\":\"");
  if (idx != -1) {
    String dateStr = response.substring(idx + 12, idx + 31); // 2025-08-29T10:21:35
    return dateStr;
  }
  return "TIME_ERR";
}

void logEvent(String eventType, int dist, String timeStr) {
  String logMsg = "[" + timeStr + "] Object " + eventType + " at " + String(dist) + " cm";
  Serial.println(logMsg);

  logFile = SD.open("log.txt", FILE_WRITE);
  if (logFile) {
    logFile.println(logMsg);
    logFile.close();
  } else {
    Serial.println("Error writing to log.txt");
  }
}

// RGB LED indication
void blinkRGB(int dist) {
  if (dist > 0 && dist < 7) {
    digitalWrite(redPin, HIGH);
    digitalWrite(greenPin, LOW);
    digitalWrite(bluePin, LOW);
  } else if (dist >= 7 && dist <= 15) {
    digitalWrite(redPin, LOW);
    digitalWrite(greenPin, LOW);
    digitalWrite(bluePin, HIGH);
  } else if (dist > 15) {
    digitalWrite(redPin, LOW);
    digitalWrite(greenPin, HIGH);
    digitalWrite(bluePin, LOW);
  } else {
    digitalWrite(redPin, LOW);
    digitalWrite(greenPin, LOW);
    digitalWrite(bluePin, LOW);
  }
}
