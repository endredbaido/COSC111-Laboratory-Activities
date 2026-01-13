// ================= PIN DEFINITIONS =================
const int RED_LED = 7;
const int GREEN_LED = 6;
const int BLUE_LED = 5;

const int BTN1 = 12;
const int BTN2 = 11;
const int BTN3 = 10;

// ================= VARIABLES =================
bool redState = false;
bool greenState = false;
bool blueState = false;

// ================= SETUP =================
void setup() {
  Serial.begin(9600);

  // Configure LED Pins
  pinMode(RED_LED, OUTPUT);
  pinMode(GREEN_LED, OUTPUT);
  pinMode(BLUE_LED, OUTPUT);

  // Configure Button Pins
  pinMode(BTN1, INPUT_PULLUP);
  pinMode(BTN2, INPUT_PULLUP);
  pinMode(BTN3, INPUT_PULLUP);

  // Initialize LEDs to OFF
  digitalWrite(RED_LED, LOW);
  digitalWrite(GREEN_LED, LOW);
  digitalWrite(BLUE_LED, LOW);
  
  
}

// ================= LOOP =================
void loop() {
  
  // 1. CHECK FOR SERIAL COMMANDS (From Python)
  if (Serial.available() > 0) {
    char input = Serial.read();

    switch (input) {
      case '1':
        redState = !redState;
        digitalWrite(RED_LED, redState);
        break;

      case '2':
        greenState = !greenState;
        digitalWrite(GREEN_LED, greenState);
        break;

      case '3':
        blueState = !blueState;
        digitalWrite(BLUE_LED, blueState);
        break;

      
      case 's': 
        Serial.print(redState);
        Serial.print(",");
        Serial.print(greenState);
        Serial.print(",");
        Serial.println(blueState); 
        break;
    }
  }
  
  if (digitalRead(BTN1) == LOW) {
    redState = !redState;
    digitalWrite(RED_LED, redState);
    delay(300);
  }

  if (digitalRead(BTN2) == LOW) {
    greenState = !greenState;
    digitalWrite(GREEN_LED, greenState);
    delay(300);
  }

  if (digitalRead(BTN3) == LOW) {
    blueState = !blueState;
    digitalWrite(BLUE_LED, blueState);
    delay(300);
  }
}
