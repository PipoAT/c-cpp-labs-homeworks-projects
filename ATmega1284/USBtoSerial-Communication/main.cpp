#define F_CPU 1000000UL          // defines F_CPU
#define BAUD 1200		// defines BAUD rate
#define BAUDRATE ((F_CPU / (16UL * BAUD))-1)

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>


void USART_init(void) {

	// can change to 9 bit ------------------------------|				 | Engage parity bits
	UCSR0B = (0 << TXB80) | (0 << RXB80) | (0 << UCSZ02) | (1 << TXEN0) | (0 << UPM01) | (0 << UPM00);
	UCSR0C = (1 << UCSZ01) | (1 << UCSZ00); // <--------------- defines as 8 bit
	UCSR0A = (0 << U2X0);
	UBRR0H = (BAUDRATE >> 8);
	UBRR0L = BAUDRATE;

}


void USART_Transmit(unsigned char value) { // <----------- takes the data to be transmitted and adds it to register to send

	while(!(UCSR0A & (1 << UDRE0)));
	UDR0 = value;
}


int main(void) {

		unsigned char data = (unsigned char) 'A'; // <--------- change value to send to PC
		data = 255 - (data << 1); //<----------- manipulate the data input to convert to a different value to print out correctly (due to unknown issue)
		USART_init();
		while(1) {
			USART_Transmit(data);
			//USART_Transmit(0x41);
			_delay_ms(1000);	//<-------------- sends data repeatedly

		}

}