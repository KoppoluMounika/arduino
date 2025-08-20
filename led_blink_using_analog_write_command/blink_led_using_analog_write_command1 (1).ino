int redPin=9;//by using redwire pin 9 connected to the resister.
int bright=250;//led intensity range.

void setup()
{
  pinMode(redPin, OUTPUT);
}

void loop()
{	
  //led intensity will be increased between 0-250.
  for(int i=0;i<bright;i++){
    analogWrite(redPin,i);
    delay(20);
  }
  //led intensity will be decresed between 250-0.
  for(int j=bright;j>=0;j--){
    analogWrite(redPin,j);
    delay(20);
  }
}