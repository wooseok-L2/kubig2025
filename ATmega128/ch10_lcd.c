#include "lcd.h"
#include <avr/delay.h>
#include <avr/io.h>
#include <stdlib.h>

int main(void)
{
    DDRE = _BV(PE3); // PE3 출력 설정

    TCCR3A = _BV(COM3A1) | _BV(WGM31);
    TCCR3B = _BV(WGM33) | _BV(WGM32) | _BV(CS31);
    // 분주비 8, fast PWM mode, timer3
    ICR3 = 40000; // 20ms 2MHz -> 2000000 -> 1초 ? -> 0.02초
    OCR3A = 3000; // 40000 : 20 = ? :1.5  2000~4000 -> -90 ~ 90

    lcdInit();
    lcdClear();
    char buffer[16];

    while (1)
    {
        for (uint16_t pulse = 2000; pulse <= 4000; pulse += 40)
        {
            OCR3A = pulse;
            itoa(pulse, buffer, 10);
            lcdGotoXY(0, 0);
            lcdPrint(buffer);
            _delay_ms(100);
        }
        for (uint16_t pulse = 4000; pulse >= 2000; pulse -= 40)
        {
            OCR3A = pulse;
            itoa(pulse, buffer, 10);
            lcdGotoXY(0, 0);
            lcdPrint(buffer);
            _delay_ms(100);
        }
    }
    return 0;
}