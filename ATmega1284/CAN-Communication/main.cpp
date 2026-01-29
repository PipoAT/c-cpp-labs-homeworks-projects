/*
 * ATmega1284 CAN Communication Example
 * 
 * This is an introductory example demonstrating CAN (Controller Area Network) 
 * communication using the ATmega1284 microcontroller with an MCP2515 CAN controller.
 * 
 * Hardware Requirements:
 * - ATmega1284 microcontroller
 * - MCP2515 CAN controller module
 * - CAN transceiver (typically included in MCP2515 modules)
 * 
 * Connections:
 * - MCP2515 SCK  -> ATmega1284 PB7 (SCK)
 * - MCP2515 MISO -> ATmega1284 PB6 (MISO)
 * - MCP2515 MOSI -> ATmega1284 PB5 (MOSI)
 * - MCP2515 CS   -> ATmega1284 PB4 (SS)
 * - MCP2515 INT  -> ATmega1284 PD2 (INT0)
 * 
 * This example initializes the CAN controller and sends a simple message.
 */

#define F_CPU 16000000UL
#define CAN_BITRATE 125  // 125 kbps

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

// MCP2515 Register Addresses
#define MCP_RXF0SIDH    0x00
#define MCP_RXF0SIDL    0x01
#define MCP_CANCTRL     0x0F
#define MCP_CNF3        0x28
#define MCP_CNF2        0x29
#define MCP_CNF1        0x2A
#define MCP_CANINTE     0x2B
#define MCP_CANINTF     0x2C
#define MCP_TXB0CTRL    0x30
#define MCP_TXB0SIDH    0x31
#define MCP_TXB0SIDL    0x32
#define MCP_TXB0DLC     0x35
#define MCP_TXB0DATA    0x36

// MCP2515 Commands
#define MCP_RESET       0xC0
#define MCP_READ        0x03
#define MCP_WRITE       0x02
#define MCP_RTS         0x80
#define MCP_READ_STATUS 0xA0

// MCP2515 Modes
#define MODE_NORMAL     0x00
#define MODE_SLEEP      0x20
#define MODE_LOOPBACK   0x40
#define MODE_LISTENONLY 0x60
#define MODE_CONFIG     0x80

// CS (Chip Select) pin definitions
#define CS_PIN          PB4
#define CS_PORT         PORTB
#define CS_DDR          DDRB

// Function prototypes
void spi_init(void);
void mcp2515_init(void);
void mcp2515_reset(void);
void mcp2515_write_register(uint8_t address, uint8_t data);
uint8_t mcp2515_read_register(uint8_t address);
void mcp2515_set_mode(uint8_t mode);
void can_send_message(uint16_t id, uint8_t *data, uint8_t length);
uint8_t spi_transfer(uint8_t data);
void cs_select(void);
void cs_deselect(void);

int main(void)
{
    // Initialize SPI and CAN controller
    spi_init();
    _delay_ms(100);
    mcp2515_init();
    
    // Prepare a simple CAN message
    uint8_t message_data[8] = {0x48, 0x65, 0x6C, 0x6C, 0x6F, 0x43, 0x41, 0x4E}; // "HelloCAN"
    uint16_t message_id = 0x123;  // CAN message ID
    
    // Main loop - send message every 2 seconds
    while(1)
    {
        can_send_message(message_id, message_data, 8);
        _delay_ms(2000);
    }
    
    return 0;
}

// Initialize SPI as master
void spi_init(void)
{
    // Set MOSI, SCK, and SS as outputs
    DDRB |= (1 << PB5) | (1 << PB7) | (1 << CS_PIN);
    // Set MISO as input
    DDRB &= ~(1 << PB6);
    
    // Set CS high (deselected)
    CS_PORT |= (1 << CS_PIN);
    
    // Enable SPI, Master mode, set clock rate fck/16
    SPCR = (1 << SPE) | (1 << MSTR) | (1 << SPR0);
}

// Transfer one byte via SPI
uint8_t spi_transfer(uint8_t data)
{
    SPDR = data;
    while(!(SPSR & (1 << SPIF)));  // Wait for transmission complete
    return SPDR;
}

// Select MCP2515 (CS low)
void cs_select(void)
{
    CS_PORT &= ~(1 << CS_PIN);
}

// Deselect MCP2515 (CS high)
void cs_deselect(void)
{
    CS_PORT |= (1 << CS_PIN);
}

// Reset MCP2515
void mcp2515_reset(void)
{
    cs_select();
    spi_transfer(MCP_RESET);
    cs_deselect();
    _delay_ms(10);
}

// Write to MCP2515 register
void mcp2515_write_register(uint8_t address, uint8_t data)
{
    cs_select();
    spi_transfer(MCP_WRITE);
    spi_transfer(address);
    spi_transfer(data);
    cs_deselect();
}

// Read from MCP2515 register
uint8_t mcp2515_read_register(uint8_t address)
{
    uint8_t result;
    cs_select();
    spi_transfer(MCP_READ);
    spi_transfer(address);
    result = spi_transfer(0x00);
    cs_deselect();
    return result;
}

// Set MCP2515 operating mode
void mcp2515_set_mode(uint8_t mode)
{
    mcp2515_write_register(MCP_CANCTRL, mode);
    _delay_ms(10);
}

// Initialize MCP2515 CAN controller
void mcp2515_init(void)
{
    // Reset the MCP2515
    mcp2515_reset();
    
    // Enter configuration mode
    mcp2515_set_mode(MODE_CONFIG);
    
    // Configure bit timing for 125 kbps @ 16 MHz
    // CNF1: SJW = 1 TQ, BRP = 7
    mcp2515_write_register(MCP_CNF1, 0x03);
    // CNF2: BTLMODE = 1, SAM = 0, PHSEG1 = 6 TQ, PRSEG = 1 TQ
    mcp2515_write_register(MCP_CNF2, 0xB8);
    // CNF3: PHSEG2 = 6 TQ
    mcp2515_write_register(MCP_CNF3, 0x05);
    
    // Configure filters and masks (accept all messages)
    mcp2515_write_register(MCP_RXF0SIDH, 0x00);
    mcp2515_write_register(MCP_RXF0SIDL, 0x00);
    
    // Enable interrupts (optional, for receive)
    mcp2515_write_register(MCP_CANINTE, 0x00);
    
    // Enter normal mode
    mcp2515_set_mode(MODE_NORMAL);
}

// Send a CAN message
void can_send_message(uint16_t id, uint8_t *data, uint8_t length)
{
    // Limit data length to 8 bytes (CAN standard)
    if (length > 8) length = 8;
    
    // Set message ID (standard 11-bit identifier)
    mcp2515_write_register(MCP_TXB0SIDH, (uint8_t)(id >> 3));
    mcp2515_write_register(MCP_TXB0SIDL, (uint8_t)(id << 5));
    
    // Set data length code
    mcp2515_write_register(MCP_TXB0DLC, length);
    
    // Write data bytes
    for (uint8_t i = 0; i < length; i++)
    {
        mcp2515_write_register(MCP_TXB0DATA + i, data[i]);
    }
    
    // Request to send
    cs_select();
    spi_transfer(MCP_RTS | 0x01);  // Request transmission on buffer 0
    cs_deselect();
    
    // Wait for transmission to complete (simple polling)
    _delay_ms(10);
}
