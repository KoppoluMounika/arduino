/* based on the user input to chage the direction of servo */

#include <Servo.h>
int servoPin=9;					//pin 9 is connected to servo
int servoPos=180;				//initially the servo position is 180 degrees
int pos = 0;
Servo myServo;
void setup()
{
  Serial.begin(9600);
  myServo.attach(servoPin);
}

void loop()
{												//taking input from thye user
  Serial.println("what angle for the servo?");
  while(Serial.available()==0){
  }
  servoPos=Serial.parseInt();
  myServo.write(servoPos);
}