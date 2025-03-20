
#include "uart0.h"
#include <avr/interrupt.h>
#include <avr/io.h>
#include <stdio.h>

volatile uint8_t intData = '0';

int main()
{
    uart0Init();
    stdin = &INPUT;
    stdout = &OUTPUT;

    DDRE = 0x02; // Rx(입력), TX(출력)1, SW0~3 입력

    EICRB = 0xFF; // 4567 상승 엣지에서 동작 289p.
    EIMSK = 0xF0; // 4567 허용
    EIFR = 0xF0;  // 4567 클리어

    sei(); // 전역 인터럽트 허용

    printf("Hi, I'm Atmega128");

    while (1)
    {
        if (intData != '0')
        {
            printf("\n\r Input Switch : %c", intData);
            intData = '0';
        }
    }
    return 0;
}

ISR(INT4_vect)
{
    cli();
    intData = '1';
    sei();
}

ISR(INT5_vect)
{
    cli();
    intData = '2';
    sei();
}

ISR(INT6_vect)
{
    cli();
    intData = '3';
    sei();
}

ISR(INT7_vect)
{
    cli();
    intData = '4';
    sei();
}
