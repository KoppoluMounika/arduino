/*by using while blink the led with certain range 
that wiill be moniter by using potentiometer
*/

int potPin=A1;//the potentiometr will be connected to A1 for reading input
int redPin=9;//led connected to pin 9 for output.
int potVal;
void setup()
{
  pinMode(potPin, INPUT);
  pinMode(redPin,OUTPUT);
}

void loop()
{
  potVal=analogRead(potPin);
  //if read the input from potPin if it is geterthan 100 the led is on
 while(potVal>100){
  digitalWrite(redPin, HIGH);
   potVal=analogRead(potPin);
  delay(1000); // Wait for 1000 millisecond(s)
  
 }
  //if potvalue will be lessthan 100 the led is off. 
 digitalWrite(redPin, LOW);
  delay(1000); // Wait for 1000 millisecond(s)
}