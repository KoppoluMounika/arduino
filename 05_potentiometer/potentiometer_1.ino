/* by using potentiometer how to blink led,if potentiometer 
voltage is greter than 4 volts then only the led blink otherwise the led unblink.
*/
int myPin=A2;
int readVal;
float V2;
int dt=250;
int redPin=9;
void setup()
{
  Serial.begin(9600);
  pinMode(myPin,INPUT);//a2 is input pin.
  pinMode(redPin,OUTPUT);//9 is output pin
}

void loop()
{
  readVal=analogRead(myPin);
  V2=(5./1023.)*readVal;
  Serial.println(V2);
  //if voltage is geterthan 4 volen led blink.
  if (V2>4.0){
    digitalWrite(redPin,HIGH);
    
  }
  //if voltage is lessthan 4 voles the led unblink.
  if (V2<4.0){
    digitalWrite(redPin,LOW);
  }
               
   delay(dt);
                 
}