/*
 * lcd.c
 *
 * HD44780 LCD Driver Implementation for ATmega1284
 * 
 * This file contains the implementation of LCD control functions
 * for HD44780-based displays in 4-bit mode.
 * 
 * Created: 1/29/2026
 * Author: Educational Example
 */ 

#include "lcd.h"

// Static variable to track display control state
static uint8_t display_control = LCD_DISPLAY_CONTROL | LCD_DISPLAY_ON | LCD_CURSOR_OFF | LCD_BLINK_OFF;

/*
 * ============================================================================
 * LOW-LEVEL FUNCTIONS
 * ============================================================================
 */

/**
 * @brief Sends an enable pulse to the LCD
 * 
 * The HD44780 requires a specific timing for the Enable pulse:
 * 1. Set E high
 * 2. Wait for at least 450ns (we use 1us to be safe)
 * 3. Set E low
 * 4. Wait for at least 37us for command execution
 * 
 * The Enable pulse tells the LCD to read the data on the data lines.
 */
void LCD_EnablePulse(void)
{
    // Set Enable pin HIGH
    LCD_PORT |= (1 << LCD_ENABLE_PIN);
    
    // Wait for minimum enable pulse width (450ns minimum, we use 1us)
    _delay_us(1);
    
    // Set Enable pin LOW - this triggers the LCD to read the data
    LCD_PORT &= ~(1 << LCD_ENABLE_PIN);
    
    // Wait for command execution time (37us minimum, we use 50us)
    _delay_us(50);
}

/**
 * @brief Sends a nibble (4 bits) to the LCD
 * 
 * In 4-bit mode, we only use the upper 4 data lines (D4-D7).
 * This function takes a 4-bit value and places it on these pins.
 * 
 * @param data The 4-bit data to send (only lower 4 bits are used)
 */
void LCD_SendNibble(uint8_t data)
{
    // Clear the data pins (D4-D7) while preserving other pins
    LCD_PORT &= ~((1 << LCD_D4_PIN) | (1 << LCD_D5_PIN) | 
                  (1 << LCD_D6_PIN) | (1 << LCD_D7_PIN));
    
    // Set data pins according to the nibble
    // We shift each bit to its corresponding pin position
    if (data & 0x01) LCD_PORT |= (1 << LCD_D4_PIN);  // Bit 0 -> D4
    if (data & 0x02) LCD_PORT |= (1 << LCD_D5_PIN);  // Bit 1 -> D5
    if (data & 0x04) LCD_PORT |= (1 << LCD_D6_PIN);  // Bit 2 -> D6
    if (data & 0x08) LCD_PORT |= (1 << LCD_D7_PIN);  // Bit 3 -> D7
    
    // Pulse the Enable pin to latch the data
    LCD_EnablePulse();
}

/*
 * ============================================================================
 * COMMAND AND DATA FUNCTIONS
 * ============================================================================
 */

/**
 * @brief Sends a command to the LCD
 * 
 * Commands control LCD operations like clearing the display, 
 * setting cursor position, etc.
 * 
 * The RS (Register Select) pin determines if we're sending a command (RS=0)
 * or data (RS=1). For commands, RS must be LOW.
 * 
 * In 4-bit mode, we send commands in two parts:
 * 1. Upper nibble (bits 7-4)
 * 2. Lower nibble (bits 3-0)
 * 
 * @param cmd The command byte to send
 */
void LCD_Command(uint8_t cmd)
{
    // Set RS to 0 for command mode
    LCD_PORT &= ~(1 << LCD_RS_PIN);
    
    // Send upper nibble (bits 7-4)
    LCD_SendNibble(cmd >> 4);
    
    // Send lower nibble (bits 3-0)
    LCD_SendNibble(cmd & 0x0F);
    
    // Most commands need 37us to execute, but some (like clear and home)
    // need up to 1.52ms. We use a conservative delay here.
    _delay_us(40);
}

/**
 * @brief Sends a data byte (character) to the LCD
 * 
 * Data represents actual characters to display on the screen.
 * The RS (Register Select) pin must be HIGH for data.
 * 
 * Like commands, data is sent in two nibbles in 4-bit mode.
 * 
 * @param data The character to display
 */
