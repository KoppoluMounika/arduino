#include <LiquidCrystal.h>//load the liquird crystal library
LiquidCrystal LCD{10,9,5,4,3,2};

int trigPin=13;//connect sensor trig pin to arduino pin 13
int echoPin=11;//connect sensor echo pin to arduino pin 11
float pingTime;//declare a variable for measured ping time
float targetDistance;
float speedOfSound=776.5;//speed of sound in miles per hour
void setup()
{
  Serial.begin(9600);//turn on serial moniter
  pinMode(trigPin,OUTPUT);//set the trigger pin to be an output
  pinMode(echoPin,INPUT);//set echo pin is to be input
  
  LCD.begin(16,2);//turn on the lcd and tell arduino how big it is.
  LCD.setCursor(0,0);//puts cirser in upper left corner of display
  LCD.print("target distance: ");//ptiny first row
  
  
}

void loop()
{
  digitalWrite(trigPin,LOW);//set the trigger pin low
  delayMicroseconds(2000);//delay 2000 microseconds
  digitalWrite(trigPin,HIGH);//trig pin high
  delayMicroseconds(15);//delay 15 microseconds
  digitalWrite(trigPin,LOW);//trig pin low
  delayMicroseconds(10);//delay 2000 microseconds
  
  pingTime=pulseIn(echoPin,HIGH);//measure pin time
  pingTime = pingTime/1000000.;//converts microseconds to seconds
  pingTime = pingTime/3600.;//converts seconds to hours
  targetDistance=speedOfSound * pingTime;//measure distance travelled by the ping
  targetDistance=targetDistance/2;
  targetDistance=targetDistance*63360;//miles converted into inches
  
  LCD.setCursor(0,1);//set curseor to first row second column
  LCD.print("                ");//clear row two
  LCD.setCursor(0,1);
  LCD.print(targetDistance);
  LCD.print(" inches");//print units
  delay(250);
  
  
}