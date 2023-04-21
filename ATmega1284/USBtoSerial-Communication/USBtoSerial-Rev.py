import serial.tools.list_ports as port_list
ports = list(port_list.comports())
for p in ports:
    print(p)

# above code prints out what ports are available to communicate to

# below code opens up COM4 and sends it one single byte

import serial
from time import sleep

while True:
    try:
        ser = serial.Serial(
            port='COM4', baudrate=1200, stopbits=1, bytesize=8, timeout=5, parity='N')
        print(f"Sending")
        sleep(0.5)
        ser.write(b"X")
        sleep(0.5)
        print(f"Sent")
    except Exception as e:
        print(f"Error: {e}")
    finally:
        ser.close()
