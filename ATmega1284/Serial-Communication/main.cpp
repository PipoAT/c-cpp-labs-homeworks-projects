#define F_CPU 12000000UL					// defined at 12MHz		// BOTH MCUs must be at the same BAUD rate
#define BAUD 9600							// defined baud
#define TIMER_0_PRESCALER	(1 << CS02)


#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <stdio.h>

volatile unsigned char ledison = 0;  // declared global variables
volatile unsigned char u_usart0rx = 0; // declared global variable   // both used in timer and to help blink led
volatile unsigned char threshold = 128; // used for threshold for when the green led should turn on
volatile unsigned char overflow = 0;	// initialize counter for overflow
volatile unsigned char overflowcondition = 255; // define condition starter for red led


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

void USART_Init(void) {
	

	UCSR0B = (1 << RXEN0) | (1 << TXEN0) | (1 << RXCIE0);		// activates or engages the receiver and transmit and engages the complete interrupt for RX
	UCSR0C = (1 << USBS0) | (3 << UCSZ00);
	UBRR0 = (unsigned short)((F_CPU / (16 * BAUD))-1);			// Defines the BAUD rate and places into the registers
}

void USART_Transmit(unsigned char data) {
	while (!(UCSR0A & (1 << UDRE0)));     // adds data into the buffer
	UDR0 = data;
	
}

unsigned char USART_Receive(void) {
	while (!(UCSR0A & (1 << RXC0)));
	// get and return from buffer
	return UDR0;
}


int main()
{
	char c = 0; // can be commented out for the receiving mcu program
	
	// initialize the ports/directions (or reset)
	PORTA = 0;
	PORTB = 0;
	PORTD = 0;
	DDRA = 0xFF;
	DDRB = 0xFF;
	DDRD = 0xFF;
	
	sei();  // enable global interrupts
	
	timer0_init();
	USART_Init(); // calls the initialization of the USART
	_delay_ms(10); // delay to allow mcu and program to catch up
	while(1)
	{
		// parent mcu code
		//USART_Transmit(c); // calls the transmit function for the data
		
		//if(c < 255)
		//{
		//	c++;
		//}
		//else
		//{
		//	c = 0;
		//}
		
		// _delay_ms(10);
		
		// }
		
			USART_Receive(); // code for the receiving mcu
			
			if (ledison == 1) {
				PORTB |= (1 << 3); // checks the state of led light from ISR and triggers led light on PB3 // ON
			}
			if (ledison == 0) { // OFF
				PORTB &= ~(1 << 3);
				
			}
	}
	
}


ISR(USART0_RX_vect) {
	u_usart0rx = UDR0;	// reads value from UDR0 register
	if (u_usart0rx >= threshold) {		// will blink led if data value hits 128 or 255
		ledison = 1; // led state on
		if (overflow > 1) {
		overflowcondition = overflowcondition - 1; // decreases the threshold for when the red led can blink
		}
		} else {
		ledison = 0; // led state off
	}
	if (u_usart0rx == 255) {
		overflow++;		// increase count of number of times UDR0 hits overflow of 255
	}
}

ISR(TIMER0_OVF_vect)														// Timer 0, overflow
{
	TCCR0B &= ~(TIMER_0_PRESCALER);
	// keep a track of number of overflows
	if (overflow >= overflowcondition) {
		PORTA  ^= (1 << 3); // toggle led after overflow hits
		overflow = 0; // reset overflow counter
	}
	TCNT0 = 0;
	TCCR0B |= (TIMER_0_PRESCALER);
}