import serial.tools.list_ports as port_list     # code to list out the available COM ports connected
ports = list(port_list.comports())
for p in ports:
    print (p)


import serial
from time import sleep


while (True):

    ser = serial.Serial(                                # defines what port it is communicating from and defines the settings
    port='COM4', baudrate = 1200, stopbits = 1, bytesize = 8, timeout = 0.5, parity='N')

    #ser.write(b"TEST")
    o = ser.readline()
    # print(ser.readline())    # reads the data from the port coming from MCU
    o = o.decode('ISO-8859-1')
    print(o)        # prints the data

    ser.close()         # closes out port if while loop exits for some ungodly reasoning

