#define THERMISTOR_PIN A0
#define PHOTO_PIN A2
#define ALERT_PIN 12

const float TEMP_THRESHOLD = 50.0;
const int LIGHT_THRESHOLD = 220;

float readTemperature() {
  int analogValue = analogRead(THERMISTOR_PIN);
  float voltage = analogValue * (5.0 / 1023.0);
  float resistance = (5.0 - voltage) * 10000.0 / voltage;
  float temperatureC = 1.0 / (log(resistance / 10000.0) / 3950.0 + 1.0 / (25.0 + 273.15)) - 273.15;
  return temperatureC;
}

void setup() {
  Serial.begin(9600);
  pinMode(ALERT_PIN, OUTPUT);
}

void loop() {
  float temperature = readTemperature();
  int scaledBrightness = map(analogRead(PHOTO_PIN), 0, 1023, 0, 300);
  int brightnessDigital = (scaledBrightness >= LIGHT_THRESHOLD) ? HIGH : LOW;

  Serial.print("Temperature: ");
  Serial.print(temperature);
  Serial.print(" °C | Brightness: ");
  Serial.print(scaledBrightness);
  Serial.println(brightnessDigital == HIGH ? " (Bright)" : " (Dark)");

  if (temperature >= TEMP_THRESHOLD && brightnessDigital == HIGH) {
    digitalWrite(ALERT_PIN, HIGH);
    delay(100);
    digitalWrite(ALERT_PIN, LOW);
    delay(100);
  } else {
    digitalWrite(ALERT_PIN, LOW);
    delay(500);
  }
}
