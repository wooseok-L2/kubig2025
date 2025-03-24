#include "at25160.h"
#include "lcd.h"
#include <avr/delay.h>
#include <avr/io.h>

#define ARRAY_SIZE(array) (sizeof(array) / sizeof(array[0]))

uint8_t msg1[] = "welcome!!";
uint8_t msg2[] = "Atmega128-World!!";
uint8_t msg3[] = "SPI-Flash Example";

int main(void)
{
    uint8_t i = 0;
    uint8_t buf1[20] = {0};
    uint8_t buf2[20] = {0};
    uint8_t buf3[20] = {0};

    SPI_Init(); // PB0 1 2 3
    lcdInit();  // PC4 5 6 7 PG2

    at25160_Write_Arry(0x0100, msg1, ARRAY_SIZE(msg1));
    at25160_Write_Arry(0x0200, msg2, ARRAY_SIZE(msg2));
    at25160_Write_Arry(0x0300, msg3, ARRAY_SIZE(msg3));

    at25160_Read_Arry(0x0100, buf1, ARRAY_SIZE(buf1));
    at25160_Read_Arry(0x0200, buf2, ARRAY_SIZE(buf2));
    at25160_Read_Arry(0x0300, buf3, ARRAY_SIZE(buf3));

    while (1)
    {
        lcdGotoXY(0, 0);
        for (i = 0; i < ARRAY_SIZE(msg1) - 1; i++)
        {
            lcdDataWrite(buf1[i]);
            _delay_ms(100);
        }
        i = 0;
        lcdGotoXY(0, 1);
        while (buf2[i])
        {
            lcdDataWrite(buf2[i]);
            ++i;
            _delay_ms(100);
        }
        lcdGotoXY(0, 0);
        lcdPrint(buf3);
        _delay_ms(2000);
        lcdClear();
    }

    return 0;
}