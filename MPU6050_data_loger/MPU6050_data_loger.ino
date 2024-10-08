#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
#include <Wire.h>
#include "MPUSetup.h"

void setup(void) {
  Serial.begin(115200);
  while (!Serial)
    delay(10);  // will pause Zero, Leonardo, etc until serial console opens

  Serial.println("Adafruit MPU6050 test!");

  // Try to initialize!
  if (!mpu.begin()) {
    Serial.println("Failed to find MPU6050 chip");
    while (1) {
      delay(10);
    }
  }
  Serial.println("MPU6050 Found!");
  mpuSetup();
  
  Serial.println("");
  delay(100);
  Serial.println("Acceleration data:");
  Serial.print("X axis");
  Serial.print(",");
  Serial.print("Y axis");
  Serial.print(",");
  Serial.println("Z axis");
}

void loop() {
  /* Get new sensor events with the readings */
  sensors_event_t a, g, temp;
  mpu.getEvent(&a, &g, &temp);

  /* Print out the values */
  //Serial.print("Acceleration X: ");
  Serial.print(a.acceleration.x);
  Serial.print(",");
  //Serial.print(", Y: ");
  Serial.print(a.acceleration.y);
  Serial.print(",");
  //Serial.print(", Z: ");
  Serial.println(a.acceleration.z);
  //.println(" m/s^2");

  // Serial.print("Rotation X: ");
  // Serial.print(g.gyro.x);
  // Serial.print(", Y: ");
  // Serial.print(g.gyro.y);
  // Serial.print(", Z: ");
  // Serial.print(g.gyro.z);
  // Serial.println(" rad/s");

  // Serial.print("Temperature: ");
  // Serial.print(temp.temperature);
  // Serial.println(" degC");

  //Serial.println("");
  delay(500);
}
