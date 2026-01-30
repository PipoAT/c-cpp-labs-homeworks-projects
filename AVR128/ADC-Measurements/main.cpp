/*
 * AVR128 ADC (Analog-to-Digital Converter) Example
 * 
 * This example demonstrates how to use the ADC peripheral on AVR128 series
 * microcontrollers (e.g., AVR128DA, AVR128DB) to read analog voltage values.
 * 
 * Hardware Requirements:
 * - AVR128DA or AVR128DB microcontroller
 * - Potentiometer or analog sensor (0-3.3V or 0-5V depending on VCC)
 * - Optional: LED for visual indication
 * 
 * Connections:
 * - Analog input -> PD0 (AIN0) or any ADC-capable pin
 * - LED (optional) -> PA0
 * - Potentiometer: one end to VCC, other to GND, wiper to analog input
 * 
 * The AVR128DA/DB series features a 12-bit ADC with multiple channels,
 * automatic sampling, and flexible reference voltage options.
 */

#define F_CPU 24000000UL  // 24 MHz internal oscillator

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

// ADC configuration constants
#define ADC_CHANNEL 0        // ADC0 (PD0/AIN0)
#define ADC_RESOLUTION 4096  // 12-bit ADC (2^12 = 4096)
#define ADC_VREF_MV 3300     // Reference voltage in millivolts (3.3V)

// Function prototypes
void system_init(void);
void adc_init(void);
uint16_t adc_read(uint8_t channel);
void uart_init(void);
void uart_transmit(unsigned char data);
void uart_print_string(const char* str);
void uart_print_number(uint16_t number);

// Global variables for ADC readings
uint16_t adc_value = 0;
uint16_t voltage_mv = 0;

int main(void)
{
    // Initialize system peripherals
    system_init();
    adc_init();
    uart_init();
    
    // Configure LED pin for visual indication (PA1)
    PORTA.DIRSET = PIN1_bm;  // Set PA1 as output
    
    uart_print_string("AVR128 ADC Example Started\r\n");
    uart_print_string("Reading analog input on PD0 (AIN0)\r\n\r\n");
    
    // Main loop - continuously read ADC and display values
    while(1)
    {
        // Read ADC value from channel 0
        adc_value = adc_read(ADC_CHANNEL);
        
        // Convert ADC value to voltage in millivolts
        voltage_mv = (uint32_t)adc_value * ADC_VREF_MV / ADC_RESOLUTION;
        
        // Print results via UART
        uart_print_string("ADC Value: ");
        uart_print_number(adc_value);
        uart_print_string(" (0-");
        uart_print_number(ADC_RESOLUTION - 1);
        uart_print_string(")  Voltage: ");
        uart_print_number(voltage_mv);
        uart_print_string(" mV\r\n");
        
        // Toggle LED to indicate measurement activity
        PORTA.OUTTGL = PIN1_bm;
        
        // Visual feedback: LED brightness could be PWM-controlled based on ADC value
        // (not implemented in this basic example)
        
        // Delay between readings
        _delay_ms(500);
    }
    
    return 0;
}

// Initialize system clock
void system_init(void)
{
    // Configure CPU to run at 24 MHz from internal oscillator
    // This is the default for AVR128DA/DB, but we ensure no prescaler is set
    _PROTECTED_WRITE(CLKCTRL.MCLKCTRLB, 0x00);  // No prescaler, full speed
}

// Initialize ADC peripheral
void adc_init(void)
{
    // Configure ADC reference voltage source via VREF peripheral
    // VREF.ADC0REF: Select internal 2.048V, 2.5V, 4.096V, or VDD reference
    // For VDD reference (typically 3.3V or 5V):
    VREF.ADC0REF = VREF_REFSEL_VDD_gc;  // Use VDD as reference
    
    // Alternative internal references for better accuracy:
    // VREF.ADC0REF = VREF_REFSEL_2V048_gc;  // Internal 2.048V
    // VREF.ADC0REF = VREF_REFSEL_2V5_gc;    // Internal 2.5V
    
    // Configure ADC0
    // ADC0.CTRLA: Control Register A
    ADC0.CTRLA = ADC_ENABLE_bm          // Enable ADC
               | ADC_RESSEL_12BIT_gc;   // 12-bit resolution
    
    // ADC0.CTRLB: Control Register B - Sample duration
    // Default sample duration is usually adequate
    ADC0.CTRLB = ADC_SAMPNUM_NONE_gc;  // No accumulation (single sample)
    
    // ADC0.CTRLC: Control Register C - Clock and reference selection
    // Prescaler: ADC clock should be 50kHz - 1.5MHz for 12-bit resolution
    // For F_CPU = 24MHz, prescaler of 16 gives 1.5MHz ADC clock
    // REFSEL should match the source configured in VREF.ADC0REF
    ADC0.CTRLC = ADC_PRESC_DIV16_gc     // Prescaler DIV16 (24MHz/16 = 1.5MHz)
               | ADC_REFSEL_VDDREF_gc;  // VDD reference (matches VREF.ADC0REF setting)
    
    // Configure input pin (PD0/AIN0) as input with no pull-up
    PORTD.DIRCLR = PIN0_bm;     // Set PD0 as input
    PORTD.PIN0CTRL = 0x00;      // Disable pull-up, normal input
    
    // Short delay to allow ADC to stabilize
    _delay_ms(10);
}

