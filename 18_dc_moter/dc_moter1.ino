int LED_RINCON_1=8;             //dc moter terminal one is connected to pin 8
int LED_RINCON_2=9;             //dc moter terminal two is connected to pin p

void setup()
{
  pinMode(LED_RINCON_1, OUTPUT);
  pinMode(LED_RINCON_2, OUTPUT); 
  
}

void loop()
{
  digitalWrite(LED_RINCON_1, HIGH);
  delay(1000);
  digitalWrite(LED_RINCON_2,LOW);
  delay(1000);
  digitalWrite(LED_RINCON_2,HIGH);
  delay(1000); // Wait for 1000 millisecond(s)
  digitalWrite(LED_RINCON_1,LOW);
  delay(1000); // Wait for 1000 millisecond(s)
}