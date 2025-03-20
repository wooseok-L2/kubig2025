#include <avr/interrupt.h>
#include <avr/io.h>

volatile uint8_t txFlag = 0;
volatile char txData = 0;

uint8_t getch(void)
{
    uint8_t data;
    while ((UCSR0A & 0x80) == 0) // 문자 버퍼에 있으면 루프 탈출
        ;
    data = UDR0;
    UCSR0A |= 0x80;
    return data;
}

int main()
{
    uint8_t numbers[] = {0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x27, 0x7F, 0x67};
    uint8_t rxData;
    DDRA = 0xFF;

    UCSR0A = 0x00;
    UCSR0B = 0x18; // 0b00011000 Rx, Tx enable
    UCSR0C = 0x16; // 0b00010110  비동기, no Parity, 1 stop bit

    UBRR0H = 0x00;
    UBRR0L = 0x07; // 115200 bps

    while (1)
    {
        rxData = getch();
        if ((rxData >= 0x30) && (rxData <= 0x39))
        {
            PORTA = numbers[rxData - 0x30];
        }
    }
    return 0;
}