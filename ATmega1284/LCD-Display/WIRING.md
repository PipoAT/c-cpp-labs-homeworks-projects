# LCD Display Wiring Diagram

## Quick Reference Card

### Pin Connections Summary

| LCD Pin | Pin Name | Function         | Connect To              |
|---------|----------|------------------|-------------------------|
| 1       | VSS      | Ground           | GND                     |
| 2       | VDD      | Power (+5V)      | +5V                     |
| 3       | V0       | Contrast         | 10kΩ Pot (middle pin)   |
| 4       | RS       | Register Select  | ATmega1284 PC0 (Pin 22) |
| 5       | RW       | Read/Write       | GND                     |
| 6       | E        | Enable           | ATmega1284 PC1 (Pin 23) |
| 7       | DB0      | Data Bit 0       | Not Connected           |
| 8       | DB1      | Data Bit 1       | Not Connected           |
| 9       | DB2      | Data Bit 2       | Not Connected           |
| 10      | DB3      | Data Bit 3       | Not Connected           |
| 11      | DB4      | Data Bit 4       | ATmega1284 PC4 (Pin 26) |
| 12      | DB5      | Data Bit 5       | ATmega1284 PC5 (Pin 27) |
| 13      | DB6      | Data Bit 6       | ATmega1284 PC6 (Pin 28) |
| 14      | DB7      | Data Bit 7       | ATmega1284 PC7 (Pin 29) |
| 15      | A        | Backlight (+)    | +5V via 220Ω resistor   |
| 16      | K        | Backlight (-)    | GND                     |

## Breadboard Layout Suggestion

```
                        Power Rails
                    +5V ━━━━━━━━━━━━━ Red Rail
                    GND ━━━━━━━━━━━━━ Blue Rail


        10kΩ Potentiometer                    220Ω Resistor
        (Contrast Control)                    (Backlight)
              
         +5V ──┐                                 +5V ──┬─[220Ω]─> LCD Pin 15
               │                                       │
              ┌┴┐                                      │
              │ │  Turn this until                     │
              │ │  text is visible!                    │
              └┬┘                                      │
               ├──> LCD Pin 3 (V0)                     │
               │                                       │
         GND ──┘                              GND ─────┴────> LCD Pin 16


           ATmega1284P                           20x4 LCD Display
        ┌──────────────┐                    ┌──────────────────┐
        │              │                    │                  │
        │   PC0 ───────┼────────────────────┼──> RS (Pin 4)   │
        │   PC1 ───────┼────────────────────┼──> E  (Pin 6)   │
        │   PC4 ───────┼────────────────────┼──> D4 (Pin 11)  │
        │   PC5 ───────┼────────────────────┼──> D5 (Pin 12)  │
        │   PC6 ───────┼────────────────────┼──> D6 (Pin 13)  │
        │   PC7 ───────┼────────────────────┼──> D7 (Pin 14)  │
        │              │                    │                  │
        │   VCC ───────┼──── +5V Rail       │  VDD (Pin 2) <─  +5V
        │   GND ───────┼──── GND Rail       │  VSS (Pin 1) <─  GND
        │              │                    │  RW  (Pin 5) <─  GND
        └──────────────┘                    └──────────────────┘
```

## Step-by-Step Assembly Guide

### Step 1: Power Connections
1. Connect LCD Pin 1 (VSS) to GND
2. Connect LCD Pin 2 (VDD) to +5V
3. Connect LCD Pin 5 (RW) to GND

### Step 2: Contrast Potentiometer
1. Connect one outer pin of 10kΩ pot to +5V
2. Connect other outer pin of 10kΩ pot to GND
3. Connect middle pin of pot to LCD Pin 3 (V0)

### Step 3: Control Signals
1. Connect LCD Pin 4 (RS) to ATmega1284 PC0
2. Connect LCD Pin 6 (E) to ATmega1284 PC1

### Step 4: Data Lines
1. Leave LCD Pins 7-10 (DB0-DB3) not connected
2. Connect LCD Pin 11 (DB4) to ATmega1284 PC4
3. Connect LCD Pin 12 (DB5) to ATmega1284 PC5
4. Connect LCD Pin 13 (DB6) to ATmega1284 PC6
5. Connect LCD Pin 14 (DB7) to ATmega1284 PC7

