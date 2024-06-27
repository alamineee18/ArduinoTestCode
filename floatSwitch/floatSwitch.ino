int FloatSensor = 26;
//int led = 13;
int buttonState = 1; //reads pushbutton status

void setup() {
  Serial.begin(9600);
  pinMode(FloatSensor, INPUT_PULLUP);
  //pinMode (led, OUTPUT);
}

void loop() {
  buttonState = digitalRead(FloatSensor);

  if (buttonState == HIGH) {
    //digitalWrite(led, LOW);
    Serial.println("WATER LEVEL - LOW");
  }
  else {
    //digitalWrite(led, HIGH);
    Serial.println("WATER LEVEL - HIGH");
  }
  delay(1000);
}