//taking the user input led will be blinks
int ledBlinks;//user input for no of times the led blinks
int redPin=12;//led is connected to pin 12.
String msg="enter how many times led blinks:";
void setup()
{
  Serial.begin(9600);
  pinMode(redPin, OUTPUT);
}

void loop()
{
  Serial.println(msg);
  ledBlinks=Serial.parseInt();//taking input from the user.
  for(int i=0;i<ledBlinks;i++){
    digitalWrite(redPin,HIGH);
    delay(500);
    digitalWrite(redPin,LOW);
    delay(500);
  }
}