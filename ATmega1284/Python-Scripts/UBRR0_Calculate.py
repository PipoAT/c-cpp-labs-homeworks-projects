## auto script to calc BAUD rates

freq = 1000000   # user input for freq used, can change here

BAUD = 2500   # set the lower limit of what BAUD rates you want to check

LIMIT = BAUD + 500     # defines the upper limit to allow 500 BAUD rate calculations
print("")
print("BAUD   UBRR0 Value")
while(BAUD < LIMIT):
    x = ((freq) / (16 * BAUD)) - 1          # calc and print baud rate
    print(BAUD, "", x)
    print("")
    BAUD = BAUD + 1