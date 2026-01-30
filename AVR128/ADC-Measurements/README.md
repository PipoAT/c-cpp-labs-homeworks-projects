# AVR128 ADC (Analog-to-Digital Converter) Example

This example demonstrates how to use the built-in ADC peripheral on AVR128 series microcontrollers to measure analog voltages.

## Overview

The AVR128DA/DB series features a powerful 12-bit ADC with the following capabilities:
- **12-bit resolution** (4096 discrete values: 0-4095)
- **Multiple input channels** (up to 16 depending on package)
- **Flexible reference voltage** options (internal or external)
- **Single-ended or differential** measurements
- **Oversampling and decimation** for enhanced resolution
- **Window comparator** mode for threshold detection

## Hardware Requirements

### Basic Setup:
- **AVR128DA** or **AVR128DB** microcontroller
- **Potentiometer** (10kΩ recommended) or analog sensor
- **Breadboard and jumper wires**
- **Power supply** (3.3V or 5V depending on microcontroller)
- Optional: **LED** for visual indication
- Optional: **USB-to-Serial adapter** for UART output

## Wiring Connections

### ADC Input:
| Component | AVR128 Pin | Description |
|-----------|------------|-------------|
| Potentiometer wiper | PD0 (AIN0) | Analog input channel 0 |
| Potentiometer end 1 | VCC | Positive supply |
| Potentiometer end 2 | GND | Ground |

### Optional Components:
| Component | AVR128 Pin | Description |
|-----------|------------|-------------|
| LED (with resistor) | PA1 | Activity indicator |
| UART TX | PA0 | Serial output for readings |
| UART RX | PA1 (alternate) | Serial input (if needed) |

**Note:** Pin assignments may vary based on your AVR128 variant and package. Consult the datasheet for your specific device.

## What This Example Does

1. **Initializes the ADC peripheral**
   - Configures 12-bit resolution mode
   - Sets VDD as reference voltage
   - Configures ADC clock prescaler for optimal performance

2. **Reads analog input continuously**
   - Samples PD0 (AIN0) every 500ms
   - Converts raw ADC value (0-4095) to voltage in millivolts

3. **Outputs results via UART**
   - Displays both raw ADC value and calculated voltage
   - Updates at 2 Hz (every 500ms)

4. **Provides visual feedback**
   - Toggles LED on PA0 with each measurement

## ADC Configuration Details

### Resolution and Range
- **Resolution:** 12-bit (4096 steps)
- **Input range:** 0V to VREF (typically VDD = 3.3V or 5V)
- **LSB size:** VREF / 4096
  - Example: 3.3V / 4096 ≈ 0.806 mV per step
  - Example: 5.0V / 4096 ≈ 1.221 mV per step

### Reference Voltage Options
The AVR128 ADC supports multiple reference voltage sources:

| Reference | Voltage | Use Case |
|-----------|---------|----------|
| VDD | Supply voltage (3.3V or 5V) | Simple, full-range measurements |
| Internal 2.048V | 2.048V | Better accuracy, precise reference |
| Internal 2.5V | 2.5V | Alternative internal reference |
| Internal 4.096V | 4.096V | High-voltage measurements |
| External VREF | User-defined | Highest accuracy with precision reference |

### Clock Configuration
The ADC clock frequency affects conversion time and accuracy:
- **Optimal ADC clock:** 50 kHz - 1.5 MHz for 12-bit resolution
- **This example:** 24 MHz / 16 = 1.5 MHz (using DIV16 prescaler)
- **Conversion time:** ~13 ADC clock cycles ≈ 8.7 µs @ 1.5 MHz

## Building and Flashing

### Using avr-gcc (command line):
```bash
# For AVR128DA28
avr-gcc -mmcu=avr128da28 -DF_CPU=24000000UL -Os -o main.elf main.cpp
avr-objcopy -O ihex -R .eeprom main.elf main.hex
avrdude -c serialupdi -p avr128da28 -U flash:w:main.hex:i

# For AVR128DB28
avr-gcc -mmcu=avr128db28 -DF_CPU=24000000UL -Os -o main.elf main.cpp
avr-objcopy -O ihex -R .eeprom main.elf main.hex
avrdude -c serialupdi -p avr128db28 -U flash:w:main.hex:i
```

### Using MPLAB X IDE:
1. Create a new project for AVR128DA or AVR128DB
2. Add the `main.cpp` file to your project
3. Configure project settings:
   - Device: AVR128DA28/32/48/64 or AVR128DB28/32/48/64
   - Compiler: AVR GCC
   - F_CPU: 24000000UL
4. Build the project (Production → Build)
5. Program using UPDI programmer (MPLAB Snap, Curiosity Nano, etc.)

### Using Arduino IDE (with DxCore):
1. Install **DxCore** board package:
   - Add URL to Board Manager: `http://drazzy.com/package_drazzy.com_index.json`
   - Install "DxCore" from Board Manager
2. Select your board:
   - Tools → Board → DxCore → AVR DA-series or AVR DB-series
   - Tools → Chip → AVR128DA28 (or your variant)
3. Set clock speed:
   - Tools → Clock Speed → 24 MHz internal
4. Upload the sketch using UPDI programmer

## Testing

### With Serial Monitor (UART):
1. Connect USB-to-Serial adapter:
   - Adapter TX → AVR128 RX (PC1)
   - Adapter RX → AVR128 TX (PC0)
   - Common GND
