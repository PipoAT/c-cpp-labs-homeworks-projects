#define F_CPU 1000000UL
#define BAUD 1200
#define BAUDRATE ((F_CPU / (16 * BAUD)) - 1)

#include <avr/io.h>
#include <util/delay.h>

volatile unsigned char received_char = 0;
volatile unsigned char new_received_char = 0;

void setup_serial() {
	// Set baud rate to 9600 or 1200
	UBRR0H = (BAUDRATE >> 8);
	UBRR0L = BAUDRATE;
	// Enable transmitter and receiver
	UCSR0B = (1<<RXEN0) | (1<<TXEN0);
	// Set frame format: 8 data bits, 1 stop bit
	UCSR0C = (3<<UCSZ00);
}

char receive_char() {
	// Wait until data is available in the receive buffer
	while (!(UCSR0A & (1<<RXC0))) {}
	// Return the data from the receive buffer
	return UDR0;
}

void send_char(char data) {
	// Wait until the transmit buffer is empty
	while (!(UCSR0A & (1<<UDRE0))) {}
	// Put the data into the transmit buffer
	UDR0 = data;
}

int main() {
	// Set PB5 as an output
	PORTB = 0;
	DDRB = 0xFF;
	setup_serial();

	while (true) {

		received_char = receive_char(); // below conditions only work on the upper cases				// conditions set due to unknown error

		if (received_char >= 83) {
			new_received_char = (-2 * received_char) + 255;
		}
		else if (received_char >= 41) {
			new_received_char = (-4 * received_char) + 254;
		}
		else if (received_char >= 21) {
			new_received_char = (-8 * received_char) + 252;
		}
		else if (received_char > 5) {
			new_received_char = (-16 * received_char) + 248;
		}

		// exceptions, no clear algorithm   // letter 'P'

		else { // if received_char == 5
			new_received_char = 80;
		}

		if (new_received_char != 'X') {		// if char does not match what is expected, blink error LED
			// Blink the LED
			PORTB |= (1 << 5);
			_delay_ms(500);
			PORTB &= ~(1 << 5);
			_delay_ms(500);
		} else {						// blink green led if all matches
			PORTB |= (1 << 6);
			_delay_ms(500);
			PORTB &= ~(1 << 6);
			_delay_ms(500);
		}
	}

	return 0;
}
