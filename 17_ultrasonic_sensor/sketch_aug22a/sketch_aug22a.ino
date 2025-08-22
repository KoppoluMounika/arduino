#define  trigPin 9    //trig pin connected to pin 9
#define   echoPin 10    //echo pin is connected pin 10
#define ledPin 13    // led pin is connected to pin 13

long duration;
int distance;

void setup() {
  pinMode(trigPin,OUTPUT);
  pinMode(echoPin,INPUT);
  pinMode(ledPin, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  // Send ultrasonic pulse
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  // Measure echo
  duration = pulseIn(echoPin, HIGH);
  distance = duration * 0.0343 / 2;              // Convert to cm

  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" cm");
  if (distance < 2 || distance > 440) {
                                              // Out of range  LED off
    analogWrite(ledPin, 0);
  }

  else if (distance>=2 && distance <= 10) {
                                              //led blink fast and intensity is high 
    analogWrite(ledPin, 255);
    digitalWrite(ledPin, HIGH);
    delay(600);                              
    digitalWrite(ledPin, LOW);
    delay(600);
  }
  else if (distance > 10 && distance <= 20) {
                                            // led blink decrease and intensity medium
    analogWrite(ledPin, 170);
    digitalWrite(ledPin, HIGH);
    delay(300);
    digitalWrite(ledPin, LOW);
    delay(300);
  }
  else if (distance>20 && distance <= 34) {
                                          // led blink high and intensity very high
    analogWrite(ledPin, 100);
    digitalWrite(ledPin, HIGH);
    delay(100);
    digitalWrite(ledPin, LOW);
    delay(100);
  }
  
}

