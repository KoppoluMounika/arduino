#include <SPI.h>
#include <SPIMemory.h>

// Ultrasonic sensor pins
const int trigPin = 2;
const int echoPin = 3;

// W25Qxx Flash chip select pin
const int chipSelect = 4;

// Flash object
SPIFlash flash(chipSelect);

long duration;
int distance;
bool objectPresent = false;
uint32_t logAddress = 0;    
bool logsPrinted = false;   

void setup() {
  Serial.begin(9600);

  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  if (!flash.begin()) {
    Serial.println("Flash initialization failed!");
    while (1);
  }
  Serial.println("Flash initialized.");

  // Clear old logs (erase first sector)
  flash.eraseSector(0);
  logAddress = 0;

  logEvent("System started");
}

void loop() {
  distance = getDistance();

  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" cm");

  // Logging object entry/exit
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

  if (distance > 20 && distance <= 40) {
    if (!logsPrinted) {
      readLogs();
      logsPrinted = true;
    }
  } else {
    logsPrinted = false;
  }

  delay(500);
}

// ultrasonic distance
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


void logEvent(String text) {
  String entry = "[" + String(millis()) + " ms] " + text + "\n";
  Serial.print("Logged: ");
  Serial.println(entry);

  for (unsigned int i = 0; i < entry.length(); i++) {
    flash.writeByte(logAddress++, entry[i]);
  }
}

// Read logs sequentially until logAddress
void readLogs() {
  Serial.println("\n--- Reading Logs from Flash ---");
  uint32_t addr = 0;
  char c;

  while (addr < logAddress) {
    c = flash.readByte(addr++);

    // Skip unprogrammed/erased bytes (0xFF)
    if (c == (char)0xFF) continue;

    Serial.print(c);
  }

  Serial.println("\n--- End of Logs ---");
}
