#ifndef __UART_H
#define __UART_H

#define UBRR 103

void uart_init(void);

void uart_transmitt(unsigned char data);

unsigned char uart_receive(void);

#endif
