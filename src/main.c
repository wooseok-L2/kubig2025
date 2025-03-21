// uart를 이용해서 시리얼 통신으로 센서 값을 0.1초 간격으로 출력 기능 추가하세요.-
// --> CDS ADC_data : xxxx

#include "lcd.h"
#include "uart0.h"
#include <avr/interrupt.h>
#include <avr/io.h>
#include <stdio.h>
#include <string.h>
#include <util/delay.h>

volatile uint16_t adcResult = 0;

int main()
{
    uart0Init();
    lcdInit();

    stdin = &INPUT;
    stdout = &OUTPUT;

    DDRC = 0x0F; // 1, 2, 3, 4 출력 설정.

    ADMUX = 0x40;   // ADC0 single mode, 0번 채널, 3.3V 외부 기준 전압(AREF)
    ADCSRA = 0xAF;  // 10101111 ADC 허가, free running mode, Intterrupt en, 128 분주비
    ADCSRA |= 0x40; // ADC 개시
    sei();          // 전역 인터럽트 허용
    printf("Hi, I'm Atmega128");

    lcdGotoXY(0, 0);
    lcdPrintData("Light Sensor", 12);
    char buf[16];
    uint16_t onTime, offTime;
    while (1)
    {
        lcdGotoXY(0, 1);
        // sprintf(buf, "L: %u", adcResult);
        // lcdPrintData(buf, strlen(buf));
        // printf("CDS ADC_data : %u\r\n", adcResult);
        // 시간 연산
        onTime = (adcResult - 100);
        if (onTime < 0)
            onTime = 0;
        if (onTime > 700)
            onTime = 700;
        offTime = 700 - onTime;
        PORTC = 0x0F;
        // 켜지는 시간 딜레이
        for (int i = 0; i < onTime; ++i)
            _delay_ms(1);
        PORTC = 0x00;
        // 꺼지는 시간 딜레이
        for (int i = 0; i < offTime; ++i)
            _delay_ms(1);
    }
    return 0;
}

ISR(ADC_vect)
{
    cli();
    adcResult = ADC; // 2^16 -> 0 ~ 1023
    sei();
}