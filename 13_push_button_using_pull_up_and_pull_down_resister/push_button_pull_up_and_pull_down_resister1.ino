/*by using push button we cam on and off the led */

int ledPin=8;                      //pin 8 is connected to ledpin
int buttonPin=12;				   //pin 12 connected to push button
int buttonRead;

void setup()
{
  Serial.begin(9600);
  pinMode(ledPin, OUTPUT);
  pinMode(buttonPin, INPUT);
}

void loop()
{
  buttonRead=digitalRead(buttonPin);
  Serial.println(buttonRead);
  delay(250);				
  if(buttonRead==1){			//if button not pressed
    digitalWrite(ledPin,LOW);
  }
  if(buttonRead==0){			//button pressed
    digitalWrite(ledPin,HIGH);
  }
  
}