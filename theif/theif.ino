int PIRsensor = 2;
int thief = 0;
int buzzer = 10;

void setup() {
  pinMode(PIRsensor, INPUT);
  pinMode(buzzer, OUTPUT);
}

void loop() {
  thief = digitalRead(PIRsensor);

  if (thief == 1)
  {
    digitalWrite(buzzer, HIGH);
    delay(100);
  }
  else
  {
    digitalWrite(buzzer, LOW);
  }

}
