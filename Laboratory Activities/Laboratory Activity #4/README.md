# Light-Triggered Latched Alarm System

## Overview
This Arduino project implements a light-activated security or notification system with a "latching" mechanism. Unlike simple sensors that turn off when the stimulus is removed, this system activates a blinking LED alarm when the ambient light exceeds a specific threshold and **keeps blinking** regardless of subsequent light levels. The alarm state can only be deactivated manually by sending a specific text command via the Serial Monitor.

## Activity/File Descriptions

| File Name | Activity / Description |
| :--- | :--- |
| **Light_Latch_Alarm.ino** | **Sensor Monitoring & Serial Control:** <br>1. **Monitoring:** Continuously reads an analog photoresistor (Pin A2) and maps the value to a 0-300 scale.<br>2. **Triggering:** If brightness exceeds the threshold (220), a boolean flag (`isBlinking`) is set to `true`.<br>3. **Feedback:** Continuously logs current brightness and system status (Idle/Blinking) to the Serial console.<br>4. **Manual Reset:**listens for the text command "stop" via the Serial interface to reset the system and turn off the alarm.<br>5. **Actuation:** Executes a non-blocking 100ms strobe effect on the LED when the alarm flag is active. |

## Tech Stack
* **Hardware:** Arduino Microcontroller, Photoresistor (LDR), LED.
* **Language:** C++ (Arduino).
* **Concepts:** Analog Data Mapping, Serial String Parsing, Boolean State Management (Latching Logic).

## How to Run

1.  **Hardware Setup:**
    * **Sensor:** Connect a Photoresistor (LDR) to **Pin A2** (using a voltage divider circuit with a 10kΩ resistor).
    * **Actuator:** Connect an LED to **Pin 8** (with a current-limiting resistor).

2.  **Software Configuration:**
    * Open the code in the Arduino IDE.
    * Upload the sketch to your board.

3.  **Execution & Testing:**
    * Open the **Serial Monitor** (Ctrl+Shift+M).
    * **Important:** Set the line ending dropdown (at the bottom of the Serial Monitor) to **"Newline"** or **"Both NL & CR"**.
    * Shine a bright light on the sensor. The LED will start blinking rapidly.
    * Remove the light source. Notice the LED **continues** to blink (Latched State).
    * To reset the system, type `stop` into the Serial Monitor input field and press Enter.
