/*
 * BlinkingLEDFunction.h
 *
 * Created: 1/5/2023 9:37:13 AM
 *  Author: apipo
 */ 


#ifndef BLINKINGLEDFUNCTION_H_
#define BLINKINGLEDFUNCTION_H_

#define OHMS_LAW_VOLTAGE(_I, _R)	(_I*_R)



//This needs included with every AVR project
#include <avr/io.h>
#include <avr/delay.h>

//Frequency for the CPU/Micro controller. 12 MHz aka 12 million hertz
#define F_CPU 12000000UL

void BlinkingLED()
{
	//Variables
	unsigned short ushtCurrentDelayTime = 500;
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
	//Your program loop.
	while (1)
	{
		//Toggle the value 1 (0b00000001, 0x01, (1 << 0) to toggle the state of PORTB's pin 0. This will change the voltage it is outputting on each iteration...
		//from ~0 volts to ~5 volts.
		PORTA ^= 1;
		//Using delay for milliseconds from avr delay header. 1000 milliseconds = 1 second
		//Since this MCU is an 8 bit MCU, it only handle 8 bits at a time. This means that using byte sized data (such as a char or unsigned char)...
		//can be more efficient at times, especially your for loops, in terms of speed. In small devices, it can be best to use the smallest possible data types
		//and any data that can be calculated before the main loop or precalculated and hard coded into variables/macros

		//Maybe not the best loop, but its a delay loop
		for(uint16_t i = 0; i < ushtCurrentDelayTime; i++)
		{
			//Delay for ushtCurrentDelayTime delay time
			_delay_ms(1);
		}
		
		//If delay greater than 25...
		if(ushtCurrentDelayTime > 25)
		{
			//Subtract from the delay time
			ushtCurrentDelayTime -= 10;
		}
		//Else...
		else
		{
			//Reset variable to 1 half second
			ushtCurrentDelayTime = 500;
		}
	}
}



#endif /* BLINKINGLEDFUNCTION_H_ */