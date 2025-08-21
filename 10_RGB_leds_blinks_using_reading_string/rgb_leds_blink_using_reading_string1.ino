//taking input from the user if based on user input that led will on.
String msg="what color LED?";
String mycolor;//user input
int redPin=12;//redled connected to pin12
int greenPin=11;//greenled connected to pin 11
int bluePin=10;//blue led connected to pin 10
void setup()
{
  Serial.begin(9600);
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);
}

void loop()
{
  Serial.println(msg);
  while(Serial.available()==0){
  }
  mycolor=Serial.readString();//reading user input
  //based on user input led blink
  if (mycolor=="red"){
  digitalWrite(redPin, HIGH);
  digitalWrite(greenPin, LOW);
  digitalWrite(bluePin, LOW);
  }
  
  if (mycolor=="green"){
  digitalWrite(redPin, LOW);
  digitalWrite(greenPin, HIGH);
  digitalWrite(bluePin, LOW);
  }
  
  if (mycolor=="blue"){
  digitalWrite(redPin, LOW);
  digitalWrite(greenPin, LOW);
  digitalWrite(bluePin, HIGH);
  }
  
}