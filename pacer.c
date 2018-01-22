#include <avr/io.h>
#include "pacer.h"
#include "main.h"

static uint16_t pacer_tics;

/* Initialise the pacer module.  */
void pacer_init(uint16_t pacer_frequency)
{
    TCCR1A = 0x00;
    TCCR1B = 0x05;
    TCCR1C = 0x00;

    TCCR0A = 0x00;
    TCCR0B = 0x05;
    
    pacer_tics = F_CPU / (PRESCALER * pacer_frequency);
    TCNT1 = 0;
}


/* Pace a while loop.  */
void pacer_wait(void)
{
    while (TCNT1 <= pacer_tics);
	TCNT1 = 0;
}