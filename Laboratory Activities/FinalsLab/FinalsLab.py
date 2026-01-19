import serial
import requests
import time

# CONFIGURATION
SERIAL_PORT = 'COM5'      # Change if needed
BAUD_RATE = 9600
BASE_URL = 'http://172.20.10.3:8000'  # Provided by instructor

def normalize_input(data):
    return data.strip().lower()

def is_valid_group(data):
    return data.isdigit()

def main():
    try:
        ser = serial.Serial(SERIAL_PORT, BAUD_RATE, timeout=1)
        print("Listening to Arduino...")
    except serial.SerialException as e:
        print(f"Serial error: {e}")
        return

    while True:  # NON-TERMINATING APPLICATION
        try:
            if ser.in_waiting > 0:
                raw_data = ser.readline().decode('utf-8', errors='ignore')
                normalized = normalize_input(raw_data)

                if not normalized:
                    print("Error: Empty serial input")
                    continue

                if not is_valid_group(normalized):
                    print(f"Invalid group number received: {raw_data.strip()}")
                    continue

                group_number = normalized
                endpoint = f"/led/group/{group_number}/toggle"
                full_url = BASE_URL + endpoint

                print(f"Group number received: {group_number}")
                print(f"Endpoint called: {endpoint}")

                try:
                    response = requests.get(full_url, timeout=5)

                    if response.status_code == 200:
                        print(f"API response: SUCCESS ({response.text})")
                    else:
                        print(f"API response: ERROR ({response.status_code})")

                except requests.RequestException as e:
                    print(f"API request failed: {e}")

        except Exception as e:
            print(f"Unexpected error: {e}")

        time.sleep(0.1)  # Prevent CPU overuse

if __name__ == "__main__":
    main()
