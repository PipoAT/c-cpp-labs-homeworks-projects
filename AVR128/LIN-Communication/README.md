# AVR128 LIN (Local Interconnect Network) Communication Example

This example demonstrates basic LIN bus communication using AVR128 series microcontrollers. LIN is a low-cost serial communication protocol widely used in automotive applications for body control, lighting, and other subsystems.

## Overview

LIN (Local Interconnect Network) is a serial network protocol used primarily in automotive applications:

- **Single-wire communication** (plus ground) - reduces wiring cost
- **Master-slave architecture** - one master node, up to 16 slaves
- **Low cost** - simpler than CAN, uses standard UART
- **Deterministic timing** - master controls all communication
- **Speed:** 2.4 - 20 kbps (typical: 19.2 kbps)
- **Distance:** Up to 40 meters
- **Voltage:** 12V nominal bus voltage

### When to Use LIN vs CAN:
| Feature | LIN | CAN |
|---------|-----|-----|
| Speed | Up to 20 kbps | Up to 1 Mbps (Classic) |
| Cost | Low | Medium |
| Wiring | Single wire + GND | Two wires (CANH/CANL) |
| Use Case | Non-critical control | Critical, high-speed control |
| Typical Application | Windows, mirrors, lights | Engine, brakes, transmission |

## Hardware Requirements

### Essential Components:
- **AVR128DA** or **AVR128DB** microcontroller
- **LIN transceiver** (TJA1020, TJA1021, MCP2003, MCP2004, or ATA6662)
- **12V power supply** (for LIN bus voltage - VBAT)
- **5V or 3.3V power supply** (for microcontroller - VCC)
- **Breadboard and jumper wires**
- Optional: **LIN bus analyzer** or oscilloscope for testing
- Optional: **Second LIN node** (master or slave) for testing

### LIN Transceiver Comparison:
| Transceiver | Manufacturer | Features | Common Use |
|-------------|--------------|----------|------------|
| TJA1020 | NXP | Slope control, low EMI | General automotive |
| TJA1021 | NXP | Extended temperature | Harsh environments |
| MCP2003 | Microchip | Low power, 3.3V/5V | General purpose |
| MCP2004 | Microchip | Enhanced ESD protection | Robust designs |
| ATA6662 | Microchip | LIN 2.2A compliant | Modern automotive |

## Wiring Connections

### AVR128 to LIN Transceiver:
| AVR128 Pin | LIN Transceiver Pin | Description |
|------------|---------------------|-------------|
| PC0 (USART1 TX) | TXD | UART transmit to transceiver |
| PC1 (USART1 RX) | RXD | UART receive from transceiver |
| VCC (5V or 3.3V) | VCC | Logic supply |
| GND | GND | Ground |

### LIN Transceiver to LIN Bus:
| LIN Transceiver Pin | LIN Bus | Description |
|---------------------|---------|-------------|
| VBAT | +12V Supply | Bus supply voltage |
| LIN | LIN Bus Wire | LIN bus connection |
| GND | Ground | Common ground |

### Optional Components:
| Component | Connection | Purpose |
|-----------|------------|---------|
| LED + Resistor | AVR128 PA0 | Activity indicator |
| Pull-up resistor (1kΩ) | LIN bus to VBAT | Recessive state |
| Master termination resistor (1kΩ) | LIN to GND | Only on master node |
| Diode (1N4148) | Transceiver protection | Optional ESD protection |

## What This Example Does

This example implements a **LIN master node** that:

1. **Initializes the UART for LIN communication**
   - Configures USART1 at 19200 baud
   - Sets up 8-bit data, no parity, 1 stop bit

2. **Generates LIN break field**
   - Forces TX line low for ≥13 bit times (~677µs @ 19200 bps)
   - Signals start of new message frame

3. **Sends complete LIN frames**
   - Break field (13+ bit times)
   - Sync field (0x55)
   - Protected ID (6-bit ID + 2 parity bits)
   - Data bytes (0-8 bytes)
   - Checksum (enhanced LIN 2.x)

4. **Provides LED indication**
   - Toggles PA0 with each transmitted message
   - Visual confirmation of activity

## LIN Frame Structure

```
┌─────────────┬──────┬──────────┬───────────────┬─────────┬──────────┐
│ Break Field │Delim.│ Sync (0x55)│ Protected ID │  Data   │Checksum  │
│  ≥13 bits   │1 bit │  8 bits  │   8 bits     │ 0-8 B   │  8 bits  │
└─────────────┴──────┴──────────┴───────────────┴─────────┴──────────┘
    Master           Master         Master        Master/Slave  Master/Slave
```

### Field Descriptions:

**Break Field (≥13 bit times dominant)**
- Sent by master to initiate communication
- Must be at least 13 bit times (677µs @ 19200 bps)
- Followed by 1 bit time recessive (break delimiter)

**Sync Field (0x55)**
- Binary: 10101010b
- Allows slaves to synchronize to master's baud rate
- Used for clock tolerance compensation

