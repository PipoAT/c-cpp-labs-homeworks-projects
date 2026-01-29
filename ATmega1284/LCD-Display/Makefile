# Makefile for ATmega1284 LCD Display Project
#
# This Makefile automates the compilation and programming process
# for the LCD display example.
#
# Usage:
#   make          - Compile the project
#   make hex      - Create hex file for programming
#   make program  - Upload to microcontroller
#   make clean    - Remove compiled files
#   make size     - Show memory usage

# Microcontroller settings
MCU = atmega1284p
F_CPU = 12000000UL

# Programmer settings (adjust for your programmer)
PROGRAMMER = usbasp
# PROGRAMMER = arduino
# PORT = /dev/ttyUSB0  # Uncomment if using arduino as programmer

# Compiler settings
CC = avr-gcc
OBJCOPY = avr-objcopy
SIZE = avr-size
AVRDUDE = avrdude

# Compiler flags
CFLAGS = -mmcu=$(MCU) -DF_CPU=$(F_CPU) -Os -Wall -Wextra
CFLAGS += -std=gnu99
CFLAGS += -funsigned-char -funsigned-bitfields -fpack-struct -fshort-enums
CFLAGS += -ffunction-sections -fdata-sections

# Linker flags
LDFLAGS = -mmcu=$(MCU) -Wl,--gc-sections

# Source files
SOURCES = Main.c lcd.c
OBJECTS = $(SOURCES:.c=.o)

# Output files
TARGET = lcd_display
ELF = $(TARGET).elf
HEX = $(TARGET).hex
MAP = $(TARGET).map

# Default target
all: $(ELF) size

# Compile C files to object files
%.o: %.c
	@echo "Compiling $<..."
	$(CC) $(CFLAGS) -c $< -o $@

# Link object files to create ELF
$(ELF): $(OBJECTS)
	@echo "Linking..."
	$(CC) $(LDFLAGS) -Wl,-Map,$(MAP) $(OBJECTS) -o $(ELF)

# Create hex file from ELF
hex: $(ELF)
	@echo "Creating hex file..."
	$(OBJCOPY) -O ihex -R .eeprom $(ELF) $(HEX)
	@echo "Hex file created: $(HEX)"

# Show memory usage
size: $(ELF)
	@echo "Memory usage:"
	$(SIZE) --format=avr --mcu=$(MCU) $(ELF)

# Program the microcontroller
program: hex
	@echo "Programming $(MCU)..."
	$(AVRDUDE) -p $(MCU) -c $(PROGRAMMER) -U flash:w:$(HEX):i
# If using arduino programmer, uncomment the line below and comment the one above
#	$(AVRDUDE) -p $(MCU) -c $(PROGRAMMER) -P $(PORT) -U flash:w:$(HEX):i

# Clean compiled files
clean:
	@echo "Cleaning..."
	rm -f $(OBJECTS) $(ELF) $(HEX) $(MAP)
	@echo "Clean complete."

# Show help
help:
	@echo "ATmega1284 LCD Display Project Makefile"
	@echo ""
	@echo "Available targets:"
	@echo "  make          - Compile the project"
	@echo "  make hex      - Create hex file for programming"
	@echo "  make program  - Upload to microcontroller"
	@echo "  make clean    - Remove compiled files"
	@echo "  make size     - Show memory usage"
	@echo "  make help     - Show this help message"
	@echo ""
	@echo "Configuration:"
	@echo "  MCU:        $(MCU)"
	@echo "  F_CPU:      $(F_CPU)"
	@echo "  Programmer: $(PROGRAMMER)"

# Phony targets
.PHONY: all hex size program clean help
