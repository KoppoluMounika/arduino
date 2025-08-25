int redLed=9;              //red led is conected to pin 9
int greenLed=8;			   //green led is connected to pin 8
int val;
int photoPin=A1;		   //photoresistor is connected to analog pin A1
void setup()
{
  Serial.begin(9600);
  pinMode(redLed,OUTPUT);
  pinMode(greenLed,OUTPUT);
  pinMode(photoPin,OUTPUT);
}
void loop()
{
  val=analogRead(A1);	   //taking reading from the photoresistor	
  Serial.println(val);
  if(val>=0 && val<=250)   //if intensity lessthan 250 the green led will on
  {
    digitalWrite(greenLed,HIGH);
    digitalWrite(redLed,LOW);
  }
  delay(1000);
  if(val>250)				//if inetensity is greterthan 250,the red led will on
  {
    digitalWrite(redLed,HIGH);
    digitalWrite(greenLed,LOW);
  }
  delay(1000);
}