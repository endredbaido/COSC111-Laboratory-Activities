# IoT Remote Group Trigger System (Finals Lab)

## Overview
This project serves as the final laboratory submission for an IoT systems course. It establishes a hardware-to-cloud (or local network) bridge where a physical button press on an Arduino triggers a specific API endpoint on a remote server.

The system is designed to identify a specific student group (Group 6) and toggle a remote LED or resource associated with that group. It utilizes a Python script as a middleware gateway to translate Serial communication from the microcontroller into HTTP requests.

## Activity/File Descriptions

| File Name | Activity / Description |
| :--- | :--- |
| **FinalsLab.ino** | **Hardware Trigger & Debounce Logic:** <br>1. **Input Handling:** Monitors a push button on Pin 2 using an internal pull-up resistor.<br>2. **Signal Processing:** Implements non-blocking software debouncing (50ms delay) to prevent false triggers or multiple signals from a single press.<br>3. **Identification:** Upon a valid press, it transmits the hardcoded Group ID (`6`) via Serial to the connected computer. |
| **FinalsLab.py** | **Serial-to-HTTP Gateway:** <br>1. **Listener:** Continuously monitors the Serial port (`COM5`) for incoming data.<br>2. **Validation:** Checks if the incoming data is a valid digit (the Group ID).<br>3. **API Interaction:** Dynamically constructs a URL (`http://.../led/group/6/toggle`) and sends an HTTP GET request to the instructor's server to perform the toggle action.<br>4. **Error Handling:** Robustly manages timeouts, serial connection failures, and invalid server responses without crashing (Non-terminating application). |

## Tech Stack
* **Hardware:** Arduino Microcontroller, Push Button.
* **Firmware:** C++ (Arduino).
* **Software:** Python 3.
* **Libraries:**
    * Python: `pyserial`, `requests`, `time`.
    * Arduino: Standard `Arduino.h`.
* **Protocol:** UART Serial (9600 Baud), HTTP (REST).

## How to Run

1.  **Hardware Setup:**
    * Connect a Push Button to **Digital Pin 2** and **GND**.
    * Ensure the Arduino is connected to the computer via USB.

2.  **Firmware Configuration:**
    * Open `FinalsLab.ino`.
    * *Optional:* If you need to change the group identity, modify `const int groupNumber = 6;` on line 2.
    * Upload the sketch to the Arduino.

3.  **Software Configuration:**
    * Open `FinalsLab.py`.
    * **Update COM Port:** Change `SERIAL_PORT = 'COM5'` to match your actual device port.
    * **Update Server IP:** Verify `BASE_URL = 'http://172.20.10.3:8000'` matches the current IP address of the target server.
    * Install dependencies if missing:
        ```bash
        pip install pyserial requests
        ```

4.  **Execution:**
    * Run the Python gateway:
        ```bash
        python FinalsLab.py
        ```
    * Press the physical button.
    * Observe the terminal for "Group number received: 6" and the subsequent "API response: SUCCESS".
