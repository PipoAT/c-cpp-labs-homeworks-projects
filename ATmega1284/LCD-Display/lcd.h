/*
 * lcd.h
 *
 * HD44780 LCD Driver for ATmega1284
 * 
 * This library provides functions to control a standard 20x4 (or 16x2) LCD display
 * using the HD44780 controller in 4-bit mode.
 * 
 * Created: 1/29/2026
 * Author: Educational Example
 */ 

#ifndef LCD_H_
#define LCD_H_

// Frequency for the CPU/Micro controller. 12 MHz aka 12 million hertz
// Must be defined before including delay.h
#define F_CPU 12000000UL

// This needs included with every AVR project
#include <avr/io.h>
#include <util/delay.h>

/*
 * ============================================================================
 * HARDWARE WIRING CONFIGURATION
 * ============================================================================
 * 
 * LCD Pin Connections to ATmega1284:
 * -----------------------------------
 * LCD Pin 1  (VSS)  -> GND (Ground)
 * LCD Pin 2  (VDD)  -> +5V (Power)
 * LCD Pin 3  (V0)   -> Potentiometer middle pin (10K pot for contrast control)
 *                      - One end of pot to +5V, other end to GND
 * LCD Pin 4  (RS)   -> ATmega1284 Pin PC0 (PORTC bit 0) - Register Select
 * LCD Pin 5  (RW)   -> GND (We only write to LCD, no reading)
 * LCD Pin 6  (E)    -> ATmega1284 Pin PC1 (PORTC bit 1) - Enable
 * LCD Pin 7  (DB0)  -> Not Connected (4-bit mode uses DB4-DB7 only)
 * LCD Pin 8  (DB1)  -> Not Connected
 * LCD Pin 9  (DB2)  -> Not Connected
 * LCD Pin 10 (DB3)  -> Not Connected
 * LCD Pin 11 (DB4)  -> ATmega1284 Pin PC4 (PORTC bit 4) - Data bit 4
 * LCD Pin 12 (DB5)  -> ATmega1284 Pin PC5 (PORTC bit 5) - Data bit 5
 * LCD Pin 13 (DB6)  -> ATmega1284 Pin PC6 (PORTC bit 6) - Data bit 6
 * LCD Pin 14 (DB7)  -> ATmega1284 Pin PC7 (PORTC bit 7) - Data bit 7
 * LCD Pin 15 (A)    -> +5V through 220Ω resistor (Backlight Anode)
 * LCD Pin 16 (K)    -> GND (Backlight Cathode)
 * 
 * 
 * IMPORTANT NOTES:
 * ---------------
 * 1. The contrast potentiometer (Pin 3) is CRITICAL - without it, you won't
 *    see any characters on the display even if everything else is correct.
 * 
 * 2. We're using 4-bit mode to save microcontroller pins. This means we send
 *    data in two nibbles (4 bits at a time) instead of 8 bits at once.
 * 
 * 3. RW (Read/Write) pin is grounded because we only write to the LCD.
 *    In more advanced applications, you could read the busy flag.
 * 
 * 4. The backlight resistor (220Ω) protects the backlight LED. Check your
 *    LCD's datasheet - some displays have built-in resistors.
 * 
 * 5. All connections should be as short as possible to minimize noise,
 *    especially for the Enable (E) line.
 */

// LCD Pin Definitions - Change these if you use different pins
#define LCD_RS_PIN      0       // Register Select on PC0
#define LCD_ENABLE_PIN  1       // Enable on PC1
#define LCD_D4_PIN      4       // Data bit 4 on PC4
#define LCD_D5_PIN      5       // Data bit 5 on PC5
#define LCD_D6_PIN      6       // Data bit 6 on PC6
#define LCD_D7_PIN      7       // Data bit 7 on PC7

// LCD Port - All control and data pins are on PORTC
#define LCD_PORT        PORTC
#define LCD_DDR         DDRC

// LCD Commands - HD44780 instruction set
#define LCD_CLEAR_DISPLAY       0x01    // Clear entire display
#define LCD_RETURN_HOME         0x02    // Return cursor to home position
#define LCD_ENTRY_MODE_SET      0x04    // Set cursor move direction
#define LCD_DISPLAY_CONTROL     0x08    // Display ON/OFF control
#define LCD_CURSOR_SHIFT        0x10    // Cursor or display shift
#define LCD_FUNCTION_SET        0x20    // Interface length, lines, font
#define LCD_SET_CGRAM_ADDR      0x40    // Set CGRAM address
#define LCD_SET_DDRAM_ADDR      0x80    // Set DDRAM address (cursor position)

// Entry Mode Flags
#define LCD_ENTRY_RIGHT         0x00    // Entry from right
#define LCD_ENTRY_LEFT          0x02    // Entry from left
#define LCD_ENTRY_SHIFT_INC     0x01    // Shift display on entry
#define LCD_ENTRY_SHIFT_DEC     0x00    // Don't shift display on entry

