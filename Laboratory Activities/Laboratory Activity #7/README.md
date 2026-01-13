# State-Synchronized FastAPI LED Controller

## Overview
This project builds a robust "Internet of Things" (IoT) system that allows users to control an Arduino LED array via a web API (FastAPI) while maintaining synchronization with physical buttons.

Unlike simple "fire-and-forget" controllers, this system features **State Awareness**. Before executing a command (like "Turn All On"), the Python server queries the Arduino for the *actual* status of the LEDs. This prevents logic errors where a "Toggle" command accidentally turns an LED off when it was supposed to turn it on, ensuring the software dashboard always matches the physical hardware reality.

## Activity/File Descriptions

| File Name | Activity / Description |
| :--- | :--- |
| **LabAct7.py** (Python) | **FastAPI Server & Logic Engine:** <br>1. **API Endpoints:** Exposes HTTP routes (`/led/on`, `/led/off`, `/led/{color}`) to control hardware.<br>2. **State Logic:** Defines a function `get_arduino_state()` that sends an 's' query to the Arduino and parses the "R,G,B" response.<br>3. **Smart Control:** In the "All On/Off" routes, it checks the current state *before* sending a command. It only sends a toggle signal if the LED is not currently in the desired state. |
| **LabAct7.ino** (Arduino) | **Hardware Controller & Status Reporter:** <br>1. **Command Listener:** Listens for toggle commands ('1', '2', '3') and status requests ('s').<br>2. **Status Reporting:** When it receives 's', it prints the current boolean state of all LEDs (e.g., `1,0,1`) back to the serial port.<br>3. **Physical Override:** Monitors 3 physical push buttons. If a button is pressed, it toggles the LED locally, ensuring manual control still works alongside the web API. |

## Tech Stack
* **Hardware:** Arduino Microcontroller, 3 LEDs, 3 Push Buttons.
* **Backend:** Python 3, FastAPI.
* **Communication:** UART Serial (9600 Baud), PySerial Library.
* **Firmware:** C++ (Arduino).

## How to Run

### 1. Hardware Setup
* **LEDs:** Connect Red (Pin 7), Green (Pin 6), and Blue (Pin 5).
* **Buttons:** Connect Buttons to Pins 12, 11, and 10 (Ground the other side; internal pull-ups are used).

### 2. Arduino Setup
* Open the Arduino code (`LabAct7.ino`).
* Upload the sketch to your board.
* **Close the Arduino IDE Serial Monitor** (The Python script cannot connect if the IDE is using the port).

### 3. Python Setup
* Install dependencies:
    ```bash
    pip install fastapi uvicorn pyserial
    ```
* Update the `COM_PORT` in the Python script (Line 6) to match your Arduino's port.

### 4. Execution
* Start the server using Uvicorn:
    ```bash
    uvicorn LabAct7:app --reload
    ```
* Open your browser to the interactive API documentation:
    **`http://127.0.0.1:8000/docs`**
* **Test:**
    1.  Click `/led/on` -> "Try it out" -> Execute. All LEDs should light up.
    2.  Press a physical button on the breadboard to turn one LED OFF.
    3.  Execute `/led/on` again. The system will detect that only one LED is off and turn *only* that one back on.
