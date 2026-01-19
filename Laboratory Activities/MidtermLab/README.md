# Midterm Lab: Smart Hybrid Light Intensity Control System

## Overview
This project is an advanced environmental monitoring system designed to classify ambient light levels into three distinct categories: **Cloudy**, **Normal**, and **Bright Sunlight**.

The core feature of this system is its **Hybrid Control Architecture**, which allows the user to switch between two operational modes at runtime:
1.  **Automatic Mode:** The system autonomously classifies the environment using pre-calibrated, hardcoded thresholds.
2.  **Manual Mode:** The system surrenders control to the user, allowing for dynamic calibration of sensitivity thresholds via Serial commands. This allows the device to adapt to different room lighting conditions on the fly without re-uploading code.

## File & Logic Description

| File Name | Description & Technical Implementation |
| :--- | :--- |
| **MidtermLab.ino** | **Main Firmware & Logic Controller**<br>The code is structured into three non-blocking modules:<br><br>1. **Command Parser (`checkSerialInput`):** Implements a String buffer to read UART data character-by-character. It parses specific keywords (`MODE`, `SET`) to change system state variables.<br>2. **Logic Engine (`runSystemLogic`):** Reads the Photoresistor (ADC), maps the value to a percentage (0-100%), and compares it against the active thresholds (either Manual or Auto) to update the LED traffic light.<br>3. **Status Reporter (`printStatusReport`):** Uses `millis()` for non-blocking timing to print a telemetry report every 1 second, ensuring the system remains responsive to user input at all times. |

## Tech Stack
* **Microcontroller:** Arduino Uno / Nano (ATmega328P)
* **Input Sensor:** Photoresistor (LDR) + 10kΩ Resistor (Voltage Divider)
* **Output Actuators:** 3 LEDs (Green, Yellow, Red)
* **Communication:** UART Serial Interface (9600 Baud)
* **Software Concepts:** Finite State Machine (Enum), Analog-to-Digital Conversion, String Manipulation, Time-Division Multiplexing.

## Operational Modes & Commands

The system is controlled entirely through the **Arduino IDE Serial Monitor**.

### 1. Mode Switching
| Command | Function |
| :--- | :--- |
| `MODE AUTO` | Locks the thresholds to fixed values (Low: 40%, High: 70%). User cannot change thresholds in this mode. |
| `MODE MANUAL` | **(Default)** Enables custom threshold tuning. |

### 2. Threshold Calibration (Manual Mode Only)
| Command | Function |
| :--- | :--- |
| `SET LOW xx` | Sets the lower boundary percentage (e.g., `SET LOW 25`). Below this value is "Green/Cloudy". |
| `SET HIGH xx` | Sets the upper boundary percentage (e.g., `SET HIGH 85`). Above this value is "Red/Bright". |

## How to Run

1.  **Hardware Assembly:**
    * **Photoresistor:** Connect to Analog Pin **A0**.
    * **Green LED:** Connect to Digital Pin **11**.
    * **Yellow LED:** Connect to Digital Pin **12**.
    * **Red LED:** Connect to Digital Pin **13**.
    
2.  **Deployment:**
    * Open the code in Arduino IDE.
    * Upload to the board.
    * Open **Serial Monitor** (Ctrl+Shift+M).
    * **Important:** Ensure the "Line Ending" dropdown in the Serial Monitor is set to **"Both NL & CR"** or **"Newline"** so the system detects the end of your commands.

3.  **Demonstration Sequence:**
    * Observe the startup status (Default: Manual).
    * Type `SET LOW 10` to make the Green LED harder to trigger.
    * Type `MODE AUTO` to reset to factory defaults.
    * Shine a light on the sensor to observe the transition from Green → Yellow → Red.
