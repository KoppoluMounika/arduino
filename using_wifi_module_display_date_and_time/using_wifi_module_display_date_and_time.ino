#include <SPI.h>
#include <SD.h>
#include <SoftwareSerial.h>

SoftwareSerial esp(8, 9);                           // RX, TX for ESP-01

// Ultrasonic pins
const int trigPin = 2;
const int echoPin = 3;

// SD card CS
const int chipSelect = 10;

// RGB LED pins
const int redPin = 6;
const int greenPin = 5;
const int bluePin = 4;

// WiFi credentials
String ssid = "BITSILICA_1";
String password = "cepybdmv";

// Variables
long duration;
int distance;
bool objectPresent = false;
File logFile;

void setup() {
  Serial.begin(9600);                                   // Serial Monitor
  esp.begin(115200);                                    // ESP-01 baud

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

  // Connect ESP to WiFi
  sendESPCommand("AT+RST", 2000);
  sendESPCommand("AT+CWMODE=1", 1000);
  sendESPCommand("AT+CWJAP=\"" + ssid + "\",\"" + password + "\"", 5000);
  Serial.println("ESP connected to WiFi.");
}

void loop() {
  // Read Ultrasonic distance
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  duration = pulseIn(echoPin, HIGH, 30000);
  distance = duration * 0.034 / 2;

  String currentTime = getTimeFromESP();                  // Fetch real time string

  // Object detection
  if (distance > 0 && distance < 15 && !objectPresent) {
    objectPresent = true;
    logEvent("ENTERED", distance, currentTime);
  } 
  else if ((distance >= 15 || distance == 0) && objectPresent) {
    objectPresent = false;
    logEvent("EXITED", distance, currentTime);
  }

  // RGB LED blink based on distance
  blinkRGB(distance);

  delay(500);
}

void sendESPCommand(String cmd, int waitTime) {
  esp.println(cmd);
  long start = millis();
  while ((millis() - start) < waitTime) {
    while (esp.available()) {
      char c = esp.read();
      Serial.write(c);                       // Print ESP response to Serial Monitor
    }
  }
}

// Dummy time function
String getTimeFromESP() {
  return "2025-08-28 14:23:51";
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

// RGB LED blink based on distance
void blinkRGB(int dist) {
  if (dist > 0 && dist < 7) {
                                                // Near -- Red blink
    digitalWrite(redPin, HIGH);
    digitalWrite(greenPin, LOW);
    digitalWrite(bluePin, LOW);
  }
  else if (dist >= 7 && dist <= 15) {
                                                // Medium -- Blue blink
    digitalWrite(redPin, LOW);
    digitalWrite(greenPin, LOW);
    digitalWrite(bluePin, HIGH);
  }
  else if (dist > 15) {
                                                // Far -- Green blink
    digitalWrite(redPin, LOW);
    digitalWrite(greenPin, HIGH);
    digitalWrite(bluePin, LOW);
  }
  else {
                                                // Turn off LED if no object detected
    digitalWrite(redPin, LOW);
    digitalWrite(greenPin, LOW);
    digitalWrite(bluePin, LOW);
  }
}
