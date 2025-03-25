
#include "SHT2x.h"
#include "TWI_driver.h"
#include "lcd.h"
#include <avr/interrupt.h>
#include <avr/io.h>
#include <util/delay.h>

void printf_2dot1(uint8_t sense, uint16_t sense_temp);

uint16_t temperaturC, humidityRH;

int main(void)
{
    Init_TWI();
    lcdInit();
    SHT2x_Init();
    nt16 sRH;
    nt16 sT;
    uint8_t error;

    while (1)
    {
        error |= SHT2x_MeasureHM(HUMIDITY, &sRH);
        error |= SHT2x_MeasureHM(TEMP, &sT);
        temperaturC = SHT2x_CalcTemperatureC(sT.u16) * 10;
        humidityRH = SHT2x_CalcRH(sRH.u16) * 10;
        if (error == SUCCESS)
        {
            lcdGotoXY(0, 0);
            printf_2dot1(TEMP, temperaturC);
            lcdGotoXY(0, 1);
            printf_2dot1(HUMIDITY, humidityRH);
        }
        else
        {
            lcdGotoXY(0, 0);
            lcdPrintData(" Temp: --.-C", 12);
            lcdGotoXY(0, 1);
            lcdPrintData(" Humi: --.-%", 12);
        }
        _delay_ms(300);
    }
    return 0;
}

void printf_2dot1(uint8_t sense, uint16_t sense_temp)
{
    uint8_t s100, s10;
    if (sense == TEMP)
    {
        lcdPrintData(" Temp: ", 7);

        s100 = sense_temp / 100; // 100의 자리
        if (s100 > 0)
            lcdDataWrite(s100 + '0');

        s10 = sense_temp / 10 - s100 * 10; // 10의 자리
        if (s10 > 0)
            lcdDataWrite(s10 + '0');
        lcdDataWrite('.');                   // . 프린트
        lcdDataWrite(sense_temp % 10 + '0'); // 1의 자리
        lcdDataWrite('C');                   // C 프린트
    }
    else if (sense == HUMIDITY)
    {
        lcdPrintData(" Humi: ", 7);
        s100 = sense_temp / 100; // 100의 자리
        if (s100 > 0)
            lcdDataWrite(s100 + '0');

        s10 = sense_temp / 10 - s100 * 10; // 10의 자리
        if (s10 > 0)
            lcdDataWrite(s10 + '0');
        lcdDataWrite('.');                   // . 프린트
        lcdDataWrite(sense_temp % 10 + '0'); // 1의 자리
        lcdDataWrite('%');                   // % 프린트
    }
}