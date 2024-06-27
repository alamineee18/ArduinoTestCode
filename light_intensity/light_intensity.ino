#include <Wire.h>
#include <BH1750.h>
BH1750 GY30; // instantiate a sensor event object
void setup(){
  Serial.begin(9600); // launch the serial monitor
  Wire.begin(); // Initialize the I2C bus for use by the BH1750 library  
  GY30.begin(); // Initialize the sensor object
  Serial.println("Flux Workshop Example");
}
void loop() {
  float lux = GY30.readLightLevel(); // read the light level from the sensor and store it in a variable
  Serial.println((String)"Light: " + lux + " lx"); // print the data to the serial monitor
  delay(1000); // Pause for a second before repeating the sensor poll
}