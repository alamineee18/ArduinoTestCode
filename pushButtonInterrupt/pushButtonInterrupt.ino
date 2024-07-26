// Button pins
#define BUTTON 27
#define LED 2

#define HIGH_PULSE_WIDTH_THRESHOLD 2000
bool BUTTON_Pressed = false;
volatile uint32_t currTime = 0;
volatile uint32_t prevTime = 0;
uint16_t pulseCount = 0;
uint32_t duration = 0;

void setup() {
  Serial.begin(9600);
  //Initialize the button to input
  pinMode(BUTTON, INPUT_PULLUP);
  pinMode(LED, OUTPUT);
  //Call interrupt when button will press
  attachInterrupt(digitalPinToInterrupt(BUTTON), handleButtonPress, CHANGE);  // Attach interrupt on falling edge
}

void loop() {
  if (digitalRead(LED) == HIGH && BUTTON_Pressed) {
    BUTTON_Pressed = false;             // Reset the flag
    Serial.println("Button pressed!");  // Debug message
    digitalWrite(LED, LOW);
    Serial.print("HIGH Time: ");
    Serial.println(duration);
    Serial.print("Pulse Count: ");
    Serial.println(pulseCount);
  } else if (digitalRead(LED) == LOW && BUTTON_Pressed) {
    BUTTON_Pressed = false;             // Reset the flag
    Serial.println("Button pressed!");  // Debug message
    digitalWrite(LED, HIGH);
    Serial.print("Low Time: ");
    Serial.println(duration);
  }
}

void handleButtonPress() {
  static unsigned long lastInterruptTime = 0;
  unsigned long interruptTime = millis();

  // Debouncing logic: Ignore the interrupt if it occurs within 50 ms of the last interrupt
  if (interruptTime - lastInterruptTime > 200) {
    BUTTON_Pressed = true;              // Set the flag to indicate a button press
    //    Serial.println("Button Pressed");
    currTime = millis();
    duration = currTime - prevTime;
    if (digitalRead(BUTTON)) {
      //      Serial.print("Low Time: ");
    } else {
      //      Serial.print("High Time: ");
      if (duration > HIGH_PULSE_WIDTH_THRESHOLD) {
        pulseCount++;
        //        Serial.print("Pulse Count: ");
        //        Serial.println(pulseCount);
      }
    }
    //    Serial.println(duration);
    prevTime = currTime;
    lastInterruptTime = interruptTime;  // Update the last interrupt time
  }
}