**Protected ID (8 bits)**
- Bits [5:0]: Frame ID (0-63)
- Bit 6: P0 parity = ID0 ⊕ ID1 ⊕ ID2 ⊕ ID4
- Bit 7: P1 parity = ¬(ID1 ⊕ ID3 ⊕ ID4 ⊕ ID5)

**Data Field (0-8 bytes)**
- Length determined by frame ID configuration
- Contains actual payload data
- Sent by master or slave depending on frame type

**Checksum (8 bits)**
- Enhanced checksum (LIN 2.x): Includes protected ID + data
- Classic checksum (LIN 1.x): Data only
- Formula: Checksum = ~(Sum of bytes with carry handling)

## Building and Flashing

### Using avr-gcc (command line):
```bash
# For AVR128DA28
avr-gcc -mmcu=avr128da28 -DF_CPU=24000000UL -Os -o main.elf main.cpp
avr-objcopy -O ihex -R .eeprom main.elf main.hex
avrdude -c serialupdi -p avr128da28 -U flash:w:main.hex:i

# For AVR128DB48
avr-gcc -mmcu=avr128db48 -DF_CPU=24000000UL -Os -o main.elf main.cpp
avr-objcopy -O ihex -R .eeprom main.elf main.hex
avrdude -c serialupdi -p avr128db48 -U flash:w:main.hex:i
```

### Using MPLAB X IDE:
1. Create new project:
   - File → New Project
   - Microchip Embedded → Standalone Project
   - Device: AVR128DA28/32/48/64 or AVR128DB28/32/48/64

2. Add files:
   - Add `main.cpp` to Source Files

3. Configure build settings:
   - Project Properties → Conf → AVR-GCC
   - Add to C Compiler options: `-DF_CPU=24000000UL`

4. Build and program:
   - Production → Build Main Project
   - Production → Make and Program Device
   - Use UPDI programmer (MPLAB Snap, Curiosity Nano, etc.)

### Using Arduino IDE (with DxCore):
1. Install DxCore:
   - File → Preferences
   - Additional Boards Manager URLs: `http://drazzy.com/package_drazzy.com_index.json`
   - Tools → Board → Boards Manager → Install "DxCore"

2. Configure board:
   - Tools → Board → DxCore → AVR DA-series or AVR DB-series
   - Tools → Chip → AVR128DA28 (or your variant)
   - Tools → Clock Speed → 24 MHz Internal

3. Upload:
   - Sketch → Upload
   - Requires UPDI programmer or SerialUPDI adapter

## Testing

### Test Setup 1: Oscilloscope or Logic Analyzer
1. Connect probe to LIN bus or PC0 (TX)
2. Flash the code and power on
3. Observe waveform:
   - Break field: Low for ~750µs
   - Sync byte: 0x55 (alternating high/low)
   - Protected ID: Check parity bits
   - Data bytes: Should match transmitted data
   - Checksum: Verify calculation

### Test Setup 2: LIN Bus Analyzer
1. Connect LIN analyzer to the bus
2. Configure analyzer for 19200 baud
3. Run the code
4. Observe decoded LIN frames:
   ```
   Frame ID: 0x35
   Data: 0x11 0x22 0x33 0x44
   Checksum: [calculated]
   ```

### Test Setup 3: Two AVR128 Nodes
1. Program first AVR128 as master (this example)
2. Modify code for second AVR128 as slave
3. Connect both to LIN bus via transceivers
4. Master sends frames, slave responds when ID matches

### Expected Behavior:
- LED blinks at 5 Hz (100ms period)
- Each blink = one LIN message transmitted
- Data field increments with each message

## Understanding the Code

### Key Functions:

**`lin_init(role)`**
- Initializes UART for LIN communication (19200 baud)
- Configures TX/RX pins
- Sets up for master or slave role

**`lin_send_break()`**
- Disables UART transmitter
- Forces TX pin low for break duration (≥13 bit times)
- Re-enables UART transmitter
- Critical for frame synchronization

**`lin_send_sync()`**
- Sends sync byte (0x55)
- Allows slaves to measure bit timing

**`lin_calculate_parity(id)`**
- Computes P0 and P1 parity bits
- Creates protected ID from 6-bit frame ID

**`lin_calculate_checksum(id, data, length)`**
- Implements enhanced checksum (LIN 2.x)
- Includes protected ID in calculation
- Handles carry propagation

**`lin_master_send_message(message)`**
- Sends complete LIN frame
- Includes break, sync, ID, data, checksum

## Common Applications

### Automotive Body Control:
- Power windows (driver, passenger, rear)
- Mirror adjustment (left, right, fold)
- Seat adjustment (position, lumbar, heating)
- Door locks and handles

### Lighting Control:
- Interior lighting (dome, ambient, footwell)
- Exterior lighting (headlights, taillights)
- Dashboard illumination

### Climate Control:
- HVAC fan speed
- Temperature control
- Air distribution (vent, floor, defrost)

### Sensors:
- Rain sensors
- Sunlight sensors
- Temperature sensors
- Position sensors

## Troubleshooting

