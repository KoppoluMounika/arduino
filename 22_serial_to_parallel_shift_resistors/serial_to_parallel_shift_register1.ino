int latchPin=11;
int clockPin=9;
int dataPin=12;

byte LEDs=0x88;

void setup()
{
  pinMode(latchPin, OUTPUT);
  pinMode(dataPin, OUTPUT);
  pinMode(clockPin, OUTPUT);
  Serial.begin(9600);
}

void loop()
{
  digitalWrite(latchPin, LOW);
  shiftOut(dataPin,clockPin,LSBFIRST,LEDs);
  digitalWrite(latchPin,HIGH);
  
}