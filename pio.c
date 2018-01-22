#include <stdint.h>
#include <avr/io.h>
#include "pio.h"

void toggle_pin(uint8_t pin)
{
    PORTB ^= (1 << pin);
}