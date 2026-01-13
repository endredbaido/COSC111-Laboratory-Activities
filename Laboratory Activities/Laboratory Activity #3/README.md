# Dual-Sensor Environmental Alert System

## Overview
This Arduino project implements an environmental safety monitor that reads real-time data from a temperature sensor (Thermistor) and a light sensor (Photoresistor). It prints the calculated temperature (in °C) and brightness status to the Serial Monitor.

The system features a conditional alert logic: it triggers a rapid alarm signal on a digital pin only when **both** specific conditions are met simultaneously:
1.  High Temperature (≥ 50.0°C)
2.  High Brightness (Scaled value ≥ 220)

## Activity/File Descriptions

| File Name | Activity / Description |
| :--- | :--- |
| **Env_Monitor.ino** | **Sensor Fusion & Logic:** <br>1. **Data Acquisition:** Reads raw analog signals from A0 (Thermistor) and A2 (Photoresistor).<br>2. **Signal Processing:** Converts thermistor voltage to temperature using the Steinhart-Hart equation and maps photoresistor values to a scaled 0-300 range.<br>3. **Alert System:** Checks if both temperature and light thresholds are exceeded. If yes, it strobes Pin 12 (100ms interval); otherwise, it remains idle with a 500ms refresh rate. |

## Tech Stack
* **Hardware:** Arduino, NTC Thermistor (10kΩ), Photoresistor (LDR), 10kΩ Fixed Resistors (for voltage dividers), Output Device (LED or Buzzer).
* **Algorithm:** Steinhart-Hart equation for temperature conversion.
* **Concepts:** Analog-to-Digital Conversion (ADC), Sensor Calibration, Boolean Logic.

## How to Run

1.  **Hardware Setup:**
    * **Thermistor:** Connect a 10kΩ NTC Thermistor and a 10kΩ resistor in a voltage divider configuration. Connect the junction to **Pin A0**.
    * **Photoresistor:** Connect the LDR and a resistor (usually 10kΩ) in a voltage divider configuration. Connect the junction to **Pin A2**.
    * **Alert Output:** Connect an LED (with resistor) or Piezo Buzzer to **Digital Pin 12**.

2.  **Configuration:**
    * Open the code in Arduino IDE.
    * Adjust `TEMP_THRESHOLD` (currently `50.0`) if you need a different temperature trigger.
    * Adjust `LIGHT_THRESHOLD` (currently `220`) based on your ambient lighting conditions.

3.  **Execution:**
    * Upload the sketch to the Arduino.
    * Open the **Serial Monitor** (Ctrl+Shift+M) and set baud rate to **9600**.
    * Observe the real-time readings. To test the alarm, apply heat to the thermistor and shine a bright light on the LDR simultaneously.
