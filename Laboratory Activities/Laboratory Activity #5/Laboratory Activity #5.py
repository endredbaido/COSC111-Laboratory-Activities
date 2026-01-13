import serial
import time
import os


COM_PORT = 'COM5'
BAUD_RATE = 9600


def clear_screen():
    os.system('cls')


def main():
    try:
        arduino = serial.Serial(port=COM_PORT, baudrate=BAUD_RATE, timeout=1)
        time.sleep(2)
    except serial.SerialException:
        print(f"Error: Could not connect to {COM_PORT}.")
        return

    while True:
        clear_screen()
        print("=== Arduino LED Controller ===")
        print("[R] Red ON/OFF")
        print("[G] Green ON/OFF")
        print("[B] Blue ON/OFF")
        print("[A] All ON")
        print("[O] All OFF")
        print("[X] Exit")
        print("==============================")

        user_input = input("Enter Choice: ").strip()


        if not user_input:
            continue

        valid_commands = ['R', 'G', 'B', 'A', 'O', 'X']

        if len(user_input) > 1 or user_input[0].upper() not in valid_commands:
            print("Invalid command.")
            time.sleep(1)
            continue

        command = user_input[0].upper()

        if command == 'X':
            arduino.write('O'.encode())
            time.sleep(1)
            print("Terminating application...")
            arduino.close()
            break


        arduino.write(command.encode())
        print(f"Command '{command}' sent.")

        time.sleep(1)


if __name__ == "__main__":
    main()
