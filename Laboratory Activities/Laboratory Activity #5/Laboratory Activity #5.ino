#include "led_functions.h"

void setup() {
  Serial.begin(9600); // Initialize serial communication
  setupLEDPins();     // Call function from header file
}

void loop() {
  if (Serial.available() > 0) {
    char input = Serial.read();

    // Logic based on input
    switch (input) {
      // Toggle Red
      case 'R':
        toggleLED(RED_PIN);
        break;

      // Toggle Green
      case 'G':
        toggleLED(GREEN_PIN);
        break;

      // Toggle Blue
      case 'B':
        toggleLED(BLUE_PIN);
        break;

      // All ON
      case 'A':
        turnAllOn();
        break;

      // All OFF
      case 'O':
        turnAllOff();
        break;
      
      // Error handling
      default:
        break;
    }
  }
}