// Read ADC value from specified channel
uint16_t adc_read(uint8_t channel)
{
    // Select ADC channel (AIN0-AIN15 depending on device)
    // For channel 0 (PD0/AIN0)
    ADC0.MUXPOS = channel;  // Select positive input
    
    // Start conversion
    ADC0.COMMAND = ADC_STCONV_bm;
    
    // Wait for conversion to complete
    // ADC0.INTFLAGS will have RESRDY bit set when done
    while (!(ADC0.INTFLAGS & ADC_RESRDY_bm));
    
    // Clear the interrupt flag
    ADC0.INTFLAGS = ADC_RESRDY_bm;
    
    // Read and return the result
    return ADC0.RES;
}

// Initialize UART for debug output
void uart_init(void)
{
    // For AVR128DA/DB, USART0 is typically on PA0 (TxD) and PA1 (RxD)
    // or PC0/PC1 depending on pin mapping
    
    // Set baud rate (9600 baud @ 24MHz)
    // For AVR128: BAUD = (64 * F_CPU) / (16 * desired_baud)
    uint16_t baud_setting = (uint32_t)(64UL * F_CPU) / (16UL * 9600UL);
    USART0.BAUD = baud_setting;
    
    // Configure USART0
    USART0.CTRLB = USART_TXEN_bm;  // Enable transmitter
    
    // Set TX pin as output (PA0 for USART0)
    PORTA.DIRSET = PIN0_bm;
}

// Transmit single character via UART
void uart_transmit(unsigned char data)
{
    // Wait for transmit buffer to be empty
    while (!(USART0.STATUS & USART_DREIF_bm));
    
    // Put data into buffer, sends the data
    USART0.TXDATAL = data;
}

// Transmit string via UART
void uart_print_string(const char* str)
{
    while (*str)
    {
        uart_transmit(*str++);
    }
}

// Transmit number as ASCII string via UART
void uart_print_number(uint16_t number)
{
    char buffer[6];  // Max 5 digits for 16-bit number + null terminator
    int i = 0;
    
    // Handle zero case
    if (number == 0)
    {
        uart_transmit('0');
        return;
    }
    
    // Convert number to string (reverse order)
    while (number > 0)
    {
        buffer[i++] = (number % 10) + '0';
        number /= 10;
    }
    
    // Print in correct order
    while (i > 0)
    {
        uart_transmit(buffer[--i]);
    }
}

/*
 * IMPLEMENTATION NOTES:
 * 
 * This example demonstrates basic ADC usage on AVR128DA/DB series.
 * Key features showcased:
 * 
 * 1. ADC Initialization:
 *    - 12-bit resolution (0-4095 range)
 *    - VDD reference voltage
 *    - Prescaler configuration for proper ADC clock
 * 
 * 2. Single-ended measurement:
 *    - Reads single analog input channel
 *    - Converts raw ADC value to voltage
 * 
 * 3. UART output:
 *    - Displays ADC values and calculated voltage
 *    - Useful for monitoring and debugging
 * 
 * ADVANCED FEATURES (not shown here):
 * - Differential measurements
 * - Oversampling and decimation for higher resolution
 * - Free-running mode with interrupts
 * - Window comparator mode for threshold detection
 * - Multiple channel scanning
 * - DMA integration for background sampling
 * 
 * CALIBRATION:
 * - The ADC may benefit from calibration for better accuracy
 * - Internal bandgap reference can be used for calibration
 * - See AVR128DA/DB datasheet for calibration procedures
 * 
 * REFERENCE VOLTAGE OPTIONS:
 * - VDD (supply voltage): Simple but less accurate
 * - Internal 2.048V: Better accuracy, independent of supply
 * - Internal 2.5V: Alternative internal reference
 * - Internal 4.096V: For higher voltage measurements
 * - External VREF pin: Best accuracy with external precision reference
 */
