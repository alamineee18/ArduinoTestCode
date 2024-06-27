#include <OneWire.h>
#include <DallasTemperature.h>

#define ONE_WIRE_BUS 6 // Change this to your DS18B20 data pin
OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);


#include <dht.h>        // Include library
#define outPin1 A0        // Defines pin number to which the sensor is connected
#define outPin2 A2        // Defines pin number to which the sensor is connected
dht DHT;


#include <LiquidCrystal.h>
#include <Wire.h>
#include <BH1750.h>
BH1750 GY30; // instantiate a sensor event object
LiquidCrystal lcd(9, 8, 5, 4, 3, 2);

void  setup() {
  // put your setup code here, to run once:
  lcd.begin(16, 2);
  Wire.begin(); // Initialize the I2C bus for use by the BH1750 library  
  GY30.begin(); // Initialize the sensor object

  sensors.begin(); // Initialize the DS18B20 sensors
}

void loop() {
  // put your main code here, to run  repeatedly:
  
  float lux = GY30.readLightLevel();
  lcd.setCursor(0,  0);
  lcd.print("Light: ");
  lcd.print(lux);
  lcd.print("Lux");

  delay(2000); // Pause for a second before repeating the sensor poll
  
  lcd.clear();
  int readData1 = DHT.read11(outPin1);
	float h1 = DHT.humidity;           // Read humidity
  lcd.setCursor(0,  0);
  lcd.print("Hum 1 = ");
  lcd.print(h1);
  lcd.print("%");

	delay(1000);

  int readData2 = DHT.read11(outPin2);
	float h2 = DHT.humidity;           // Read humidity
  lcd.setCursor(0,  0);
  lcd.print("Hum 2 = ");
  lcd.print(h2);
  lcd.print("%");

	delay(1000);

  sensors.requestTemperatures(); // Request temperature readings from DS18B20 sensors

  //lcd.clear(); // Clear the LCD screen

  for (int i = 0; i < sensors.getDeviceCount(); i++) {
    float tempC = sensors.getTempCByIndex(i); // Get temperature in Celsius
    lcd.setCursor(0, 1); // Set the LCD cursor position
    lcd.print("Temp ");
    lcd.print(i + 1);
    lcd.print(": ");
    lcd.print(tempC);
    lcd.print("C");
    delay(1500);
  }


  delay(1000); // Delay for 2 seconds before updating the display

  lcd.clear();

}

