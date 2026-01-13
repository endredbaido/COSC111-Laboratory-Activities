# Bidirectional Serial LED & Button Interface

## Overview
This project demonstrates full-duplex serial communication between an Arduino microcontroller and a Python script. It creates a physical feedback loop where button presses on the hardware side are sent to the computer, processed by Python, and sent back to the Arduino to toggle LEDs.

Instead of the buttons directly turning on the LEDs (local control), the signal makes a round trip:
**Button Press (Arduino) → Serial 'R/G/B' → Python → Serial '1/2/3' → Toggle LED (Arduino)**

## Activity/File Descriptions

| File Name | Activity / Description |
| :--- | :--- |
| **Arduino_Serial_IO.ino** | **Hardware Logic:** <br>1. **Outbound (TX):** Monitors three buttons (Red, Green, Blue) using "Edge Detection" (detecting the exact moment a button goes from unpressed to pressed). When a press is detected, it sends a character (`'R'`, `'G'`, or `'B'`) to the computer.<br>2. **Inbound (RX):** Listens for characters from the computer (`'1'`, `'2'`, `'3'`). Upon receiving them, it toggles the state (ON/OFF) of the corresponding LED. |
| **Python_Bridge.py** | **Software Logic / Echo Server:** <br>1. Establishes a serial connection to the Arduino.<br>2. Continuously listens for incoming characters.<br>3. Maps the inputs to outputs: If it hears `'R'`, it writes back `'1'`; if `'G'`, it writes `'2'`; if `'B'`, it writes `'3'`. This completes the control loop. |

## Tech Stack
* **Hardware:** Arduino, 3 LEDs (Red, Green, Blue), 3 Push Buttons.
* **Software:** Python 3 (`pyserial` library).
* **Firmware:** C++ (Arduino).
* **Communication:** UART Serial (9600 Baud).
* **Concepts:** Edge Detection, Pull-up Resistors, Serial Echo/Mirroring.

## How to Run

1.  **Hardware Setup:**
    * **LEDs:** Connect Red to Pin 7, Green to Pin 6, Blue to Pin 5 (with resistors).
    * **Buttons:** Connect buttons to Pins 12 (Red), 11 (Green), and 10 (Blue). Connect the other leg of each button to **GND** (The code uses internal Pull-ups, so external resistors are not needed for buttons).

2.  **Arduino Upload:**
    * Copy the Arduino C++ code into the IDE.
    * Upload to your board.

3.  **Python Setup:**
    * Ensure Python is installed.
    * Install the serial library:
        ```bash
        pip install pyserial
        ```
    * Open the Python script and verify `PORT = "COM5"` matches your actual device port.
    * Run the script:
        ```bash
        python Python_Bridge.py
        ```

4.  **Verification:**
    * Press the button connected to Pin 12.
    * The Arduino sends 'R' to Python.
    * Python sees 'R', prints nothing, but instantly sends '1' back.
    * Arduino receives '1' and turns on the Red LED (Pin 7).
    * Press the button again to toggle it off.
