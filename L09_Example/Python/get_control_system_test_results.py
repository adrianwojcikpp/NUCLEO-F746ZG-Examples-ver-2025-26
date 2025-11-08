import serial
import struct
import time
import numpy as np
import matplotlib.pyplot as plt

# --- Serial configuration ---
PORT = 'COM8'
BAUD = 115200
TIMEOUT = 10  # seconds

# --- Expected data parameters ---
NUM_FLOATS = 3000
BYTES_PER_FLOAT = 4
TOTAL_BYTES = NUM_FLOATS * BYTES_PER_FLOAT

def read_exact(ser, num_bytes):
    """Read exactly num_bytes from serial."""
    data = b''
    while len(data) < num_bytes:
        chunk = ser.read(num_bytes - len(data))
        if not chunk:
            raise TimeoutError("Timeout waiting for serial data.")
        data += chunk
    return data

def request_data(ser, ref_ma):
    """Send reference, request data, and return parsed arrays."""
    # Format reference as e.g. R0005.00
    ref_str = f"R{ref_ma:07.2f}"
    ser.write(ref_str.encode('ascii'))
    print(f"Sent: {ref_str} (set reference to {ref_ma:.2f} mA)")
    time.sleep(2)

    # Request float data
    ser.write(b'FLOAT___')
    print("Sent: FLOAT___ (request data)")

    raw = read_exact(ser, TOTAL_BYTES)
    floats = struct.unpack('<' + 'f' * NUM_FLOATS, raw)
    data = np.array(floats).reshape(-1, 3)
    return data

def main():
    with serial.Serial(PORT, BAUD, timeout=TIMEOUT) as ser:
        print("Connected to", PORT)

        ser.write(b'M0000001')
        print("Sent: M0000001 (enable closed loop control)")
        time.sleep(0.5)

        all_data = []

        # Sweep from 0 to 20 mA in steps of 1 mA
        for ref_ma in range(0, 21):
            print(f"\n=== Step {ref_ma} mA ===")
            ser.write(b'L0000001')
            print("Sent: L0000001 (enable logging)")
            data = request_data(ser, ref_ma)
            all_data.append(data)

        # Combine all results
        full_data = np.vstack(all_data)

        # Split columns
        duty = full_data[:, 0]
        meas = full_data[:, 1]
        ref = full_data[:, 2]

        # Add tolerance bands (+/- 1 mA)
        ref_plus = ref + 1.0
        ref_minus = ref - 1.0

        # --- Plot ---
        fig, (ax1, ax2) = plt.subplots(2, 1, figsize=(10, 8), sharex=True)

        ax1.plot(meas, label='Measured Current [mA]')
        ax1.plot(ref, label='Reference Current [mA]', linestyle='--')
        ax1.plot(ref_plus, linestyle=':', color='tab:red', label='+1 mA tolerance')
        ax1.plot(ref_minus, linestyle=':', color='tab:red', label='-1 mA tolerance')

        ax1.set_ylabel('Current [mA]')
        ax1.set_title('Measured vs Reference Current (0–20 mA sweep)')
        ax1.legend()
        ax1.grid(True)

        ax2.plot(duty, color='tab:orange')
        ax2.set_ylabel('Duty [%]')
        ax2.set_xlabel('Sample Index')
        ax2.set_title('Duty Cycle')
        ax2.grid(True)

        plt.tight_layout()
        plt.show()

if __name__ == '__main__':
    main()
