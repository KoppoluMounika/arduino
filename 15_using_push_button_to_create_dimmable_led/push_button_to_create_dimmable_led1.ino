/* using push button to create a dimmable led */
int buttonPin1=10;    			         //button one is connected to pin 10
int buttonPin2=11;						 //button two connected to pin 11
int buttonVal1;
int buttonVal2;
int ledPin=9;							//led is connected to pin 9
int ledBright=0;
void setup(){
  Serial.begin(9600);
  pinMode(buttonPin1, INPUT);
  pinMode(buttonPin2, INPUT);
  pinMode(ledPin,OUTPUT);
}

void loop()
{										//taking inputs from the buttons wether it is push or not
  buttonVal1=digitalRead(buttonPin1);
  buttonVal2=digitalRead(buttonPin2);
  Serial.print("Button 1 = ");
  Serial.print(buttonVal1);
  Serial.print(", ");
  Serial.print("Button 2 = ");
  Serial.println(buttonVal2);
  delay(250);
  if(buttonVal1==0){					//if button one push it increase the intensity level +5volts
    ledBright=ledBright+5;
  }
  if(buttonVal2==0){					//if button two push it decrease the intensity level -5volts
    ledBright=ledBright-5;
  }
  if(ledBright>255){
    ledBright=255;
  }
  if(ledBright<0){
    ledBright=0;
  }
  analogWrite(ledPin,ledBright);
}