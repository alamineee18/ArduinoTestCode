#include <Arduino.h>
#include <WiFi.h>
#include "time.h"
#include <ESP_Google_Sheet_Client.h>
#include <GS_SDHelper.h>  // For SD/SD_MMC mounting helper

#define WIFI_SSID "ESP_Network"
#define WIFI_PASSWORD "AlAmin789"

// Google Project ID
#define PROJECT_ID "adcirq"
#define CLIENT_EMAIL "adcirq@adcirq.iam.gserviceaccount.com"  // Service Account's client email
// Service Account's private key
const char PRIVATE_KEY[] PROGMEM = "" -- -- -BEGIN PRIVATE KEY-- -- -\nMIIEvwIBADANBgkqhkiG9w0BAQEFAASCBKkwggSlAgEAAoIBAQDYuhlc5ba3ZGMF\nC6UHUS + GUQOukony7e7cMXK4ljJ1dGAQgKQsGDVjBvmlTAAPpSFAfwzwEwY4utJC\nh8vihl7HWL9dVTwzG59Z5nRmBf92j478ZJAPqosf04vHmsGkJ0j40IJIvN / FoHzi\nR3CC76WhBBjL / 3RWLy3AdNHSDqk72o8Q92f0S1WMQ4TVjSDYXVR2A4lKDNWxTdeP\nZUy0KzEUZ1fBk558CA9keNe2 / kSrpk8C3cy7gN / ywXZQyoac6 / ILfwcQITBXGyhz\nODgcpolzoKxVbtNhlTHe + TjtuUyu9vcVIPuQoIzm4np + Z0dPyebNXOYppAe0gIqj\n3RhaN / pVAgMBAAECggEADXGWn8axS8H8StruKaLvGQ / CDZx4b / gzbQRCOThthXZE\nST6TMH48Vya4UKxP6qiHHgP9KCoKvkHuFGnUPpQWoZrPNnmfKnQIF / o6j5bHdUuY\noCGXnOkq1SNFur2BgO6Q6u8TZ3JHFta90gZPCkg8VKpQ5KkCRrnv4BrYmYU55gT4\nHG + UZhOVSdUoYY8P08hu0pvX8ckc / 2BF7S9uwjmujjrVFY / 5QGdh8XpNil8oWw3c\nRP9aHOIbnEMGxhd93RL7WsXSF28k15JEJSRm4i / cHG6A63Y3xUyqtuENiywQgsU1\nhwSM0pKhYia / IVd7blZMyfTFvENEBQvV / psqJgQ0xwKBgQD9dig2dR6vrRFguiKN\ngZlszSka0IHeDeE3y4Klx3W2f1Cf0xk1op1KACHRQODaifKzYmj72uB7815mtrj6\n3U84BVpzg1pt47B1Wf1JPT + FjtL2NRcft07G2BGbHbRuMMgm9mUtFGhizGXlkxjh\ngWytoxUrjKzW1135g5AYdXp9KwKBgQDa5cJZ5wD1zrgwSod8onw618tw3A11fRHm\ncpJ8Zv3cK1jRvOC2hTVzILr165U8ZpEVzsO5uG4iEV6TOYdDIaAP9vfbHTaHsNOY\n6HFe6cIxRZwF9uLBJxOuQMJZI9plRQc6mp6sVyNeGb97 + 6WNeJAYwzXIUEp0GsMf\nvhLHTt6mfwKBgQCLP2 / mQ0ABmd5zOq + i + HF28dvETIscmJmEEr2LIGLOSXHc7Jfr\n / JPXRO1PTgp6ZdE9tjIhM + Wik1joqzhDMnTEPUStM5vpxW57el4J76lHUekatJ4o\noYeY / Lnnc1FePFSp + zIoqw6SQOM2VjMUKQuw9Wi7DUUjnxyU6S + wEFKkEwKBgQC9\n8G4DGppPsI9Mf + 8uq8NGP+esx5T6JIt6vmHzhl6zQ / 2vCMioN9BYVMdGCqSVI56z\nIJXfOnR + JTo + X8XJ74x3LeKGA8REW6BP5yowpH + 3x2IKHt9FoQXHxzOcq6qfAxWx\nuWcDvhzXU1o / V + 2gY0QN6J1rcpgYRPyZN5IN1ZcHOwKBgQC + Su + JGiVd9qBpWqmU\nxJ2zpthNtuVOQI / HIJecKzS7PvWsmCanju7nO1AmS4kPw / T5 / qmHR1P8hjjisT / Q\nlOWpHIwtL / 9WzHPqenVzPJRBZMlaGNfkSTC3vmBpREqN4juWrnhw4lC9onhqcljM\nh6gPb + XfmJ2T75BVwUnbZifzMg ==\n-- -- -END PRIVATE KEY-- -- -\n ";

