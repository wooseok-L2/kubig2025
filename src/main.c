// SHT 5초 마다 한번씩 온습도 측정 - timer0 5초 주기를 계산.
// 외부 EEPROM  의 주소는 0100-> 온도 0200-> 습도
// SHT 에서 측정 실패는 error 성공 시에만 EEPROM 에 저장.
// INT4 번 써서(스위치를 누르면) EEPROM 에 데이터를 읽어서 UART로 출력하기.
// 0 ~ 99.9 표현하려면 1 byte 로는 부족하다. ???

#include "SHT2x.h"
#include "at25160.h"
#include "uart0.h"
#include <avr/interrupt.h>
#include <avr/io.h>

volatile uint8_t readFlag = 1, txFlag = 0;
uint16_t timerCount = 0;
uint16_t temperatureC, humidityRH;

int main(void)
{
    SPI_Init();

    Init_TWI();
    SHT2x_Init();

    uart0Init();
    DDRE = _BV(PE1); // 0x02;

    // interrupt 4 설정
    EICRB = 0x03; // int 4 상승 엣지
    EIMSK = 0x10;

    TCCR0 = 0x07; // 1024 분주비
    TCNT0 = 112;  // 144 세기.. 16M /1024/ 0.1초 ....
    TIMSK = 0x01; // timer0 ovf enable

    sei();
    stdout = &OUTPUT;

    while (1)
    {
        if (readFlag)
        {
            // i2c temp read -> spi eeprom write
            SHT2x_MeasureHM(TEMP, (nt16 *)&temperatureC);
            SHT2x_MeasureHM(HUMIDITY, (nt16 *)&humidityRH);
            temperatureC = SHT2x_CalcTemperatureC(temperatureC) * 10;
            humidityRH = SHT2x_CalcRH(humidityRH) * 10;
            at25160_Write_Arry(0x0100, (uint8_t *)&temperatureC, 2);
            at25160_Write_Arry(0x0200, (uint8_t *)&humidityRH, 2);
            readFlag = 0;
        }
        if (txFlag)
        {
            // eeprom read -> uart printf();
            at25160_Read_Arry(0x0100, (uint8_t *)&temperatureC, 2);
            at25160_Read_Arry(0x0200, (uint8_t *)&humidityRH, 2);
            uart0PrintString("\n\rTemp: ");
            printf("%u.%u", temperatureC / 10, temperatureC % 10);
            uart0PrintString("\n\rHumi: ");
            printf("%u.%u", humidityRH / 10, humidityRH % 10);
            txFlag = 0;
        }
    }
    return 0;
}

ISR(TIMER0_OVF_vect)
{
    timerCount++;
    if (timerCount >= 500) // 5초 확인
    {
        timerCount = 0;
        readFlag = 1;
    }
    TCNT0 = 112;
}

ISR(INT4_vect)
{
    txFlag = 1;
}