### Problem: No activity on LIN bus
**Solutions:**
- Verify LIN transceiver power (VCC and VBAT)
- Check TX connection (PC0 to transceiver TXD)
- Ensure transceiver enable pin is high (if present)
- Verify ground connections

### Problem: Break field too short
**Solutions:**
- Increase `LIN_BREAK_DURATION_US` constant
- Verify system clock (F_CPU) is correct
- Check oscilloscope measurement

### Problem: Incorrect checksum
**Solutions:**
- Verify using enhanced checksum (includes ID)
- Check carry handling in checksum calculation
- Confirm protected ID is used, not raw ID

### Problem: Slave doesn't respond
**Solutions:**
- Verify slave is listening for correct frame ID
- Check slave's baud rate matches master (19200)
- Ensure proper break detection on slave side
- Confirm sync field allows proper synchronization

### Problem: Communication errors
**Solutions:**
- Add pull-up resistor (1kΩ) from LIN to VBAT
- Check master termination resistor (1kΩ) to GND
- Verify transceiver slope control settings
- Reduce bus length or add proper termination

## Advanced Features

### Break Detection on Slave
For a slave node, detect break field using UART break flag:
```cpp
// Enable break detection
USART1.CTRLA |= USART_RXSIE_bm;  // RX Start Frame Interrupt

// In ISR, check for break
ISR(USART1_RXC_vect) {
    if (USART1.RXDATAH & USART_FERR_bm) {
        // Break detected - start of frame
    }
}
```

### Sleep Mode and Wake-up
LIN supports sleep mode for power saving:
```cpp
// Master sends sleep command (diagnostic frame 0x3C)
void lin_sleep(void) {
    lin_master_send_header(0x3C);
    uint8_t data[8] = {0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF};
    // Send sleep command data
}

// Wake-up via break field
void lin_wakeup(void) {
    lin_send_break();
}
```

### Event-Triggered Frames
For efficient bus utilization, multiple slaves can share frame slots:
```cpp
// Slave responds only if data changed
if (data_changed) {
    lin_slave_send_response(data, length);
}
```

### Transport Layer (Multi-Frame Messages)
For data >8 bytes, use segmented transfer:
```cpp
// First frame: Length + first 6 bytes
// Consecutive frames: Sequence number + 7 bytes
// Implementation requires additional protocol handling
```

## LIN Schedule Table

In a complete LIN network, the master follows a schedule table:

| Time (ms) | Frame ID | Publisher | Subscribers | Data Length |
|-----------|----------|-----------|-------------|-------------|
| 0 | 0x10 | Master | Window ECU | 4 |
| 20 | 0x11 | Window ECU | Master | 2 |
| 40 | 0x20 | Master | Mirror ECU | 4 |
| 60 | 0x21 | Mirror ECU | Master | 3 |
| 100 | Repeat | | | |

## Resources

### Standards and Specifications:
- [LIN Specification 2.2A](https://www.lin-cia.org/) - Official LIN protocol
- [ISO 17987](https://www.iso.org/standard/61222.html) - LIN standard series
- ISO 17987-1: General information and use case definition
- ISO 17987-2: Data link layer and physical layer
- ISO 17987-3: Protocol specification
- ISO 17987-4: Electrical physical layer specification

### Datasheets:
- [TJA1020 LIN Transceiver](https://www.nxp.com/docs/en/data-sheet/TJA1020.pdf) - NXP
- [TJA1021 LIN Transceiver](https://www.nxp.com/docs/en/data-sheet/TJA1021.pdf) - NXP high-speed
- [MCP2003 LIN Transceiver](https://www.microchip.com/en-us/product/MCP2003) - Microchip
- [ATA6662 LIN Transceiver](https://www.microchip.com/en-us/product/ATA6662) - Microchip LIN 2.2A

### Microcontroller Resources:
- [AVR128DA Datasheet](https://www.microchip.com/en-us/product/AVR128DA28)
- [AVR128DB Datasheet](https://www.microchip.com/en-us/product/AVR128DB28)
- [DxCore Arduino Support](https://github.com/SpenceKonde/DxCore)

### Related Examples:
- CAN Communication (AVR128 folder) - For comparison with LIN
- Serial Communication (ATmega1284 folder) - Basic UART concepts
- ATmega1284 examples - Similar AVR programming patterns

## Next Steps

After understanding this basic LIN master example, explore:

1. **Implement LIN slave node**
   - Break detection
   - Response to specific frame IDs
   - Interrupt-driven reception

2. **Schedule table implementation**
   - Periodic frame transmission
   - Time-triggered scheduling
   - Priority handling

3. **Configuration services**
   - Node configuration frames
   - Diagnostic frames (0x3C, 0x3D)
   - Identification services

4. **Error handling**
   - Checksum verification
   - Timeout detection
   - Bus error recovery

5. **Sleep/wake-up management**
   - Low-power sleep mode
   - Wake-up via break field
   - Power-saving strategies

6. **Transport layer**
   - Multi-frame message transfer
   - Segmentation and reassembly
   - Flow control

7. **Integration with other protocols**
   - LIN to CAN gateway
   - LIN diagnostic interface
   - Vehicle network integration
