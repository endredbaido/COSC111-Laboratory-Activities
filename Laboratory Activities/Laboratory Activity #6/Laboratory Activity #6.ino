const int RED_LED = 7;
const int GREEN_LED = 6;
const int BLUE_LED = 5;

// Button pins
const int BTN_R = 12;
const int BTN_G = 11;
const int BTN_B = 10;

// tracking previous button states for edge-detection
bool prevR = HIGH;
bool prevG = HIGH;
bool prevB = HIGH;

// LED toggle states
bool redState = LOW;
bool greenState = LOW;
bool blueState = LOW;

void setup() {
  Serial.begin(9600);

  // LED pins
  pinMode(RED_LED, OUTPUT);
  pinMode(GREEN_LED, OUTPUT);
  pinMode(BLUE_LED, OUTPUT);

  // buttons using internal pull-up
  pinMode(BTN_R, INPUT_PULLUP);
  pinMode(BTN_G, INPUT_PULLUP);
  pinMode(BTN_B, INPUT_PULLUP);
}

void loop() {

  // ---------- OUTBOUND ----------
  bool currR = digitalRead(BTN_R);
  bool currG = digitalRead(BTN_G);
  bool currB = digitalRead(BTN_B);

  // detect button press (HIGH → LOW transition)
  if (prevR == HIGH && currR == LOW) {
    Serial.print('R');
  }
  if (prevG == HIGH && currG == LOW) {
    Serial.print('G');
  }
  if (prevB == HIGH && currB == LOW) {
    Serial.print('B');
  }

  prevR = currR;
  prevG = currG;
  prevB = currB;

  // ---------- INBOUND ----------
  if (Serial.available()) {
    char c = Serial.read();

    // normalize case
    c = tolower(c);

    if (c == '1') {
      redState = !redState;
      digitalWrite(RED_LED, redState);
    }
    else if (c == '2') {
      greenState = !greenState;
      digitalWrite(GREEN_LED, greenState);
    }
    else if (c == '3') {
      blueState = !blueState;
      digitalWrite(BLUE_LED, blueState);
    }
  }
}
