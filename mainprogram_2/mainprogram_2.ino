#include <SPI.h>
#include <SD.h>

#include <OneWire.h>
#include <DallasTemperature.h>


#define ONE_WIRE_BUS 6 // Change this to your DS18B20 data pin
OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);

#include <dht.h>        // Include library
#define outPin1 A0      // Defines pin number to which the sensor is connected
#define outPin2 A2      // Defines pin number to which the sensor is connected
dht DHT;

#include <LiquidCrystal.h>
#include <Wire.h>
#include <BH1750.h>
BH1750 GY30; // instantiate a sensor event object
LiquidCrystal lcd(9, 8, 5, 4, 3, 2);



#define FILE_NAME "data.csv"
File dataFile;

void setup() {
  Serial.begin(9600);
  // put your setup code here, to run once:
  lcd.begin(16, 2);
  Wire.begin(); // Initialize the I2C bus for use by the BH1750 library  
  GY30.begin(); // Initialize the sensor object

  sensors.begin(); // Initialize the DS18B20 sensors
  Serial.println("Light(lux), Hum1, Hum2, Temp1, Temp2, Temp3, Temp4, Temp5, Temp6, Temp7, Temp8, Temp9, Temp10, Temp11, Temp12, Temp13");
  
  if (SD.begin(10)) {
    Serial.println("SD card initialized.");
    dataFile = SD.open(FILE_NAME, FILE_WRITE);
    dataFile.println("Light(lux), Hum1, Hum2, Temp1, Temp2, Temp3, Temp4, Temp5, Temp6, Temp7, Temp8, Temp9, Temp10, Temp11, Temp12, Temp13");
    dataFile.close();
  } else {
    Serial.println("SD card initialization failed.");
  }
}

void loop() {
  
  float lux = GY30.readLightLevel();
  lcd.setCursor(0,  0);
  lcd.print("Light: ");
  lcd.print(lux);
  lcd.print("Lux");
  Serial.print(lux);
  Serial.print(",");
  delay(10000);
  
  lcd.clear();
  int readData1 = DHT.read11(outPin1);
	float h1 = DHT.humidity;           // Read humidity
  lcd.setCursor(0,  0);
  lcd.print("Hum 1 = ");
  lcd.print(h1);
  lcd.print("%");
  Serial.print(h1);
  Serial.print(",");

	delay(10000);

  int readData2 = DHT.read11(outPin2);
	float h2 = DHT.humidity;           // Read humidity
  lcd.setCursor(0,  0);
  lcd.print("Hum 2 = ");
  lcd.print(h2);
  lcd.print("%");
  Serial.print(h2);
  Serial.print(",");

	delay(10000);

  logData1(lux, h1, h2);

  sensors.requestTemperatures(); // Request temperature readings from DS18B20 sensors
  float tempC; 
  for (int i = 0; i < sensors.getDeviceCount(); i++) {
    tempC = sensors.getTempCByIndex(i); // Get temperature in Celsius
    lcd.setCursor(0, 1); // Set the LCD cursor position
    lcd.print("Temp ");
    lcd.print(i + 1);
    lcd.print(": ");
    lcd.print(tempC);
    lcd.print("C");
    Serial.print(tempC);
    Serial.print(",");
    delay(10000);
    logData2(tempC);
  }
  float NewLine = Serial.println();
  logData3(NewLine);

  delay(30000); // Log data every 30 seconds You can change as your need
  Serial.println(" ");
}

void logData1(float light, float hum1, float hum2) {
  dataFile = SD.open(FILE_NAME, FILE_WRITE);
  if (dataFile) {
    dataFile.print(light);
    dataFile.print(", ");
    dataFile.print(hum1);
    dataFile.print(", ");
    dataFile.print(hum2);
    dataFile.print(", ");   
    dataFile.close();
  } else {
    Serial.println("Error opening data file.");
  }
}

void logData2(float temp) {
  dataFile = SD.open(FILE_NAME, FILE_WRITE);
  if (dataFile) {
    dataFile.print(temp);
    dataFile.print(", ");   
    dataFile.close();
  } else {
    Serial.println("Error opening data file.");
  }
}

void logData3(float sps) {
  dataFile = SD.open(FILE_NAME, FILE_WRITE);
  if (dataFile) {
    dataFile.println();
    dataFile.close();
  } else {
    Serial.println("Error opening data file.");
  }
}
