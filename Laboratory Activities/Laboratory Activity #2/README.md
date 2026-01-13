# Sequential PWM Brightness Controller

## Overview
This Arduino project demonstrates the use of arrays and Pulse Width Modulation (PWM) to control a sequence of 5 LEDs. Unlike standard digital blinking, this code assigns a specific, pre-defined brightness level (ranging from 130 to 255) to each LED. The system cycles through turning the LEDs on with their assigned intensity and then turning them off sequentially.

## Activity/File Descriptions

| File Name | Activity / Description |
| :--- | :--- |
| **PWM_LED_Sequence.ino** | **Array-Based Control Logic:** This script uses two parallel arrays: `pins` (to store hardware locations) and `brightness` (to store intensity values). <br><br>**Key Activities:**<br>1. **Setup:** Uses a `while` loop to iterate through the `pins` array and configure them as `OUTPUT`.<br>2. **Activation Sequence:** Iterates through the arrays, using `analogWrite` to apply the specific brightness value to each LED with a 1-second delay.<br>3. **Deactivation Sequence:** Iterates through the arrays again to turn the LEDs off (`LOW`) one by one with a 1-second delay. |

## Tech Stack
* **Hardware:** Arduino Microcontroller, 5 LEDs.
* **Concepts:** Arrays, `while` Loops, PWM (`analogWrite`).
* **Data Structure:** Parallel Arrays (mapping Pin ID to Brightness Value).

## How to Run

1.  **Hardware Setup:**
    * Connect 5 LEDs to Digital Pins **12, 11, 10, 9, and 8**.
    * **Note on Brightness:** On a standard Arduino Uno, Pins **11, 10, and 9** support PWM (dimming). Pins **12 and 8** are standard digital pins; `analogWrite` on these pins will simply turn the LED fully ON or OFF without the dimming effect.
    * Ensure all LEDs are grounded via appropriate resistors (220Ω recommended).

2.  **Upload Code:**
    * Copy the code into the Arduino IDE.
    * Select your Board and Port.
    * Upload the sketch.

3.  **Observation:**
    * Watch the LEDs turn on in sequence. You will notice that LEDs on PWM-capable pins will shine at the specific intensity defined in the `brightness` array (e.g., the LED on pin 9 will be brighter than the LED on pin 10).
