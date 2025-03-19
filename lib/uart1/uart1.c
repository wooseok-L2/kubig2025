#include "uart1.h"


void uart1Init(void){
    UCSR0A |= _BV(U2X1);   // x2 mode
    UCSR0B = 0x18;  //0b00011000   RC, TC enable
    UCSR0C = 0x16;  // 0b0010110   noparity. 1 stop bit

    UBRR0H = 0x00;
    UBRR0L = 0x07;  // 115200 bpss --> 9600 bsp
}
void uart1Transmit(char data){
    // tomorrow
}
unsigned char uart1Receive(void){
    uint8_t data;
    while((UCSR0A & 0x08) == 0);

    return UDR0;
}
void uart1PrintString(char *void(void));
void uart1Print1ByteNumber(unsigned char n);