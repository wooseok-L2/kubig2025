#ifndef UART1_H_
#define UART1_H_
#include <avr/io.h>


void uart1Init(void);
void uart1Transmit(char data);
unsigned char uart1Receive(void);
void uart1PrintString(char *void(void));
void uart1Print1ByteNumber(unsigned char n);