import serial
import time

def main():
    # Open serial port
    ser = serial.Serial('COM8', 115200, timeout=1)
    print("Sending data on COM8 at 115200 baud...")

    try:
        while True:
            # Loop from 0 to 100 with step of 5
            for value in range(0, 105, 5):
                if value > 100:
                    value = 0
                message = f"B{value:03d}"  # Format as B000, B005, etc.
                ser.write(message.encode('ascii'))
                print(f"Sent: {message}")
                time.sleep(0.2)  # 100 ms delay
    except KeyboardInterrupt:
        print("\nStopped by user.")
    finally:
        ser.close()

if __name__ == "__main__":
    main()
