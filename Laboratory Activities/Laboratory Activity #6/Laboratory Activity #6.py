import serial
import time

PORT = "COM5"
BAUD = 9600

ser = serial.Serial(PORT, BAUD, timeout=0.1)

print("Running... Press Ctrl+C to stop.")

while True:
    if ser.in_waiting > 0:
        incoming = ser.read().decode('utf-8', errors='ignore')

        incoming = incoming.strip()

        if incoming == 'R':
            ser.write(b'1')
        elif incoming == 'G':
            ser.write(b'2')
        elif incoming == 'B':
            ser.write(b'3')

    # tiny sleep so we don't burn CPU
    time.sleep(0.01)
