#define UP  9  // the number of the pushbutton pin
#define DOWN 10  // the number of the pushbutton pin
#define LEFT  11  // the number of the pushbutton pin
#define RIGHT  12  // the number of the pushbutton pin
 // the number of the pushbutton pin

int buttonStateUP = 0;  // variable for reading the pushbutton status
int buttonStateDOWN = 0;  // variable for reading the pushbutton status
int buttonStateLEFT = 0;  // variable for reading the pushbutton status
int buttonStateRIGHT = 0;  // variable for reading the pushbutton status

void setup() {
  Serial.begin(115200);
  pinMode(UP, INPUT_PULLUP);
  pinMode(DOWN, INPUT_PULLUP);
  pinMode(LEFT, INPUT_PULLUP);
  pinMode(RIGHT, INPUT_PULLUP);  
}

void loop() {
  // read the state of the pushbutton value:
  buttonStateUP = digitalRead(UP);
  buttonStateDOWN = digitalRead(DOWN);
  buttonStateLEFT = digitalRead(LEFT);
  buttonStateRIGHT = digitalRead(RIGHT);
 


  // check if the pushbutton is pressed. If it is, the buttonState is HIGH:
  if (buttonStateUP == HIGH) {
    Serial.println("You are in mode UP");
    delay(200);
  }
  if (buttonStateDOWN == HIGH) {
    Serial.println("You are in mode DOWN");
    delay(200);
  }
  
  if (buttonStateLEFT == HIGH) {
    Serial.println("You are in mode LEFT");
    delay(200);
  }

  if (buttonStateRIGHT == HIGH) {
    Serial.println("You are in mode RIGHT");
    delay(200);
  }
  
  
}
