# AVR128 CAN Communication Example

This is an introductory example demonstrating CAN (Controller Area Network) communication using AVR128 series microcontrollers.

## Overview

The AVR128 series includes several variants, some with built-in CAN controllers:
- **AVR128DA** - Modern AVR with built-in CAN controller
- **AVR128DB** - Enhanced variant with built-in CAN controller

Unlike older AVR microcontrollers, these newer AVR128 series MCUs have integrated CAN peripherals, eliminating the need for external CAN controllers like the MCP2515.

## Hardware Requirements

### Option 1: AVR128DA/DB with Built-in CAN
- **AVR128DA** or **AVR128DB** microcontroller
- **CAN transceiver module** (e.g., TJA1050, SN65HVD230, MCP2551)
- Breadboard and jumper wires
- Power supply (3.3V or 5V depending on transceiver)

### Option 2: Other AVR128 variants
- AVR128 microcontroller (without built-in CAN)
- MCP2515 CAN controller module
- Follow the ATmega1284 example approach

## Wiring Connections

### For AVR128DA/DB (Built-in CAN):

| AVR128DA/DB Pin | CAN Transceiver | Description |
|-----------------|-----------------|-------------|
| PA6 (CANTX)     | TX              | CAN Transmit |
| PA7 (CANRX)     | RX              | CAN Receive  |
| VDD             | VCC             | Power        |
| GND             | GND             | Ground       |

CAN Bus connections:
- Transceiver **CANH** and **CANL** to CAN bus (twisted pair)
- **120Ω termination resistor** at each end of the CAN bus

## What This Example Does

1. **Initializes the system clock** - Configures the AVR128 to run at 24 MHz
2. **Configures the CAN peripheral** - Sets up the built-in CAN controller for 125 kbps operation
3. **Sends periodic CAN messages** - Transmits a message with ID 0x123 containing "HelloCAN" every 2 seconds
4. **Blinks an LED** - Toggles LED on PA0 to indicate activity

## Key Differences from ATmega1284

| Feature | ATmega1284 | AVR128DA/DB |
|---------|------------|-------------|
| CAN Controller | External (MCP2515) | Built-in |
| Communication | SPI to MCP2515 | Direct CAN peripheral |
| Pin Count | 40 pins | 28-48 pins depending on package |
| Clock Speed | Up to 20 MHz | Up to 24 MHz |
| Architecture | Classic AVR | Modern AVR |

## Important Implementation Notes

**This example provides a framework that needs device-specific customization:**

1. **Check your AVR128 variant** - Not all AVR128 MCUs have built-in CAN
2. **Consult the datasheet** - Register names and bit positions vary by device
3. **Configure bit timing** - Adjust for your clock frequency and desired bitrate
4. **Update register operations** - Replace placeholder code with actual CAN registers

### Register Examples (AVR128DA/DB):
- `CANn.CTRLA` - CAN Control Register A
- `CANn.NBTP` - Nominal Bit Timing and Prescaler
- `CANn.DBTP` - Data Bit Timing and Prescaler (CAN FD)
- `CANn.TXB` - Transmit Buffer registers
- `CANn.RXB` - Receive Buffer registers

## CAN Bit Timing Calculation

For 125 kbps @ 24 MHz:
```
Bit Rate = Clock / (Prescaler × (1 + TSEG1 + TSEG2))
125 kbps = 24 MHz / (Prescaler × Total_TQ)

Example: Prescaler=12, TSEG1=13, TSEG2=2
Bit time = (1 + 13 + 2) × (12/24MHz) = 16 × 0.5µs = 8µs = 125 kbps ✓
```

## Building and Flashing

### Using avr-gcc (for AVR128DA):
```bash
avr-gcc -mmcu=avr128da28 -DF_CPU=24000000UL -Os -o main.elf main.cpp
avr-objcopy -O ihex -R .eeprom main.elf main.hex
avrdude -c serialupdi -p avr128da28 -U flash:w:main.hex:i
```

### Using MPLAB X IDE:
1. Create a new project for AVR128DA/DB
2. Add the main.cpp file
3. Configure project settings for your device
4. Build and program using UPDI programmer

### Using Arduino IDE (with megaTinyCore/DxCore):
1. Install the DxCore board package
2. Select AVR128DA or AVR128DB
3. Compile and upload

## Testing

To test this example:
1. Connect the CAN transceiver to your AVR128
2. Connect to a CAN bus with proper termination (120Ω at each end)
3. Use a second CAN node or CAN bus analyzer
4. Flash the code and monitor the bus
5. You should see messages with ID 0x123 every 2 seconds

## Troubleshooting

- **Compilation errors**: Verify you're using the correct device (AVR128DA/DB)
- **No CAN output**: Check transceiver connections and power
- **Wrong bitrate**: Recalculate bit timing for your clock frequency
- **Bus errors**: Verify termination resistors and check CANH/CANL aren't swapped

## Advanced Features (Next Steps)

After completing this basic example, explore:
- **Message reception** with interrupts
- **CAN filtering** to receive specific message IDs
- **CAN FD support** (Flexible Data-rate) for higher throughput
- **Error handling** and bus-off recovery
- **Message prioritization** using different IDs

## Resources

- [AVR128DA Datasheet](https://www.microchip.com/en-us/product/AVR128DA28)
- [AVR128DB Datasheet](https://www.microchip.com/en-us/product/AVR128DB28)
- [CAN Bus Specification](https://www.can-cia.org/)
- [TJA1050 CAN Transceiver](https://www.nxp.com/docs/en/data-sheet/TJA1050.pdf)

## Example Applications

- Automotive sensor networks
- Industrial control systems
- Robot control buses
- Building automation
- Agricultural equipment communication
