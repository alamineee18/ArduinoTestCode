// Button pins
#define BUTTON 27
#define LED 2
bool BUTTON_Pressed = false;


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
  } else if (digitalRead(LED) == LOW && BUTTON_Pressed) {
    BUTTON_Pressed = false;             // Reset the flag
    Serial.println("Button pressed!");  // Debug message
    digitalWrite(LED, HIGH);
  }
}

void handleButtonPress() {
  static unsigned long lastInterruptTime = 0;
  unsigned long interruptTime = millis();

  // Debouncing logic: Ignore the interrupt if it occurs within 50 ms of the last interrupt
  if (interruptTime - lastInterruptTime > 200) {
    BUTTON_Pressed = true;              // Set the flag to indicate a button press
    lastInterruptTime = interruptTime;  // Update the last interrupt time
  }
}
