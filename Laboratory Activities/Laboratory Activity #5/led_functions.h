#ifndef LED_FUNCTIONS_H
#define LED_FUNCTIONS_H

#include <Arduino.h>

// Pin Definitions
const int RED_PIN = 8;
const int GREEN_PIN = 9;
const int BLUE_PIN = 10;

// Function to initialize pins
void setupLEDPins() {
  pinMode(RED_PIN, OUTPUT);
  pinMode(GREEN_PIN, OUTPUT);
  pinMode(BLUE_PIN, OUTPUT);
  // Start with all off
  digitalWrite(RED_PIN, LOW);
  digitalWrite(GREEN_PIN, LOW);
  digitalWrite(BLUE_PIN, LOW);
}

// Function to toggle a specific pin [R,G,B]
void toggleLED(int pin) {
  // Read the current state and write the opposite
  int state = digitalRead(pin);
  digitalWrite(pin, !state);
}

// Function to turn all LEDs ON [A]
void turnAllOn() {
  digitalWrite(RED_PIN, HIGH);
  digitalWrite(GREEN_PIN, HIGH);
  digitalWrite(BLUE_PIN, HIGH);
}

// Function to turn all LEDs OFF [O]
void turnAllOff() {
  digitalWrite(RED_PIN, LOW);
  digitalWrite(GREEN_PIN, LOW);
  digitalWrite(BLUE_PIN, LOW);
}

#endif