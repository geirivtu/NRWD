#include <avr/io.h>
#include <stdio.h>

#include "uart.h"

/* Functions from AT90CAN128 datasheet (p.183, p.184 and p.187) */
void uart_init(void)
{
	UBRR0H = (unsigned char) (UBRR>>8);
	UBRR0L = (unsigned char) UBRR;

	UCSR0C = (0<<UMSEL0) | (0<<UPM0) | (1<<USBS0) | (3<<UCSZ0);

	UCSR0B = (1<<RXEN0) | (1<<TXEN0);

	/* Setting up UART to use printf() */
	fdevopen((void*) &uart_transmitt, (void*) &uart_receive);
}

void uart_transmitt(unsigned char data)
{
	while (!(UCSR0A & (1<<UDRE0)));

	UDR0 = data;
}

unsigned char uart_receive(void)
{
	while (!(UCSR0A & (1<<RXC0)));

	return UDR0;
}
