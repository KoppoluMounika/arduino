/* using push button how to toggle the switch*/
int ledState=0;           			//initially the ledstate is 0
int ledPin=8;						//pin 8 is connected to 8
int buttonPin=12;					//pin 12 is connected to button
int buttonNew;
int buttonOld=1;
void setup()
{
  Serial.begin(9600);
  pinMode(ledPin, OUTPUT);
  pinMode(buttonPin, INPUT);
}

void loop()
{
  buttonNew=digitalRead(buttonPin);
  if(buttonOld==0 && buttonNew==1){
    if(ledState==0){				//if led state is 0 led will blink
      digitalWrite(ledPin,HIGH);
      ledState=1;
    }
    else{
      digitalWrite(ledPin,LOW);		//else led will unblink
      ledState=0;
    }
    
  }
  buttonOld=buttonNew;
}