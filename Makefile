# Definitions.
BIN = main
CC = avr-gcc
CFLAGS = -mmcu=atmega328p -Os -Wall -Wstrict-prototypes -Wextra -DF_CPU=16000000UL -Wl,-u,vfprintf -lprintf_flt -lm
OBJCOPY = avr-objcopy
PORT = /dev/cu.usbmodem1421
SIZE = avr-size
DEL = rm

# Default target.
all: $(BIN).out

# Compile: create object files from C source files.
$(BIN).o: $(BIN).c pio.c pio.h uart.c uart.h i2cmaster.h twimaster.c mpu6050.c mpu6050.h pacer.c pacer.h
	$(CC) -c $(CFLAGS) $< -o $@

pio.o: pio.c pio.h
	$(CC) -c $(CFLAGS) $< -o $@

uart.o: uart.c uart.h
	$(CC) -c $(CFLAGS) $< -o $@

mpu6050.o: mpu6050.c mpu6050.h twimaster.c i2cmaster.h uart.h
	$(CC) -c $(CFLAGS) $< -o $@

twimaster.o: twimaster.c i2cmaster.h

pacer.o: pacer.c pacer.h main.h
	$(CC) -c $(CFLAGS) $< -o $@

# Link: create ELF output file from object files.
$(BIN).out: $(BIN).o pio.o uart.o twimaster.o mpu6050.o pacer.o
	$(CC) $(CFLAGS) $^ -o $@ -lm
	$(SIZE) $@

# Target: program project.
.PHONY: program
program: $(BIN).out
	$(OBJCOPY) -O ihex $(BIN).out $(BIN).hex
	avrdude -v -c arduino -p ATMEGA328P -P ${PORT} -b 115200 -U flash:w:$(BIN).hex

# Target: clean project.
.PHONY: clean
clean: 
	-$(DEL) *.o *.out *.hex