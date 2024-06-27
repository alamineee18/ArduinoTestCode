#define BLYNK_PRINT Serial

#define BLYNK_TEMPLATE_ID "TMPL6Zoa-hzPb"
#define BLYNK_TEMPLATE_NAME "IoT Solar"
#define BLYNK_AUTH_TOKEN "XDXdhK280We2laD3DGaJv7_ukC4aIAsg"

#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>
char ssid[] = "Nijer Wifi Laga";
char pass[] = "eee18RU65";


#define Load 4

BLYNK_WRITE(V0)
{
  if(param.asInt()==1){
    digitalWrite(Load, HIGH);
  }
  else{
    digitalWrite(Load, LOW);
  }
}

BLYNK_CONNECTED()
{
  Blynk.syncVirtual(V0);  
}

void setup()
{
  // Debug console
  Serial.begin(9600);
  pinMode(Load, OUTPUT); // Initialise digital pin 2 as an output pin
  delay(10);

  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);
}

void loop()
{
  Blynk.run();
}

