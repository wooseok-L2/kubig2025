// timer2 번을 써서 LED 좌우로 움직이는 코드 작성. 0.3초마다 움직이기.

#include "lcd.h"
#include <avr/io.h>
#include <stdio.h>
#include <util/delay.h>

int main()
{
    lcdInit();
    lcdClear();
    char lcdBuffer[17];

    unsigned char switch_flag = 0;
    DDRE = 0x00;  // 8개의 핀을 모두 인풋!
    PORTE = 0x00; // 출력! - 풀업을 설정한다.
    DDRC = 0x0F;  // 아웃풋!
    // PINE
    while (1)
    {
        if (PINE >> 4)
        {
            switch_flag = PINE >> 4; // 0b1000 0b0100
        }
        PORTC = switch_flag;
        snprintf(lcdBuffer, sizeof(lcdBuffer), "SW: 0x%02X, %c", switch_flag, '0' + switch_flag);
        lcdGotoXY(0, 0);
        lcdPrint(lcdBuffer);
    }
    return 0;
}ude <avr/io.h>

uint8_t ledData = 0x01;
volatile uint8_t timer2Cnt = 0;
ISR(TIMER2_OVF_vect);

int main(void)
{
    DDRC = 0x0F;

    TCCR2 = _BV(CS22) | _BV(CS20); // clock select 1024 prescale
    TIMSK = _BV(TOIE2);            // timer interrupt en.

    sei();
    uint8_t direction = 0;
    while (1)
    {
        if (timer2Cnt == 30)
        {
            if (ledData > 0x04)
                direction = 0;
            if (ledData == 1)
            {
                direction = 1;
                ledData = 1;
            }
            if (direction)
                ledData <<= 1;
            else
                ledData >>= 1;
            timer2Cnt = 0;
        }
        PORTC = ledData;
    }
}

ISR(TIMER2_OVF_vect)
{
    cli();
    TCNT2 = 112; // 113, 114 .... 255 .. 144-> 0.0025 초
    timer2Cnt++;
    sei();
}