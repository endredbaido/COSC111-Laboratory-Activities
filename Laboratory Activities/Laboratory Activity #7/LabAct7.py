from fastapi import FastAPI, HTTPException
import serial
import time

app = FastAPI()

arduino = serial.Serial(port='COM5', baudrate=9600, timeout=1)
time.sleep(2)


def send_command(cmd: str):
    arduino.write(cmd.encode())
    time.sleep(0.05)  # Small delay to let Arduino process


def get_arduino_state():
    """
    Sends 's' to Arduino and reads the response "R,G,B"
    Returns a list of integers [Red, Green, Blue] (e.g., [0, 1, 0])
    """
    # 1. Clear any old data in the buffer
    arduino.reset_input_buffer()

    # 2. Ask for Status
    arduino.write(b's')
    time.sleep(0.1)  # Wait for Arduino to reply

    # 3. Read the Reply
    if arduino.in_waiting > 0:
        try:
            # Read line, strip whitespace, split by comma
            data = arduino.readline().decode().strip()
            # Example data: "0,1,0"
            states = data.split(',')

            # Convert to integers: [0, 1, 0]
            return [int(states[0]), int(states[1]), int(states[2])]
        except:
            return None
    return None


# --- ROUTES ---

@app.get("/led/on")
def all_on():
    # 1. Ask Arduino what is currently ON
    current_states = get_arduino_state()

    if current_states is None:
        raise HTTPException(status_code=500, detail="Arduino not responding")

    red_is_on = current_states[0]
    green_is_on = current_states[1]
    blue_is_on = current_states[2]

    # 2. Only Toggle if it is currently OFF (0)
    if red_is_on == 0:
        send_command("1")  # Toggle Red to ON

    if green_is_on == 0:
        send_command("2")  # Toggle Green to ON

    if blue_is_on == 0:
        send_command("3")  # Toggle Blue to ON

    return {"status": "success", "action": "Turned on necessary LEDs"}


@app.get("/led/off")
def all_off():
    # 1. Ask Arduino what is currently ON
    current_states = get_arduino_state()

    if current_states is None:
        raise HTTPException(status_code=500, detail="Arduino not responding")

    red_is_on = current_states[0]
    green_is_on = current_states[1]
    blue_is_on = current_states[2]

    # 2. Only Toggle if it is currently ON (1)
    if red_is_on == 1:
        send_command("1")  # Toggle Red to OFF

    if green_is_on == 1:
        send_command("2")  # Toggle Green to OFF

    if blue_is_on == 1:
        send_command("3")  # Toggle Blue to OFF

    return {"status": "success", "action": "Turned off necessary LEDs"}


@app.get("/led/{color}")
def control_led(color: str):
    # This remains the same (Toggle logic)
    color = color.lower()
    if color == "red":
        send_command("1")
    elif color == "green":
        send_command("2")
    elif color == "blue":
        send_command("3")
    else:
        return {"error": "Invalid color"}
    return {"status": "success", "led": color}
