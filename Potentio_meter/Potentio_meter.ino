
int sensorValue = 0;
void setup()
{
  pinMode(A0, INPUT);
  Serial.begin(9600);
}
void loop()
{
  sensorValue = analogRead(A0);
  
  Serial.print("sensor = ");
  Serial.println(sensorValue);
}
