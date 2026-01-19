#define PHOTO_PIN A0
#define GREEN_LED 11
#define YELLOW_LED 12
#define RED_LED 13

#define AUTO_LOW_THRESHOLD 40
#define AUTO_HIGH_THRESHOLD 70

String serialInputString = "";
bool commandComplete = false;
unsigned long lastPrintTime = 0;
const unsigned long printInterval = 1000;

int currentLightPercent = 0;
String activeLED = "None";
String environment = "";

int manualLowThreshold = 30;
int manualHighThreshold = 60;

enum SystemMode { MANUAL, AUTOMATIC };
SystemMode currentMode = MANUAL;

void setup() {
  Serial.begin(9600);
  pinMode(PHOTO_PIN, INPUT);
  pinMode(GREEN_LED, OUTPUT);
  pinMode(YELLOW_LED, OUTPUT);
  pinMode(RED_LED, OUTPUT);

  Serial.println("--- System Booted ---");
  Serial.println("Mode: MANUAL (default)");
  Serial.println("Type 'MODE AUTO' or 'SET LOW xx' / 'SET HIGH xx'");
  Serial.println("---------------------");
}

void loop() {
  checkSerialInput();
  runSystemLogic();
  printStatusReport();
}

void checkSerialInput() {
  while (Serial.available()) {
    char inChar = (char)Serial.read();
    if (inChar == '\n' || inChar == '\r') {
      commandComplete = true;
    } else {
      serialInputString += inChar;
    }
  }

  if (commandComplete) {
    serialInputString.toUpperCase();
    serialInputString.trim();

    if (serialInputString.startsWith("MODE")) {
      if (serialInputString.endsWith("AUTO")) {
        currentMode = AUTOMATIC;
        Serial.println("OK: Mode set to AUTOMATIC");
      } else if (serialInputString.endsWith("MANUAL")) {
        currentMode = MANUAL;
        Serial.println("OK: Mode set to MANUAL");
      } else {
        Serial.println("Error: Wrong command");
      }
    } else if (serialInputString.startsWith("SET LOW")) {
      if (currentMode == AUTOMATIC) {
        Serial.println("Error: Cannot set thresholds in AUTOMATIC mode");
      } else {
        String valueStr = serialInputString.substring(7);
        valueStr.trim();
        manualLowThreshold = valueStr.toInt();
        Serial.print("OK: Manual LOW threshold set to ");
        Serial.println(manualLowThreshold);
      }
    } else if (serialInputString.startsWith("SET HIGH")) {
      if (currentMode == AUTOMATIC) {
        Serial.println("Error: Cannot set thresholds in AUTOMATIC mode");
      } else {
        String valueStr = serialInputString.substring(8);
        valueStr.trim();
        manualHighThreshold = valueStr.toInt();
        Serial.print("OK: Manual HIGH threshold set to ");
        Serial.println(manualHighThreshold);
      }
    } else {
      Serial.println("Error: Wrong command");
    }

    serialInputString = "";
    commandComplete = false;
  }
}

void runSystemLogic() {
  int lightValue = analogRead(PHOTO_PIN);
  currentLightPercent = map(lightValue, 0, 1023, 0, 100);

  int lowThreshold = (currentMode == MANUAL) ? manualLowThreshold : AUTO_LOW_THRESHOLD;
  int highThreshold = (currentMode == MANUAL) ? manualHighThreshold : AUTO_HIGH_THRESHOLD;

  digitalWrite(GREEN_LED, LOW);
  digitalWrite(YELLOW_LED, LOW);
  digitalWrite(RED_LED, LOW);

  if (currentLightPercent < lowThreshold) {
    digitalWrite(GREEN_LED, HIGH);
    activeLED = "Green";
  } else if (currentLightPercent <= highThreshold) {
    digitalWrite(YELLOW_LED, HIGH);
    activeLED = "Yellow";
  } else {
    digitalWrite(RED_LED, HIGH);
    activeLED = "Red";
  }

  if (currentLightPercent <= 40) {
    environment = "Cloudy";
  } else if (currentLightPercent <= 70) {
    environment = "Normal";
  } else {
    environment = "Bright Sunlight";
  }
}

void printStatusReport() {
  if (millis() - lastPrintTime >= printInterval) {
    lastPrintTime = millis();

    Serial.print("Light Intensity: ");
    Serial.print(currentLightPercent);
    Serial.print("% Active LED: ");
    Serial.print(activeLED);
    Serial.print(" Current Mode: ");
    if (currentMode == MANUAL) {
      Serial.print("Manual");
    } else {
      Serial.print("Automatic Environment: ");
      Serial.print(environment);
    }
    Serial.println();
  }
}
