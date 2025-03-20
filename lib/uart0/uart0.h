#ifndef UART1_H_
#define UART1_H_
#include <stdio.h>

void uart0Init(void);
void uart0Transmit(char data);
unsigned char uart0Receive(void);
void uart0PrintString(char *str);
void uart0Print1ByteNumber(unsigned char n);

FILE OUTPUT = FDEV_SETUP_STREAM(uart0Transmit, NULL, _FDEV_SETUP_WRITE);
FILE INPUT = FDEV_SETUP_STREAM(NULL, uart0Receive, _FDEV_SETUP_READ);

#endif // UART1_h_