#define PHOTO_PIN A2
#define LED_PIN 8

const int LIGHT_THRESHOLD = 220;

bool isBlinking = false;

void setup() {
  Serial.begin(9600);
  pinMode(LED_PIN, OUTPUT);
}

void loop() {
  int brightness = map(analogRead(PHOTO_PIN), 0, 1023, 0, 300);

  Serial.print("Brightness: ");
  Serial.print(brightness);
  Serial.print(" | Status: ");
  if (isBlinking) Serial.println("Blinking");
  else Serial.println("Idle");

  if (brightness >= LIGHT_THRESHOLD) {
    isBlinking = true;
  }

  if (Serial.available() > 0) {
    String command = Serial.readStringUntil('\n');
    command.toLowerCase();
    command.trim();
    if (command == "stop") {
      isBlinking = false;
      digitalWrite(LED_PIN, LOW);
      Serial.println("Blinking stopped.");
    }
  }

  if (isBlinking) {
    digitalWrite(LED_PIN, HIGH);
    delay(100);
    digitalWrite(LED_PIN, LOW);
    delay(100);
  }
}
