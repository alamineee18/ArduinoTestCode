#include <Servo.h>

Servo myservo;
int i;

void setup()
{
  myservo.attach(9);
}

void loop()
{
  for(i=0; i<=180;i++)
  {
    myservo.write(i);
    delay(50);  
  }
}
