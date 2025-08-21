//using for loop blink the leds no of times.
int redPin=9;//red led connected to pin9.
int yellowPin=10;//yellow led connected to pin 10
void setup()
{
  pinMode(redPin, OUTPUT);
  pinMode(yellowPin,OUTPUT);
}

void loop()
{
  //three times blink the yellow led.
  for(int i=0;i<3;i++){
  digitalWrite(yellowPin, HIGH);
  delay(1000); // Wait for 1000 millisecond(s)
  digitalWrite(yellowPin, LOW);
  delay(1000); // Wait for 1000 millisecond(s)
  }
  //five times blink the red led.
  for(int i=0;i<5;i++){
  digitalWrite(redPin, HIGH);
  delay(1000); // Wait for 1000 millisecond(s)
  digitalWrite(redPin, LOW);
  delay(1000); // Wait for 1000 millisecond(s)
  }
}