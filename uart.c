#include <stdint.h>
#include <avr/io.h>
#include <stdarg.h>	
#include <stdio.h>
#include <string.h>
#include "pio.h"
#include "uart.h"

void uart_init(uint16_t baud_rate)
{
    uint16_t BRC = F_CPU / 16 / baud_rate - 1;

    // Set BAUD rate
    UBRR0H = (BRC >> 8);
    UBRR0L =  BRC;

    // Set transmit enable bit
    UCSR0B |= BIT(TXEN0);

    // Set up 8 bit dataframe
    UCSR0C |= BIT(UCSZ01) | BIT(UCSZ00);
}

int usart_write_ready_p(void)
{
    return (UCSR0A & BIT(UDRE0)) != 0;
}

/** Write character to USART1.  This blocks until the character can be
    written into the transmit register.  */
void usart_putc(char ch)
{
    while (!usart_write_ready_p ()) {
        continue;                   
    }

    /* Write a 1 to the TXC1 bit to clear it!  It will be set when the
    data is shifted out of the transmit shift register.  */
    UCSR0A |= BIT (TXC0);
    
    UDR0 = ch;
}

/** Write string to USART1.  This blocks until the string is written.  */
void serial_write(const char *str)
{
    while (*str)
        usart_putc(*str++);
}

/** Custom print function leveraging the stdarg library to include formatting. 
    Prints one line to serial output */
int println (const char *format, ...)
{
    va_list arg;
    int buf_len = 50;
    int len;
    char buf[buf_len];

    va_start (arg, format);
    len = vsprintf (buf, format, arg);

    if (len > buf_len - 3) {
        serial_write("Increase buffer length \n");
        return 0;
    }

    memcpy(&buf[len], "\n\r\0", 3);         // Terminate string correctly
    va_end (arg);

    serial_write(buf);

    return len;
}