void LCD_Data(uint8_t data)
{
    // Set RS to 1 for data mode
    LCD_PORT |= (1 << LCD_RS_PIN);
    
    // Send upper nibble (bits 7-4)
    LCD_SendNibble(data >> 4);
    
    // Send lower nibble (bits 3-0)
    LCD_SendNibble(data & 0x0F);
    
    // Data write takes 37us minimum
    _delay_us(40);
}

/*
 * ============================================================================
 * INITIALIZATION FUNCTION
 * ============================================================================
 */

/**
 * @brief Initializes the LCD in 4-bit mode
 * 
 * This initialization sequence is critical and follows the HD44780 datasheet.
 * The timing and order of operations must be followed exactly.
 * 
 * Initialization Steps:
 * 1. Wait >40ms after power-on for LCD to stabilize
 * 2. Send special initialization sequence to enter 4-bit mode
 * 3. Configure display (lines, font)
 * 4. Turn display on
 * 5. Clear display
 * 6. Set entry mode
 */
void LCD_Init(void)
{
    // Configure all LCD pins as outputs
    // RS, Enable, and all data pins (D4-D7)
    LCD_DDR |= (1 << LCD_RS_PIN) | (1 << LCD_ENABLE_PIN) |
               (1 << LCD_D4_PIN) | (1 << LCD_D5_PIN) |
               (1 << LCD_D6_PIN) | (1 << LCD_D7_PIN);
    
    // Initialize all pins to LOW
    LCD_PORT &= ~((1 << LCD_RS_PIN) | (1 << LCD_ENABLE_PIN) |
                  (1 << LCD_D4_PIN) | (1 << LCD_D5_PIN) |
                  (1 << LCD_D6_PIN) | (1 << LCD_D7_PIN));
    
    // Wait for LCD to power up (>40ms after VDD reaches 4.5V)
    // We wait 50ms to be safe
    _delay_ms(50);
    
    /*
     * Special initialization sequence for 4-bit mode
     * This is required by the HD44780 datasheet
     */
    
    // First attempt: Send 0x03 to initialize (function set: 8-bit mode)
    LCD_SendNibble(0x03);
    _delay_ms(5);  // Wait >4.1ms
    
    // Second attempt: Send 0x03 again
    LCD_SendNibble(0x03);
    _delay_us(150);  // Wait >100us
    
    // Third attempt: Send 0x03 again
    LCD_SendNibble(0x03);
    _delay_us(150);
    
    // Now switch to 4-bit mode by sending 0x02
    LCD_SendNibble(0x02);
    _delay_us(150);
    
    /*
     * From this point on, we can use LCD_Command() to send full bytes
     * because the LCD is now in 4-bit mode
     */
    
    // Function Set: 4-bit mode, 2 lines, 5x8 dots
    // This works for both 2-line (16x2) and 4-line (20x4) displays
    LCD_Command(LCD_FUNCTION_SET | LCD_4BIT_MODE | LCD_2LINE | LCD_5x8_DOTS);
    _delay_us(40);
    
    // Display Control: Display ON, Cursor OFF, Blink OFF
    display_control = LCD_DISPLAY_CONTROL | LCD_DISPLAY_ON | LCD_CURSOR_OFF | LCD_BLINK_OFF;
    LCD_Command(display_control);
    _delay_us(40);
    
    // Clear Display
    LCD_Clear();
    
    // Entry Mode Set: Increment cursor, No display shift
    // This means the cursor moves right after each character
    LCD_Command(LCD_ENTRY_MODE_SET | LCD_ENTRY_LEFT | LCD_ENTRY_SHIFT_DEC);
    _delay_us(40);
}

/*
 * ============================================================================
 * HIGH-LEVEL USER FUNCTIONS
 * ============================================================================
 */

/**
 * @brief Clears the entire display
 * 
 * Clears all characters and returns cursor to position (0,0).
 * This is one of the slower commands, taking about 1.52ms.
 */
void LCD_Clear(void)
{
    LCD_Command(LCD_CLEAR_DISPLAY);
    // Clear command takes 1.52ms according to datasheet
    _delay_ms(2);
}

/**
 * @brief Moves cursor to home position (0,0)
 * 
 * Returns cursor to top-left corner without clearing display.
 * Also resets any display shifts.
 */