// Display Control Flags
#define LCD_DISPLAY_ON          0x04    // Display ON
#define LCD_DISPLAY_OFF         0x00    // Display OFF
#define LCD_CURSOR_ON           0x02    // Cursor ON
#define LCD_CURSOR_OFF          0x00    // Cursor OFF
#define LCD_BLINK_ON            0x01    // Blinking cursor ON
#define LCD_BLINK_OFF           0x00    // Blinking cursor OFF

// Function Set Flags
#define LCD_8BIT_MODE           0x10    // 8-bit interface
#define LCD_4BIT_MODE           0x00    // 4-bit interface
#define LCD_2LINE               0x08    // 2 or 4 line display
#define LCD_1LINE               0x00    // 1 line display
#define LCD_5x10_DOTS           0x04    // 5x10 dot character font
#define LCD_5x8_DOTS            0x00    // 5x8 dot character font

// Display size constants for 20x4 LCD
#define LCD_ROWS                4       // Number of rows
#define LCD_COLS                20      // Number of columns

// Row starting addresses for 20x4 LCD
// These are the DDRAM addresses where each row starts
#define LCD_ROW_0_ADDR          0x00    // Row 0 starts at address 0x00
#define LCD_ROW_1_ADDR          0x40    // Row 1 starts at address 0x40
#define LCD_ROW_2_ADDR          0x14    // Row 2 starts at address 0x14
#define LCD_ROW_3_ADDR          0x54    // Row 3 starts at address 0x54

/*
 * ============================================================================
 * FUNCTION PROTOTYPES
 * ============================================================================
 */

/**
 * @brief Sends an enable pulse to the LCD
 * 
 * The HD44780 controller requires a pulse on the Enable pin to latch data.
 * This creates a high-to-low transition with appropriate timing.
 */
void LCD_EnablePulse(void);

/**
 * @brief Sends a nibble (4 bits) to the LCD
 * 
 * In 4-bit mode, we send data in two parts: upper nibble then lower nibble.
 * 
 * @param data The 4-bit data to send (only lower 4 bits are used)
 */
void LCD_SendNibble(uint8_t data);

/**
 * @brief Sends a command to the LCD
 * 
 * Commands control the LCD's operation (clear, cursor position, etc.)
 * RS pin must be LOW for commands.
 * 
 * @param cmd The command byte to send
 */
void LCD_Command(uint8_t cmd);

/**
 * @brief Sends a data byte (character) to the LCD
 * 
 * Data is what actually appears on the screen.
 * RS pin must be HIGH for data.
 * 
 * @param data The character to display
 */
void LCD_Data(uint8_t data);

/**
 * @brief Initializes the LCD in 4-bit mode
 * 
 * This function performs the initialization sequence required by the HD44780.
 * The sequence is timing-critical and follows the datasheet specifications.
 * 
 * Configuration:
 * - 4-bit mode
 * - 2 lines (works for 4-line displays too)
 * - 5x8 dot character font
 * - Display ON
 * - Cursor OFF
 * - Blink OFF
 */
void LCD_Init(void);

/**
 * @brief Clears the entire display
 * 
 * Clears all characters and returns cursor to home position (0,0).
 * This operation takes about 1.52ms according to the HD44780 datasheet.
 */
void LCD_Clear(void);

/**
 * @brief Moves cursor to home position (0,0)
 * 
 * Returns cursor to the top-left corner without clearing the display.
 * This operation takes about 1.52ms according to the HD44780 datasheet.
 */
void LCD_Home(void);

/**
 * @brief Positions the cursor at a specific row and column
 * 
 * @param row Row number (0-3 for 20x4 display)
 * @param col Column number (0-19 for 20x4 display)
 */
void LCD_SetCursor(uint8_t row, uint8_t col);

/**
 * @brief Prints a single character at the current cursor position
 * 
 * @param c The character to print
 */
void LCD_Putc(char c);

/**
 * @brief Prints a null-terminated string at the current cursor position
 * 
 * The cursor advances with each character. If the string exceeds the row width,
 * it may wrap or be truncated depending on LCD configuration.
 * 
 * @param str Pointer to the null-terminated string
 */
void LCD_Puts(const char *str);

/**
 * @brief Turns the display ON or OFF
 * 
 * When OFF, the display content is retained in memory.
 * 
 * @param state 1 for ON, 0 for OFF
 */
void LCD_Display(uint8_t state);

/**
 * @brief Controls the cursor visibility
 * 
 * @param state 1 to show cursor, 0 to hide cursor
 */
void LCD_Cursor(uint8_t state);

/**
 * @brief Controls cursor blinking
 * 
 * @param state 1 to enable blinking, 0 to disable blinking
 */
void LCD_Blink(uint8_t state);

#endif /* LCD_H_ */