### Step 5: Backlight (Optional but Recommended)
1. Connect 220Ω resistor between +5V and LCD Pin 15 (A)
2. Connect LCD Pin 16 (K) to GND

### Step 6: Microcontroller Power
1. Connect ATmega1284 VCC to +5V
2. Connect ATmega1284 GND to GND
3. Ensure all grounds are connected together

## Critical Notes

⚠️ **CONTRAST ADJUSTMENT**
- After powering on, you MUST adjust the contrast potentiometer
- Turn it slowly until you see text appear
- If you see solid black squares, adjust the pot
- This is the #1 reason for "my LCD doesn't work!"

⚠️ **WIRING CHECK**
- Double-check all connections before applying power
- Ensure no short circuits between +5V and GND
- Make sure data pins D4-D7 are in the correct order

⚠️ **4-BIT MODE**
- Only DB4-DB7 (Pins 11-14) are connected
- DB0-DB3 (Pins 7-10) remain unconnected
- This is normal and correct for 4-bit mode

## ATmega1284P DIP-40 Pinout

```
         ATmega1284P DIP-40 Package
        ┌─────────────────────────┐
  (XCK/T0) PB0  1  ┌───┐      40  PA0 (ADC0)
  (T1)     PB1  2  │   │      39  PA1 (ADC1)
  (AIN0/INT2) PB2  3  │   │      38  PA2 (ADC2)
  (AIN1/OC0A) PB3  4  │   │      37  PA3 (ADC3)
  (SS/OC0B) PB4  5  │   │      36  PA4 (ADC4)
  (MOSI)   PB5  6  │   │      35  PA5 (ADC5)
  (MISO)   PB6  7  │ A │      34  PA6 (ADC6)
  (SCK)    PB7  8  │ T │      33  PA7 (ADC7)
           RESET  9  │ m │      32  AREF
           VCC   10  │ e │      31  GND
           GND   11  │ g │      30  AVCC
           XTAL2 12  │ a │      29  PC7 ◄── LCD D7
           XTAL1 13  │   │      28  PC6 ◄── LCD D6
  (RXD0)   PD0  14  │ 1 │      27  PC5 ◄── LCD D5
  (TXD0)   PD1  15  │ 2 │      26  PC4 ◄── LCD D4
  (RXD1/INT0) PD2  16  │ 8 │      25  PC3
  (TXD1/INT1) PD3  17  │ 4 │      24  PC2
  (OC1B)   PD4  18  │   │      23  PC1 ◄── LCD Enable
  (OC1A)   PD5  19  │ P │      22  PC0 ◄── LCD RS
  (OC2B/ICP) PD6  20  └───┘      21  PD7 (OC2A)
        └─────────────────────────┘

  Legend:
  ◄── Indicates connection to LCD
```

## Testing Your Connections

### Power-On Test
1. Connect power to the circuit
2. LCD backlight should turn on (if connected)
3. Adjust contrast pot slowly
4. You should see black squares in the top row (this is normal before initialization)

### First Program Test
1. Upload the example code from Main.c
2. LCD should clear and show "ATmega1284 LCD"
3. If nothing appears, adjust contrast pot
4. If still nothing, verify all connections

## Common Mistakes to Avoid

❌ **Forgetting the contrast pot** - Most common issue!
❌ **Connecting RW to +5V instead of GND**
❌ **Swapping data pins** - Make sure D4→PC4, D5→PC5, etc.
❌ **Using 3.3V instead of 5V** - Both devices need 5V
❌ **Not connecting grounds together**
❌ **Forgetting backlight resistor** - Can damage backlight LED

## Wire Color Suggestions

For easier troubleshooting, use consistent colors:
- **Red**: +5V connections
- **Black**: GND connections
- **Yellow**: RS (Register Select)
- **Green**: E (Enable)
- **Blue**: Data lines (D4-D7)

This makes visual inspection much easier!

---

**Good luck with your LCD project!** 🎯
