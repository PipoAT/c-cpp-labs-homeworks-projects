#define F_CPU 12000000UL // Atmega1284

#define Up_Button_Output_Register			PORTA			// macros defined, defined button 1 output, read, and direction
#define Up_Button_Read_Register				PINA
#define Up_Button_Direction_Register		DDRA

#define Down_Button_Output_Register			PORTA			// macros defined, defined button 2 output, read, and direction
#define Down_Button_Read_Register			PINA
#define Down_Button_Direction_Register		DDRA

#define Up_Button_Position_Pin				1
#define Down_Button_Position_Pin			2				// defined locations of buttons 1 and 2


#define TIMER_0_PRESCALER	(1 << CS02)				// defined prescaler

#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/delay.h>

volatile uint8_t tot_overflow = 0;
volatile unsigned char timer0OverflowCountLimit = 12;


unsigned char State_of_Up_Button_to_Pin = 0; //The current state of the on off button pin
unsigned char State_of_Down_Button_to_Pin = 0; 
unsigned char Previous_State_Of_Up_Button = 0;
unsigned char Previous_State_Of_Down_Button = 0;


void timer0_init()																// initialize timer0, interrupt and variable
{
	
	// initialize counter
	TCNT0 = 0;																	// Gives direct access to the Timer/Counter unit 8-bit counter
	
	// enable overflow interrupt
	TIMSK0 |= (1 << TOIE0);														// Interrupt Mask Register
	
	// enable global interrupts
	sei();
	
	// set up timer with prescaler = 256											// Timer/Counter n in Control Register B
	TCCR0B |= (TIMER_0_PRESCALER);
}


int main(void)
{
	
	PORTA = 0; // reset/declare values
	DDRA = 0xFF;
	PORTB = 0;
	DDRB = 0xFF;
	PORTC = 0;
	DDRC = 0xFF;
	PORTD = 0;
	DDRD = 0xFF;

	// initialize timer0
	timer0_init();
	
	// sets up the output and direction registers with the positioning of the buttons
	
	Up_Button_Output_Register |= (1 << Down_Button_Position_Pin); // bitwise functions OR and left shifting
	Up_Button_Direction_Register &= ~(1 << Down_Button_Position_Pin); //bitwise functions using AND, NOT, and left shifting
	Down_Button_Output_Register |= (1 << Up_Button_Position_Pin);
	Down_Button_Direction_Register &= ~(1 << Up_Button_Position_Pin);
		
	for(;;) {

		//Read the current pin state of the up button
		State_of_Up_Button_to_Pin = ((Up_Button_Read_Register & (1 << Down_Button_Position_Pin)) >> Down_Button_Position_Pin);
		
		//If the current on/off state is different than the previous state...
		if(State_of_Up_Button_to_Pin != Previous_State_Of_Up_Button)
		{
			//save the new state
			Previous_State_Of_Up_Button = State_of_Up_Button_to_Pin;
		}


		// Read the current pin state of down button
		// Checking if state of the button is the same as the previous state, if not, it will update for the second button
		
		State_of_Down_Button_to_Pin = ((Down_Button_Read_Register & (1 << Up_Button_Position_Pin)) >> Up_Button_Position_Pin); // uses bitwise AND as shifting based on known positions
		if (State_of_Down_Button_to_Pin != Previous_State_Of_Down_Button) {
			Previous_State_Of_Down_Button = State_of_Down_Button_to_Pin;
		}
		
		if (State_of_Down_Button_to_Pin ^= 1) { // Down button pressed
			timer0OverflowCountLimit = 50;
		}
		else if (State_of_Up_Button_to_Pin ^= 1) {	// Up button pressed
			timer0OverflowCountLimit = 82;			
		}
		_delay_ms(100);    // to remove finger from clicking the button. Give time for the user to release the button
	}
}


ISR(TIMER0_OVF_vect)														// Timer 0, overflow
{
	TCCR0B &= ~(TIMER_0_PRESCALER);
	// keep a track of number of overflows
	tot_overflow++;
	if (tot_overflow >= timer0OverflowCountLimit) {
		PORTC ^= (1 << 1); // toggle led after overflow hits
		tot_overflow = 0;
	}
	TCNT0 = (255 - 53);
	TCCR0B |= (TIMER_0_PRESCALER);
}

// TIMER0 overflow interrupt service routine
// called whenever TCNT0 overflows


	