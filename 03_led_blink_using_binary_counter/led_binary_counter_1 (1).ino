//four pins are used for bainary counter
int pin1=9;
int pin2=10;
int pin3=11;
int pin4=12;
void setup()
{
  pinMode(9, OUTPUT);
  pinMode(10, OUTPUT);
  pinMode(11, OUTPUT);
  pinMode(12, OUTPUT);
}

void loop()
{
  while(1)
  {	//if 0001 means first led will on like the way if 1 will on
    //0 means off.
    for(int i=0;i<16;i++)
    {
      if((i>>0)&1)
      {
        digitalWrite(9,HIGH);
      }
       if((i>>1)&1)
      {
        digitalWrite(10,HIGH);
      }
       if((i>>2)&1)
      {
        digitalWrite(11,HIGH);
      }
       if((i>>3)&1)
      {
        digitalWrite(12,HIGH);
      }
      delay(1000);//after every blink 1 sec delay  
      digitalWrite(9,LOW);
      digitalWrite(10,LOW);
      digitalWrite(11,LOW);
      digitalWrite(12,LOW);

    }
  }
    
}