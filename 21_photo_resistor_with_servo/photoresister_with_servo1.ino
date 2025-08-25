
#include <Servo.h>

Servo ser;                  // Create servo object
int light;

void setup()
{
  ser.attach(12);           // Attach servo signal pin to D12
  pinMode(A1, INPUT);
}

void loop()
{
  light = analogRead(A1);   // Read LDR or sensor value

  if(light >= 200 && light < 350)
  {
    ser.write(0);           // Move to 0 degrees
    delay(1000);
    ser.write(90);          // Move to 90 degrees
    delay(1000);
  }
  else if(light >= 350 && light < 450)
  {
    ser.write(0);
    delay(1000);
    ser.write(180);         // Move to 180 degrees
    delay(1000);
  }
  else if(light >= 450)
  {
    ser.write(0);
    delay(1000);
    ser.write(180);         // Max servo angle is 180
    delay(1000);
  }
} 
