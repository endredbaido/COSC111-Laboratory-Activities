# Arduino Serial LED Controller System

## Overview
This project establishes a hardware-software interface allowing a user to control an LED array connected to an Arduino via a Python-based command-line interface (CLI) on a computer. The system utilizes serial communication to send discrete commands from the Python script to the Arduino, which then executes low-level hardware control functions to toggle specific LEDs (Red, Green, Blue) or control the entire array simultaneously.

## Activity/File Descriptions

| File Name | Activity / Description |
| :--- | :--- |
| **Lab_LED_Project.py** | **Python Serial Controller:** Acts as the primary user interface. It establishes a serial connection (default `COM5`) and presents a recurring menu allowing the user to select commands (e.g., Toggle Red, All ON). It encodes these choices into single characters and transmits them to the microcontroller. |
| **Lab_LED_Project.ino** | **Main Firmware Logic:** This is the entry point for the Arduino application. It initializes the serial baud rate (9600) and continuously monitors the serial buffer. Upon receiving data, it executes a switch-case logic to map specific characters ('R', 'G', 'B', etc.) to the corresponding hardware functions. |
| **led_functions.h** | **Hardware Abstraction Header:** Contains the hardware definitions and logic. It defines the specific digital pins (Red=8, Green=9, Blue=10) and implements modular functions for setting up pins, toggling individual LED states, and performing bulk actions (turning all LEDs ON or OFF). |

## Tech Stack
* **Hardware:** Arduino (Microcontroller), 3 LEDs (Red, Green, Blue)
* **Firmware:** C++ (Arduino IDE)
* **Software (Client):** Python 3
* **Libraries:**
    * Python: `pyserial`, `time`, `os`
    * Arduino: Standard `Arduino.h`

## How to Run

1.  **Hardware Setup:**
    * Connect the Red LED to Pin 8.
    * Connect the Green LED to Pin 9.
    * Connect the Blue LED to Pin 10.
    * Ensure all LEDs are properly grounded with appropriate resistors.

2.  **Firmware Upload:**
    * Open `Lab_LED_Project.ino` in the Arduino IDE.
    * Ensure `led_functions.h` is in the same directory as the `.ino` file.
    * Upload the sketch to your Arduino board.

3.  **Python Client Setup:**
    * Install the required Python library:
        ```bash
        pip install pyserial
        ```
    * Open `Lab_LED_Project.py`.
    * **Important:** Check line 6 (`COM_PORT = 'COM5'`) and change `'COM5'` to match the actual serial port your Arduino is connected to (e.g., `COM3`, `/dev/ttyUSB0`).

4.  **Execution:**
    * Run the Python script:
        ```bash
        python Lab_LED_Project.py
        ```
    * Follow the on-screen menu to control the LEDs.
