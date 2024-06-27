#include <Servo.h>

Servo myservo;  // Create a servo object to control the servo motor
int i, j;

void setup() {
  myservo.attach(9);  // The servo signal pin is connected to digital pin 9
}

void loop() {
  
  for (i=120; i<=150; i++){
  myservo.write(i); 
  delay(100); 
  }
  delay(1000);
  for (i=150; i>=120; --i){
  myservo.write(i); 
  delay(100); 
  }

}