// The ID of the spreadsheet where you'll publish the data
const char spreadsheetId[] = "1J8_pYL8Qvr7p_ZBoeqVO32EmTvi1EP2VRFx_7FR8yzg";

// Timer variables
unsigned long lastTime = 0;
unsigned long timerDelay = 30000;
// Token Callback function
void tokenStatusCallback(TokenInfo info);
const char* ntpServer = "pool.ntp.org";  // NTP server to request epoch time
unsigned long epochTime;                 // Variable to save current epoch time

// Function that gets current epoch time
unsigned long getTime() {
  time_t now;
  struct tm timeinfo;
  if (!getLocalTime(&timeinfo)) {
    //Serial.println("Failed to obtain time");
    return (0);
  }
  time(&now);
  return now;
}

void setup() {

  Serial.begin(115200);
  Serial.println();
  Serial.println();

  //Configure time
  configTime(0, 0, ntpServer);
  GSheet.printf("ESP Google Sheet Client v%s\n\n", ESP_GOOGLE_SHEET_CLIENT_VERSION);
  // Connect to Wi-Fi
  WiFi.setAutoReconnect(true);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);

  Serial.print("Connecting to Wi-Fi");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(1000);
  }
  Serial.println();
  Serial.print("Connected with IP: ");
  Serial.println(WiFi.localIP());
  Serial.println();

  // Set the callback for Google API access token generation status (for debug only)
  GSheet.setTokenCallback(tokenStatusCallback);
  // Set the seconds to refresh the auth token before expire (60 to 3540, default is 300 seconds)
  GSheet.setPrerefreshSeconds(10 * 60);
  // Begin the access token generation for Google API authentication
  GSheet.begin(CLIENT_EMAIL, PROJECT_ID, PRIVATE_KEY);
}

void loop() {
  // Call ready() repeatedly in loop for authentication checking and processing
  bool ready = GSheet.ready();
  if (ready && millis() - lastTime > timerDelay) {
    lastTime = millis();
    FirebaseJson response;
    Serial.println("\nAppend spreadsheet values...");
    Serial.println("----------------------------");
    FirebaseJson valueRange;

    // New BME280 sensor readings
    temp = bme.readTemperature();
    epochTime = getTime();

    valueRange.add("majorDimension", "COLUMNS");
    valueRange.set("values/[0]/[0]", epochTime);
    valueRange.set("values/[1]/[0]", temp);

    // For Google Sheet API ref doc, go to https://developers.google.com/sheets/api/reference/rest/v4/spreadsheets.values/append
    // Append values to the spreadsheet
    bool success = GSheet.values.append(&response /* returned response */, spreadsheetId /* spreadsheet Id to append */, "Sheet1!A1" /* range to append */, &valueRange /* data range to append */);
    if (success) {
      response.toString(Serial, true);
      valueRange.clear();
    } else {
      Serial.println(GSheet.errorReason());
    }
    Serial.println();
    Serial.println(ESP.getFreeHeap());
  }
}

void tokenStatusCallback(TokenInfo info) {
  if (info.status == token_status_error) {
    GSheet.printf("Token info: type = %s, status = %s\n", GSheet.getTokenType(info).c_str(), GSheet.getTokenStatus(info).c_str());
    GSheet.printf("Token error: %s\n", GSheet.getTokenError(info).c_str());
  } else {
    GSheet.printf("Token info: type = %s, status = %s\n", GSheet.getTokenType(info).c_str(), GSheet.getTokenStatus(info).c_str());
  }
}