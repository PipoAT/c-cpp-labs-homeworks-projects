# ATmega1284 CAN Communication Example

This is an introductory example demonstrating CAN (Controller Area Network) communication using the ATmega1284 microcontroller with an MCP2515 CAN controller.

## Overview

CAN (Controller Area Network) is a robust vehicle bus standard designed to allow microcontrollers and devices to communicate with each other without a host computer. It's widely used in automotive and industrial applications.

## Hardware Requirements

- **ATmega1284** microcontroller
- **MCP2515 CAN controller module** (with integrated CAN transceiver)
- Breadboard and jumper wires
- Power supply (5V)
- Optional: Second CAN node for testing (another microcontroller with CAN capability)

## Wiring Connections

| MCP2515 Pin | ATmega1284 Pin | Description |
|-------------|----------------|-------------|
| SCK         | PB7            | SPI Clock   |
| MISO        | PB6            | SPI MISO    |
| MOSI        | PB5            | SPI MOSI    |
| CS          | PB4            | Chip Select |
| INT         | PD2 (optional) | Interrupt   |
| VCC         | 5V             | Power       |
| GND         | GND            | Ground      |

For CAN bus connections:
- **CANH** and **CANL** connect to the CAN bus (twisted pair)
- Termination resistor (120Ω) required at both ends of the CAN bus

## What This Example Does

1. **Initializes SPI communication** - Sets up the SPI interface to communicate with the MCP2515
2. **Configures the MCP2515 CAN controller** - Sets the bit rate to 125 kbps and configures operating mode
3. **Sends a CAN message** - Transmits a message with ID 0x123 containing "HelloCAN" every 2 seconds

## Key Concepts

### CAN Message Structure
- **Message ID**: 11-bit identifier (0x000 - 0x7FF for standard frames)
- **Data Length**: 0-8 bytes
- **Data**: The actual payload

### MCP2515 CAN Controller
The MCP2515 is a stand-alone CAN controller that communicates via SPI. It handles:
- CAN protocol implementation
- Message transmission and reception
- Error detection

### Bit Timing Configuration
The example configures the CAN bus for 125 kbps, which is calculated based on:
- CPU clock frequency (16 MHz)
- Bit Rate Prescaler (BRP)
- Time quanta settings (PRSEG, PHSEG1, PHSEG2)

## Building and Flashing

### Using avr-gcc:
```bash
avr-gcc -mmcu=atmega1284p -DF_CPU=16000000UL -Os -o main.elf main.cpp
avr-objcopy -O ihex -R .eeprom main.elf main.hex
avrdude -c usbasp -p atmega1284p -U flash:w:main.hex:i
```

### Using Atmel Studio:
1. Create a new project for ATmega1284P
2. Add the main.cpp file
3. Build and flash to your device

## Testing

To test this example:
1. Connect two CAN nodes (or use a CAN bus analyzer)
2. Ensure proper 120Ω termination resistors at both ends
3. Flash the transmitter code to one ATmega1284
4. Use a CAN receiver or bus analyzer to verify messages
5. You should see messages with ID 0x123 appearing every 2 seconds

## Troubleshooting

- **No communication**: Check SPI connections and verify MCP2515 is powered
- **Garbage data**: Verify bit rate settings match on all nodes
- **Bus errors**: Check for proper termination resistors (120Ω at each end)
- **No messages received**: Verify CANH and CANL are not swapped

## Learning Resources

- [CAN Bus Protocol](https://en.wikipedia.org/wiki/CAN_bus)
- [MCP2515 Datasheet](https://www.microchip.com/en-us/product/MCP2515)
- [ATmega1284P Datasheet](https://www.microchip.com/en-us/product/ATmega1284P)

## Next Steps

After mastering this basic example, you can:
- Implement message reception with interrupts
- Add message filtering and masking
- Create a more complex CAN protocol with multiple message types
- Implement error handling and bus arbitration strategies
