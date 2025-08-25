int resPin=A1;             //the photoresistor pin is connected to pin A1
int light_val;
void setup()
{
  pinMode(resPin, OUTPUT);
  Serial.begin(9600);
}

void loop()
{
  light_val=analogRead(A1);	//taking reading from the use
  Serial.println(light_val);
  delay(1000);				//delay 100ms
}