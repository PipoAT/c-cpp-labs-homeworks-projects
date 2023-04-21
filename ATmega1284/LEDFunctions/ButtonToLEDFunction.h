/*
 * ButtonToLEDFunction.h
 *
 * Created: 1/5/2023 9:44:13 AM
 *  Author: apipo
 */ 

#include <avr/io.h>
#include <avr/delay.h>
#ifndef BUTTONTOLEDFUNCTION_H_
#define BUTTONTOLEDFUNCTION_H_

#define OHMS_LAW_VOLTAGE(_I, _R)	(_I*_R)
#define F_CPU 12000000UL

#define ON_OFF_OUTPUT_REGISTER		PORTA
#define ON_OFF_READ_REGISTER		PINA
#define ON_OFF_DIRECTION_REGISTER	DDRA
#define ON_OFF_OUTPUT_REGISTER_2	PORTA
#define ON_OFF_READ_REGISTER_2		PINA
#define ON_OFF_DIRECTION_REGISTER_2	DDRA

#define ON_OFF_BTN_POSITION			5
#define ON_OFF_BTN_POSITION_2		6
#define LED_POSITION				0

void ButtonToLedProgram()
{
	//Variables
	unsigned char uchrCurrentOnOffButtonPinState = 0; //The current state of the on off button pin
	unsigned char uchrCurrentOnOffButtonPinState2 = 0; //The current state of the on off button pin
	unsigned char uchrPreviousOnOffButtonPinState = 0; //The previous state of the on off button pin
	unsigned char uchrPreviousOnOffButtonPinState2 = 0; //The previous state of the on off button pin
	unsigned char uchrCurrentLEDState = 0; //The state the LED should be at
	
	//Initialize your I/O pins as 0 aka LOW
	PORTA = 0;
	PORTB = 0;
	PORTC = 0;
	PORTD = 0;
	
	//Initialize your pins Directions, input vs output. This register will control which way your current will flow. On this MCU (micro controller unit)...
	// 1 aka HIGH will be your value for OUTPUT on these registers
	
	//All directions on ports, fully output. 0xFF, 0b11111111, 255
	DDRA = 0xff;
	DDRB = 0xff;
	DDRC = 0xff;
	DDRD = 0xff;
	
	//Setup the associated control button as input, HIGH, waiting to read ground
	ON_OFF_OUTPUT_REGISTER |= (1 << ON_OFF_BTN_POSITION); // bitwise functions OR and left shifting
	ON_OFF_DIRECTION_REGISTER &= ~(1 << ON_OFF_BTN_POSITION); //bitwise functions using AND, NOT, and left shifting
	ON_OFF_OUTPUT_REGISTER_2 |= (1 << ON_OFF_BTN_POSITION_2);
	ON_OFF_DIRECTION_REGISTER_2 &= ~(1 << ON_OFF_BTN_POSITION_2);
	
	//Program loop
	for(;;)
	{
		//Read the current pin state
		uchrCurrentOnOffButtonPinState = ((ON_OFF_READ_REGISTER & (1 << ON_OFF_BTN_POSITION)) >> ON_OFF_BTN_POSITION);
		
		//If the current on/off state is different than the previous state...
		if(uchrCurrentOnOffButtonPinState != uchrPreviousOnOffButtonPinState)
		{
			//save the new state
			uchrPreviousOnOffButtonPinState = uchrCurrentOnOffButtonPinState;
		}
		
		

		
		// Checking if state of the button is the same as the previous state, if not, it will update for the second button
		uchrCurrentLEDState = PIND;
		uchrCurrentOnOffButtonPinState2 = ((ON_OFF_READ_REGISTER_2 & (1 << ON_OFF_BTN_POSITION_2)) >> ON_OFF_BTN_POSITION_2); // uses bitwise AND as shifting based on known positions
		if (uchrCurrentOnOffButtonPinState2 != uchrPreviousOnOffButtonPinState2) {
			uchrPreviousOnOffButtonPinState2 = uchrCurrentOnOffButtonPinState2;
		}
		
		unsigned char newstate = uchrCurrentOnOffButtonPinState ^= 1;
		unsigned char newstate2 = uchrCurrentOnOffButtonPinState2 ^= 1; // XOR operator to determine and analyze the state of the button(s)
		
		//Toggle the LEDs
		if (newstate2 == 1) { // 1 is pressed, 2 is not pressed

			// for loop to run sequence if second button is hit
			
			PORTA = 0x8C; // PORT D value
			_delay_ms(100);
			PORTA = 0x1C; // PORT D Value
			_delay_ms(100);
			
			
			
			
		}
		
		else if (newstate == 1) { // for loop to run sequence if first button is hit
			PORTA = 0x1C; // LED 1
			_delay_ms(1000);
			PORTA = 0x2C; // LED 2
			_delay_ms(1000);
			PORTA = 0x4C;
			_delay_ms(1000); // LED 3
			PORTA = 0x8C;
			_delay_ms(1000); // LED 4
			
			
		}
		
		
		
		// to remove finger from clicking the button. Give time for the user to release the button
		_delay_ms(100);
		
	}
}




#endif /* BUTTONTOLEDFUNCTION_H_ */