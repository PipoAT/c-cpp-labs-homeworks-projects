/*
 * Main.c
 *
 * Introductory Example Program for 20x4 LCD Display with ATmega1284
 * 
 * This program demonstrates basic LCD operations including:
 * - Initialization
 * - Displaying text on different rows
 * - Clearing the display
 * - Cursor positioning
 * - Simple animations
 * 
 * Hardware: ATmega1284 + 20x4 LCD with HD44780 controller
 * 
 * Created: 1/29/2026
 * Author: Educational Example
 */ 

#include "lcd.h"
#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>

/**
 * @brief Example 1: Display a welcome message
 * 
 * This demonstrates basic text display on multiple rows.
 */
void Example_WelcomeMessage(void)
{
    LCD_Clear();
    
    // Display text on each row of the 20x4 display
    LCD_SetCursor(0, 0);  // Row 0, Column 0
    LCD_Puts("  ATmega1284 LCD  ");
    
    LCD_SetCursor(1, 0);  // Row 1, Column 0
    LCD_Puts("    20x4 Display    ");
    
    LCD_SetCursor(2, 0);  // Row 2, Column 0
    LCD_Puts("   Hello World!    ");
    
    LCD_SetCursor(3, 0);  // Row 3, Column 0
    LCD_Puts(" Learning Embedded ");
    
    // Display for 3 seconds
    _delay_ms(3000);
}

/**
 * @brief Example 2: Display counter on LCD
 * 
 * This shows how to display numbers using sprintf and LCD_Puts.
 */
void Example_Counter(void)
{
    char buffer[21];  // Buffer for formatting strings (20 chars + null)
    
    LCD_Clear();
    LCD_SetCursor(0, 0);
    LCD_Puts("  Counter Example  ");
    
    // Count from 0 to 9
    for (uint8_t i = 0; i <= 9; i++)
    {
        LCD_SetCursor(2, 0);
        sprintf(buffer, "      Count: %d      ", i);
        LCD_Puts(buffer);
        _delay_ms(500);
    }
    
    _delay_ms(1000);
}

/**
 * @brief Example 3: Cursor demonstration
 * 
 * This shows how to control cursor visibility and blinking.
 */
void Example_CursorDemo(void)
{
    LCD_Clear();
    LCD_SetCursor(0, 0);
    LCD_Puts("Cursor Demo:");
    
    // Show cursor without blinking
    LCD_SetCursor(2, 5);
    LCD_Puts("Cursor ON");
    LCD_Cursor(1);
    _delay_ms(2000);
    
    // Show blinking cursor
    LCD_SetCursor(2, 5);
    LCD_Puts("Blink  ON");
    LCD_Blink(1);
    _delay_ms(2000);
    
    // Hide cursor
    LCD_SetCursor(2, 5);
    LCD_Puts("Cursor OFF");
    LCD_Cursor(0);
    LCD_Blink(0);
    _delay_ms(2000);
}

/**
 * @brief Example 4: Text scrolling animation
 * 
 * This creates a simple text scrolling effect by updating positions.
 */
void Example_ScrollingText(void)
{
    const char* message = "ATmega1284";
    uint8_t messageLen = 10;
    uint8_t row = 2;
    
    LCD_Clear();
    LCD_SetCursor(0, 0);
    LCD_Puts("  Scrolling Text  ");
    
    // Scroll text from right to left
    for (int8_t pos = LCD_COLS - 1; pos >= -messageLen; pos--)
    {
        // Clear the row
        LCD_SetCursor(row, 0);
        LCD_Puts("                    ");
        
        // Display message at current position
        if (pos >= 0)
        {
            LCD_SetCursor(row, pos);
            LCD_Puts(message);
        }
        else if (pos > -messageLen)
        {
            // Message is partially off-screen on the left
            LCD_SetCursor(row, 0);
            LCD_Puts(message + (-pos));
        }
        
        _delay_ms(150);
    }
    
    _delay_ms(500);
}

/**
 * @brief Example 5: Display sensor-like data
 * 
 * This simulates displaying sensor readings - useful template for real projects.
 */
void Example_SensorDisplay(void)
{
    char buffer[21];
    
    LCD_Clear();
    LCD_SetCursor(0, 0);
    LCD_Puts("==== Sensor Data ====");
    
    // Simulate temperature readings
    for (uint8_t i = 0; i < 10; i++)
    {
        uint8_t temp = 20 + i;  // Simulated temperature
        uint8_t humidity = 45 + (i * 2);  // Simulated humidity
        
        LCD_SetCursor(1, 0);
        sprintf(buffer, "Temp:     %d C      ", temp);
        LCD_Puts(buffer);
        
        LCD_SetCursor(2, 0);
        sprintf(buffer, "Humidity: %d%%      ", humidity);
        LCD_Puts(buffer);
        
        LCD_SetCursor(3, 0);
        sprintf(buffer, "Reading #%d         ", i + 1);
        LCD_Puts(buffer);
        
        _delay_ms(800);
    }
    
    _delay_ms(1000);
}

/**
 * @brief Example 6: Character positioning demo
 * 
 * This demonstrates precise character positioning across all rows and columns.
 */
void Example_PositioningDemo(void)
{
    LCD_Clear();
    
    // Draw a border pattern
    LCD_SetCursor(0, 0);
    LCD_Puts("********************");
    LCD_SetCursor(3, 0);
    LCD_Puts("********************");
    
    // Display column numbers
    LCD_SetCursor(1, 0);
    LCD_Puts("0    5    10   15  ");
    
    // Display a moving character
    LCD_SetCursor(2, 0);
    LCD_Puts("Position: ");
    
    for (uint8_t col = 0; col < LCD_COLS; col++)
    {
        char buffer[21];
        
        // Clear row 2
        LCD_SetCursor(2, 0);
        LCD_Puts("                    ");
        
        // Display position
        LCD_SetCursor(2, 0);
        sprintf(buffer, "Position: %d", col);
        LCD_Puts(buffer);
        
        // Place marker
        LCD_SetCursor(1, col);
        LCD_Putc('X');
        
        _delay_ms(200);
        
        // Remove marker
        LCD_SetCursor(1, col);
        if (col == 5 || col == 10 || col == 15)
            LCD_Putc('5' + (col / 5));  // Restore column marker
        else if (col == 0)
            LCD_Putc('0');
        else
            LCD_Putc(' ');
    }
    
    _delay_ms(1000);
}

/**
 * @brief Main function
 * 
 * Initializes the LCD and runs through various demonstration examples.
 * This program runs in an infinite loop, cycling through all examples.
 */
int main(void)
{
    // Initialize the LCD
    // This must be called before any other LCD functions
    LCD_Init();
    
    // Main program loop
    while (1)
    {
        // Run all examples in sequence
        
        Example_WelcomeMessage();
        
        Example_Counter();
        
        Example_CursorDemo();
        
        Example_ScrollingText();
        
        Example_SensorDisplay();
        
        Example_PositioningDemo();
        
        // Brief pause before repeating
        LCD_Clear();
        LCD_SetCursor(1, 0);
        LCD_Puts("   Restarting...   ");
        _delay_ms(2000);
    }
    
    return 0;
}
