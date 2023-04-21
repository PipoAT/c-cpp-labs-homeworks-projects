/*
 * main.cpp
 *
 * Created: 1/5/2023 12:27:08 PM
 *  Author: apipo
 */ 

// Brief: This program is designed to take an user input from a 3 by 4 keypad
// and will make the green LED blink if the input is between one and five and blink that many times
// If outside of 1-5 range, a solid LED light will come up to indicate an invalid input until valid input is received
// If * is selected, it will toggle between IDLE and active states/modes

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/atomic.h>
#include <avr/delay.h>
									// include helper files
#include "config.h"
#include "mcuUtils.h"
#include "mcuDelays.h"
#include "ckeypadMatrix.h"
#include "mcuPinUtils.h"



#define IDLEBUTTONOR     PORTD	// defines IDLE/ON button PORT/Location/Instructions
#define IDLEBUTTONRR     PORTD
#define IDLEBUTTONDR     PORTD
#define IDLEBUTTONL      1


	

const unsigned char m_uchrKeypdMatrixColumnPins[KP_COLUMNS] = {0, 1, 2}; // defines pin locations for columns, rows
const unsigned char m_uchrKeypdMatrixRowPins[KP_ROWS] = {3, 4, 5, 6};
const unsigned char m_uchrKeypadMatrixValues[KP_ROWS][KP_COLUMNS] = { // defines keypad set up (it is in a reverse order)
	
	{
		35, 48, 42 // ASCII values
	},			   // # 0 *
	{
		57, 56, 55 // 9 8 7
	},
	{
		54, 53, 52 // 6 5 4
	},
	{
		51, 50, 49 // 3 2 1
	}
};


unsigned char ScanKeyPad() {
	
	unsigned char currentKeypress = kp_Scan_const(m_uchrKeypdMatrixColumnPins, m_uchrKeypdMatrixRowPins, m_uchrKeypadMatrixValues);
	return currentKeypress; // calls function in ckeypadMatrix.c
}

 
int main(void) {

	PORTB = 0;			// set PORT w/ DIRECTIONS to initialize
	DDRB = 0xff;
	PORTC = 0;
	DDRC = 0xff;
	PORTD = 0xFF;			// LED on
	DDRD = 0xff;

	IDLEBUTTONOR |= (1 << IDLEBUTTONL); // bitwise functions OR and left shifting
	IDLEBUTTONDR &= ~(1 << IDLEBUTTONL); //bitwise functions using AND, NOT, and left shifting
	
	for(;;) {	

		_delay_ms(2000);		// Delay to allow user input
		
		unsigned char value = 'A';				// initialize the variable
		while (value == 'A') {					// initializes the scanning of keypad
			value = ScanKeyPad();
		}
		
		
		if (value > 53) {						// after scanning, if values are greater than 5 or less than 1. Turn LED SOLID for 1 sec
			
			PORTC ^= 0xFF;
			_delay_ms(1000);
		}
		
		else if (value == 35) {					// triggers PORTC LED if # is pressed
			PORTC ^= 0xFF;
			_delay_ms(500);
			
		}
		
		else if (value == 42) {
			PORTC = 0x00;						// Sets * as IDLE button and will go into IDLE and make LED blink if pressed
			int IDLEvalue = 42;
			while (IDLEvalue == 42) {
				PORTD ^= 0xFF;
				_delay_ms(2000);
				int newIDLEvalue = ScanKeyPad();	// if pressed while in IDLE, * makes LED solid and go into active mode
				if (newIDLEvalue == 42) {
					break;
				}
			}
		}
		
			
		else if (value < 49) {	
			PORTD = 0xFF;								// Solid LED for invalid inputs. Turns off if valid input is received
			
		} 
		
		else {								// if between 1 and 5, perform blinking LED
			PORTC = 0x00;
			short valuedec = value - 0x30;				// converting ASCII values to associated decimal form for for loop
			for(int i = 0; i < valuedec; i++) {
				
				PORTB = 0xFF;				// Would optimize however it causes bug if I do ^= as it would not blink number of times properly
				_delay_ms(2000);
				PORTB = 0x00;
				_delay_ms(2000);
			}
		}
	}
}
	

		
	

