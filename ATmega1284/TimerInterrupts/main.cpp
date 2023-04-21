/*
 * AVR Timer Interrupts.cpp
 *
 * Created: 1/6/2023 12:05:05 PM
 * Author : apipo
 */ 



#include <avr/io.h>
#include <avr/interrupt.h> // include header file for timer interrupts

// global variable to count the number of overflows
volatile uint8_t tot_overflow;

// initialize timer0, interrupt and variable
void timer0_init() // 8 bit
{
	// set up timer with prescaler = 256
	TCCR0B |= (1 << CS02);
	
	// initialize counter
	TCNT0 = 0;
	
	// enable overflow interrupt
	TIMSK0 |= (1 << TOIE0);
	
	// enable global interrupts
	sei();
	
	// initialize overflow counter variable
	tot_overflow = 0;
}


// initialize timer1, interrupt and variable
void timer1_init() // 16 bit
{
	// set up timer with prescaler = 256 and CTC mode
	TCCR1B |= (1 << WGM12)|(1 << CS12);
	
	// initialize counter
	TCNT1 = 0;
	
	// initialize compare value
	OCR1A = 62500; // Adjusted value changes the freq. upon which the LED blinks to which the counter hits desired value to reset Timer 1/Counter
	
	// enable compare interrupt
	TIMSK1 |= (1 << OCIE1A);
}

// initialize timer2
void timer2_init()
{
	// set up timer OC2A pin in toggle mode and CTC mode
	TCCR2A |= (1 << COM2A0)|(1 << WGM21);
	// set up timer with prescaler = 1024
	TCCR2B |= (1 << CS22)|(1 << CS21)|(1 << CS20);
	// initialize counter
	TCNT2 = 0;
	// initialize compare value
	OCR2A = 250;
}




// TIMER0 overflow interrupt service routine
// called whenever TCNT0 overflows
ISR(TIMER0_OVF_vect)
{
	// keep a track of number of overflows
	tot_overflow++;
}

// this ISR is fired whenever a match occurs
// hence, toggle led here itself..
ISR (TIMER1_COMPA_vect)
{
	// toggle led here
	PORTC ^= (1 << 1);
	
}




int main(void)
{
	PORTD |= (1 << PD2); // initializes the pull-up resistor on AVR pin PD2
	DDRB |= (1 << PB0); //Data Direction Register B: writing a 1 to the bit enables output
	
	
	// connect 1 (green) led to pin PB0
	DDRB |= (1 << 0);

	// connect 2 (blue) led to pin PC1
	DDRC |= (1 << 1);

	// connect 3 (red) led to pin PB3 (OC2A)
	DDRB |= (1 << 3);
	
	// initialize timer0
	timer0_init();

	// initialize timer1
	timer1_init();

	// initialize timer2
	timer2_init();
	
	// loop forever
	while(1)
	{
		// check if no. of overflows = 12
		if (tot_overflow >= 12)  // NOTE: '>=' is used
		{
			// check if the timer count reaches 53
			if (TCNT0 >= 53) // could change this value as well to change timer 0
			{
				PORTB ^= (1 << 0);    // toggles the led
				TCNT0 = 0;            // reset counter
				tot_overflow = 0;     // reset overflow counter
			}
		}
	}
}

