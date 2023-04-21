/*
 * WalkingLEDFunction.h
 *
 * Created: 1/5/2023 9:47:08 AM
 *  Author: apipo
 */ 

#include <avr/io.h>
#include <avr/delay.h>
#ifndef WALKINGLEDFUNCTION_H_
#define WALKINGLEDFUNCTION_H_
// Defined constants
#include <avr/io.h>
#define OHMS_LAW_VOLTAGE(_I, _R)	(_I*_R)
#define F_CPU 12000000UL

#define ON_OFF_OUTPUT_REGISTER		PORTD // Defines what register program needs to read/identify as output, define direction for registers.
#define ON_OFF_READ_REGISTER		PIND
#define ON_OFF_DIRECTION_REGISTER	DDRD

#define ON_OFF_OUTPUT_REGISTER_2	PORTD
#define ON_OFF_READ_REGISTER_2		PIND
#define ON_OFF_DIRECTION_REGISTER_2	DDRD

#define ON_OFF_BTN_POSITION			2 // Location of first button with PORT D
#define ON_OFF_BTN_POSITION_2		3 // Location of second button with PORT D
#define LED_POSITION				0


#include <avr/io.h>
#include <avr/delay.h>

/**
* \brief Program for blinking when the connected button is pressed
*
*/
void WalkingBlinkOnButtonPressProgram()
{
	//Variables
	unsigned char uchrCurrentMoveLeftButtonPinState = 0; //The current state of the move left button pin
	unsigned char uchrPreviousMoveLeftButtonPinState = 0; //The previous state of the move left button pin
	unsigned char uchrCurrentMoveRightButtonPinState = 0; //The current state of the move right button pin
	unsigned char uchrPreviousMoveRightButtonPinState = 0; //The previous state of the move right button pin
	unsigned char uchrActiveLedIndex = 0; //Index for which LED is currently active

	//The pin positions of the LED's to walk through
	const unsigned char LED_ORDERED_PIN_POSITIONS[] =
	{
		4,5,6,7
	};

	//Pre calculate the size of the ordered pin positions. Saves resources to pre calculate before entering loop
	const unsigned char LED_COUNT = sizeof(LED_ORDERED_PIN_POSITIONS);
	
	//Initialize your I/O pins as 0 aka LOW
	PORTA = 0;
	PORTB = 0;
	PORTC = 0;
	PORTD = 0;
	
	//Initialize your pins Directions, input vs output. This register will control which way your current will flow. On this MCU (micro controller unit)...
	// 1 aka HIGH will be your value for OUTPUT on these registers
	
	//All directions on ports, fully output. 0xFF, 0b11111111, 255
	DDRA = 0xFF;
	DDRB = 0xFF;
	DDRC = 0xFF;
	DDRD = 0xFF;


	//Flash the LED's several times to make sure the system is alive and well
	for(uint8_t i = 0; i < 5; i++)
	{
		PORTD ^= 0xFF;
		_delay_ms(1000);
	}

	//Clear any active LEDS
	PORTD = 0;
	
	//Setup the move left and move right buttons as input PULL UP (google pull up resistor for more context), waiting to read ground/be pulled low
	DDRD &= ~(1 << 3 | 1 << 2);
	PORTD |= (1 << 3 | 1 << 2);

	
	//Program loop
	for(;;)
	{
		//Read the current pin states
		uchrCurrentMoveLeftButtonPinState = ((PIND & (1 << 2)) >> 2);
		uchrCurrentMoveRightButtonPinState = ((PIND & (1 << 3)) >> 3);
		
		//If the current move left state is different than the previous state...
		if(uchrCurrentMoveLeftButtonPinState != uchrPreviousMoveLeftButtonPinState)
		{
			//save the new state
			uchrPreviousMoveLeftButtonPinState = uchrCurrentMoveLeftButtonPinState;

			//If the current state is low, meaning the button was pressed and has connected...
			if(uchrCurrentMoveLeftButtonPinState == 0)
			{
				//Set the currently active LED to OFF
				PORTD &= ~(1 << LED_ORDERED_PIN_POSITIONS[uchrActiveLedIndex]);

				//If the index is greater than 0...
				if(uchrActiveLedIndex > 0)
				{
					//Subtract from the index
					uchrActiveLedIndex--;
				}
				//else...
				else
				{
					//Reset the index to the size of our pin array - 1
					uchrActiveLedIndex = (LED_COUNT - 1);
				}

				
			}
		}
		//else If the current move right state is different than the previous state...
		else if(uchrCurrentMoveRightButtonPinState != uchrPreviousMoveRightButtonPinState)
		{
			//save the new state
			uchrPreviousMoveRightButtonPinState = uchrCurrentMoveRightButtonPinState;

			//If the current state is low, meaning the button was pressed and has connected...
			if(uchrCurrentMoveRightButtonPinState == 0)
			{
				//Set the currently active LED to OFF
				PORTD &= ~(1 << LED_ORDERED_PIN_POSITIONS[uchrActiveLedIndex]);

				//If the index is less than the size of our pin array...
				if(uchrActiveLedIndex < (LED_COUNT-1))
				{
					//Add to the index
					uchrActiveLedIndex++;
				}
				//else...
				else
				{
					//Reset the index to 0
					uchrActiveLedIndex = 0;
				}

				
			}

			
		}
		
		//Set the currently active LED to toggle
		PORTD ^= (1 << LED_ORDERED_PIN_POSITIONS[uchrActiveLedIndex]);
		
		//"Debounce" to allow the user time to release the button. This entire setup is the same as using an "On Input UP/ On Keypress Up" event.
		_delay_ms(100);
	}
}




#endif /* WALKINGLEDFUNCTION_H_ */