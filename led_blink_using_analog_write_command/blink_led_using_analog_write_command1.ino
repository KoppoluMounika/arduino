int redPin=9;
int bright=250;

void setup()
{
  pinMode(redPin, OUTPUT);
}

void loop()
{
  for(int i=0;i<bright;i++){
    analogWrite(redPin,i);
    delay(20);
  }
  for(int j=bright;j>=0;j--){
    analogWrite(redPin,j);
    delay(20);
  }
}