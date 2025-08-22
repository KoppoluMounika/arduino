//taking input from the user if based on user input that led will on.
String msg ="what color LED?";
String mycolor;//user input
int redPin=8;//redled connected to pin12
int greenPin=9;//greenled connected to pin 11
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
  
  if (mycolor=="yellow"){
  analogWrite(redPin, 255);
  analogWrite(greenPin, 100);
  analogWrite(bluePin, 0);
  }
  
  if (mycolor=="cyan"){
  analogWrite(redPin, 0);
  analogWrite(greenPin, 255);
  analogWrite(bluePin, 255);
  }
  
  if (mycolor=="megenta"){
  analogWrite(redPin, 255);
  analogWrite(greenPin, 0);
  analogWrite(bluePin, 255);
  }
}