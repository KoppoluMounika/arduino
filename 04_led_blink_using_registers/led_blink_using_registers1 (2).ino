void setup()
{
  pinMode(13, OUTPUT);//pin 13 is connected to the led in breadboard.
}

void loop()
{
  digitalWrite(13, HIGH);//led blink
  delay(500); 
  digitalWrite(13, LOW);//led unblink
  delay(100); 
}