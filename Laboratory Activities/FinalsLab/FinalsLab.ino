const int buttonPin = 2;
const int groupNumber = 6;

bool lastButtonState = HIGH;
bool buttonPressed = false;
unsigned long lastDebounceTime = 0;
const unsigned long debounceDelay = 50;

void setup() {
  pinMode(buttonPin, INPUT_PULLUP);
  Serial.begin(9600);
}

void loop() {
  bool reading = digitalRead(buttonPin);

  if (reading != lastButtonState) {
    lastDebounceTime = millis();
  }

  if ((millis() - lastDebounceTime) > debounceDelay) {
    if (reading == LOW && !buttonPressed) {
      // Valid button press detected
      Serial.println(groupNumber);
      buttonPressed = true;
    }

    if (reading == HIGH) {
      // Button released, ready for next press
      buttonPressed = false;
    }
  }

  lastButtonState = reading;
}