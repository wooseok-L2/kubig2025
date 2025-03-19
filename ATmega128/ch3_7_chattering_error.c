#include "lcd.h"
#include <avr/io.h>
#include <stdio.h>
#include <string.h>
#include <util/delay.h>

int main()
{
    unsigned char switchFlag = 0;
    DDRC = 0x0F;
    PORTE = 0x01; // 풀업 설정

    lcdInit();
    lcdClear();
    char lcdBuffer[17];
    while (1)
    {
        if (PINE)
        {
            switchFlag = PINE;
        }
        if (!(switchFlag & _BV(PC0)))
            PORTC ^= 0x01; // 1 번 비트 반전

        // PORTC ^= 0x01;
        // _delay_ms(500);
        lcdGotoXY(0, 0);
        lcdBuffer[17] = "";
        sprintf(lcdBuffer, "%d", switchFlag & _BV(PC0));
        // strcat(lcdBuffer, '0' + PORTC);
        lcdPrint(lcdBuffer);
    }

    return 0;
}