void LCD_Home(void)
{
    LCD_Command(LCD_RETURN_HOME);
    // Return home takes 1.52ms according to datasheet
    _delay_ms(2);
}

/**
 * @brief Positions the cursor at a specific row and column
 * 
 * The 20x4 LCD has a peculiar addressing scheme:
 * - Row 0: 0x00-0x13 (addresses 0-19)
 * - Row 1: 0x40-0x53 (addresses 64-83)
 * - Row 2: 0x14-0x27 (addresses 20-39)
 * - Row 3: 0x54-0x67 (addresses 84-103)
 * 
 * Note that rows 2 and 3 are NOT sequential in memory!
 * This is due to how the HD44780 maps DDRAM for 4-line displays.
 * 
 * @param row Row number (0-3)
 * @param col Column number (0-19)
 */
void LCD_SetCursor(uint8_t row, uint8_t col)
{
    uint8_t address;
    
    // Calculate DDRAM address based on row
    switch (row)
    {
        case 0:
            address = LCD_ROW_0_ADDR + col;
            break;
        case 1:
            address = LCD_ROW_1_ADDR + col;
            break;
        case 2:
            address = LCD_ROW_2_ADDR + col;
            break;
        case 3:
            address = LCD_ROW_3_ADDR + col;
            break;
        default:
            address = LCD_ROW_0_ADDR + col;  // Default to row 0 if invalid
            break;
    }
    
    // Set DDRAM address (bit 7 must be 1, hence the OR with 0x80)
    LCD_Command(LCD_SET_DDRAM_ADDR | address);
}

/**
 * @brief Prints a single character at the current cursor position
 * 
 * The cursor automatically advances after printing the character.
 * 
 * @param c The character to print
 */
void LCD_Putc(char c)
{
    LCD_Data(c);
}

/**
 * @brief Prints a null-terminated string at the current cursor position
 * 
 * Prints characters one by one until a null terminator ('\0') is encountered.
 * The cursor advances with each character.
 * 
 * Note: This function does NOT automatically wrap to the next line.
 * If the string is longer than the remaining columns, it may wrap oddly
 * or be truncated depending on the LCD's configuration.
 * 
 * @param str Pointer to the null-terminated string
 */
void LCD_Puts(const char *str)
{
    // Loop through each character until null terminator
    while (*str)
    {
        LCD_Data(*str);
        str++;
    }
}

/**
 * @brief Turns the display ON or OFF
 * 
 * When turned off, the display content remains in memory.
 * Turning it back on will restore the display.
 * This function preserves the current cursor and blink settings.
 * 
 * @param state 1 for ON, 0 for OFF
 */
void LCD_Display(uint8_t state)
{
    if (state)
    {
        // Turn display ON, preserve cursor and blink state
        display_control |= LCD_DISPLAY_ON;
    }
    else
    {
        // Turn display OFF, preserve cursor and blink state
        display_control &= ~LCD_DISPLAY_ON;
    }
    LCD_Command(display_control);
}

/**
 * @brief Controls the cursor visibility
 * 
 * The cursor appears as an underscore character at the current position.
 * This function preserves the current display and blink settings.
 * 
 * @param state 1 to show cursor, 0 to hide cursor
 */
void LCD_Cursor(uint8_t state)
{
    if (state)
    {
        // Turn cursor ON, preserve display and blink state
        display_control |= LCD_CURSOR_ON;
    }
    else
    {
        // Turn cursor OFF, preserve display and blink state
        display_control &= ~LCD_CURSOR_ON;
    }
    LCD_Command(display_control);
}

/**
 * @brief Controls cursor blinking
 * 
 * When enabled, the character at the cursor position blinks on and off.
 * This function preserves the current display and cursor settings.
 * 
 * @param state 1 to enable blinking, 0 to disable blinking
 */
void LCD_Blink(uint8_t state)
{
    if (state)
    {
        // Turn blink ON, preserve display and cursor state
        display_control |= LCD_BLINK_ON;
    }
    else
    {
        // Turn blink OFF, preserve display and cursor state
        display_control &= ~LCD_BLINK_ON;
    }
    LCD_Command(display_control);
}
