/*by using potentiometer to change the intensity of led.
rotate the potentiometer nob the light intensity will be varied.
*/
int potPin=A1;//potentiometer terminal 1 min connected to A1;
int gPin=9;//resister is connected to pin 9
int potVal;
float LEDVal;
void setup()
{
  pinMode(potPin, INPUT);
  pinMode(gPin,OUTPUT);
  Serial.begin(9600);
}

void loop()
{
  //rotate the nop by changing the intensity of led.
  potVal=analogRead(potPin);
  LEDVal=(255./1023.)*potVal;
  analogWrite(gPin,LEDVal);
  Serial.println(LEDVal);
  
}