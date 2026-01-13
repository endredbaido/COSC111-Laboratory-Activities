# Sequential LED Chaser

## Overview
This Arduino project implements a sequential lighting control system using digital output pins. The logic creates a "chaser" effect where a series of 5 LEDs (connected to pins 12 down to 8) turn on one by one in descending order, followed by turning off one by one in the same order. This cycle repeats indefinitely.

## Activity/File Descriptions

| File Name | Activity / Description |
| :--- | :--- |
| **Sequential_LEDs.ino** | **Logic Controller:** This script maintains two state variables (`bulb_on` and `bulb_off`) to track the active pin index. It utilizes a `loop()` with conditional logic to separate the operation into two phases: <br>1. **Ignition Phase:** Sequentially powers Digital Pins 12 through 8 HIGH with a 1-second delay between each. <br>2. **Extinguish Phase:** Once all are lit, sequentially powers Digital Pins 12 through 8 LOW with a 1-second delay between each. <br>3. **Reset:** Reinitializes the index variables to restart the cycle. |

## Tech Stack
* **Hardware:** Arduino Microcontroller, 5 LEDs, Resistors
* **Language:** C++ (Arduino)
* **Concepts:** Variables, Conditional Logic (`if/else if/else`), Digital I/O Control

## How to Run

1.  **Hardware Setup:**
    * Connect LEDs to Digital Pins **12, 11, 10, 9, and 8**.
    * Ensure each LED is connected in series with a suitable current-limiting resistor (e.g., 220Ω) to Ground (GND).
2.  **Code Preparation:**
    * Copy the provided code into the Arduino IDE.
    * **Note:** For optimal stability, ensure `pinMode` is set to `OUTPUT` for all pins (8-12) in the `setup()` function (the current snippet only explicitly initializes pin 12).
3.  **Execution:**
    * Connect your Arduino board via USB.
    * Select the correct Board and Port in the IDE.
    * Upload the sketch.
    * Observe the 1-second interval sequence of the LEDs.