2. Open serial monitor at **9600 baud**
3. Rotate potentiometer and observe voltage readings
4. Expected output:
   ```
   AVR128 ADC Example Started
   Reading analog input on PD0 (AIN0)
   
   ADC Value: 0 (0-4095)  Voltage: 0 mV
   ADC Value: 1024 (0-4095)  Voltage: 825 mV
   ADC Value: 2048 (0-4095)  Voltage: 1650 mV
   ADC Value: 4095 (0-4095)  Voltage: 3300 mV
   ```

### With Multimeter:
1. Measure voltage at PD0 with multimeter
2. Compare with voltage reading from serial output
3. Readings should match within ±10-50 mV (depending on reference accuracy)

### Visual Testing:
- LED on PA1 should blink at 1 Hz (500ms ON, 500ms OFF)
- Indicates ADC is actively sampling

## Understanding the Code

### Key Functions:

**`adc_init()`**
- Configures ADC reference voltage (VDD)
- Sets 12-bit resolution
- Configures clock prescaler (DIV16)
- Prepares input pin (PD0) for analog input

**`adc_read(channel)`**
- Selects ADC input channel
- Initiates conversion
- Waits for completion
- Returns 12-bit result (0-4095)

**`main()` loop**
- Reads ADC value
- Converts to millivolts: `voltage = (adc_value * VREF_mV) / 4096`
- Outputs via UART
- Toggles LED
- Repeats every 500ms

## Common Applications

### Sensor Reading:
- Temperature sensors (TMP36, LM35)
- Light sensors (photoresistor, LDR)
- Pressure sensors
- Humidity sensors
- Position sensors (potentiometer)

### Voltage Monitoring:
- Battery voltage monitoring
- Power supply monitoring (with voltage divider)
- Analog signal processing

### Control Systems:
- Closed-loop control (PID)
- Threshold detection
- Analog data acquisition

## Troubleshooting

### Problem: ADC readings are noisy or unstable
**Solutions:**
- Add decoupling capacitor (0.1µF) near VCC and GND pins
- Add capacitor (10-100nF) on analog input
- Use internal reference (2.048V) instead of VDD
- Enable oversampling in code
- Keep analog wires short and away from digital signals

### Problem: ADC always reads 0 or 4095
**Solutions:**
- Check that input voltage is within 0V to VREF range
- Verify input pin is configured correctly (not as output)
- Check reference voltage selection
- Verify potentiometer wiring

### Problem: Readings don't match expected voltage
**Solutions:**
- Verify reference voltage (VDD) is what you expect
- Check for voltage drop in power supply
- Calibrate using known reference voltage
- Consider temperature effects on ADC

### Problem: No UART output
**Solutions:**
- Verify UART pins (check datasheet for your variant)
- Check baud rate matches serial monitor setting
- Ensure TX pin is configured as output
- Try different UART pins (PORTA or PORTC)

## Advanced Features

### Oversampling for Higher Resolution
By taking multiple samples and averaging, you can achieve higher effective resolution:
```cpp
// 13-bit resolution (from 12-bit ADC)
uint32_t sum = 0;
for (int i = 0; i < 4; i++) {
    sum += adc_read(ADC_CHANNEL);
}
uint16_t result = sum >> 1;  // Divide by 2
```

### Free-Running Mode with Interrupts
For background sampling without polling:
```cpp
// Enable free-running mode
ADC0.CTRLA |= ADC_FREERUN_bm;
// Enable result ready interrupt
ADC0.INTCTRL = ADC_RESRDY_bm;
// Start first conversion
ADC0.COMMAND = ADC_STCONV_bm;
```

### Differential Measurements
For measuring small voltage differences:
```cpp
ADC0.MUXPOS = ADC_MUXPOS_AIN2_gc;  // Positive input
ADC0.MUXNEG = ADC_MUXNEG_AIN3_gc;  // Negative input
// Result is AIN2 - AIN3
```

### Window Comparator Mode
For automatic threshold detection:
```cpp
ADC0.WINLT = 1000;  // Lower threshold
ADC0.WINHT = 3000;  // Upper threshold
ADC0.CTRLE = ADC_WINCM_INSIDE_gc;  // Interrupt when inside window
```

## Resources

### Datasheets and Guides:
- [AVR128DA Datasheet](https://www.microchip.com/en-us/product/AVR128DA28)
- [AVR128DB Datasheet](https://www.microchip.com/en-us/product/AVR128DB28)
- [AVR128DA/DB Family User Guide](https://ww1.microchip.com/downloads/en/DeviceDoc/AVR128DA-Family-Data-Sheet-DS40002183.pdf)
- [TB3254: ADC Sampling Optimization](https://ww1.microchip.com/downloads/en/Appnotes/TB3254-ADC-Sampling-Optimization-90003254A.pdf)

### Tools:
- [DxCore (Arduino support for AVR DA/DB)](https://github.com/SpenceKonde/DxCore)
- [MPLAB X IDE](https://www.microchip.com/en-us/tools-resources/develop/mplab-x-ide)
- [AVR-GCC Compiler](https://www.microchip.com/en-us/tools-resources/develop/microchip-studio)

### Related Examples:
- ATmega1284 examples in this repository
- Microchip Code Examples: [GitHub](https://github.com/microchip-pic-avr-examples)

## Next Steps

After understanding this basic ADC example, explore:
1. **Multiple channels**: Read several sensors simultaneously
2. **DMA integration**: Use DMA for automatic data transfer
3. **Signal processing**: Implement filtering and averaging
4. **Sensor interfaces**: Interface specific sensors (temperature, pressure, etc.)
5. **Data logging**: Store readings to EEPROM or external memory
6. **Wireless transmission**: Send data via CAN, LIN, or wireless modules
