#include "lcd.h"           // 추가: lcd 라이브러리 포함
#include <avr/interrupt.h> // AVR 인터럽트에 대한 헤더파일
#include <avr/io.h>        //AVR 입출력에 대한 헤더 파일
#include <stdio.h>         // 추가: sprintf 사용
#include <string.h>        // 추가: strlen 사용
#include <util/delay.h>    // delay 함수사용을 위한 헤더파일

volatile unsigned int ADC_result = 0; // 범위 0~1023

int main(void)
{

    DDRB = 0x10;  // 포트B 를 출력포트로 설정한다.
                  // PB4와 LED0을 연결한다.
    TCCR0 = 0x62; // PC PWM 모드, 8 분주
                  // PWM 주기 : F_CPU/256/2/8 = 3.6 KHz
                  // 업카운트시 Clear, 다운카운트시 Set 으로 설정
    TCNT0 = 0x00; // 타이머0 카운터를 초기화 한다.

    ADMUX = 0x40;   // ADC0선택 //single mode, 0번 채널, 3.3V 외부 기준전압(AREF)
    ADCSRA = 0xAF;  // 10101111 //ADC 허가, free running Mode, Interrupt 허가, 128분주
    ADCSRA |= 0x40; // ADSC AD 개시(Start)
    sei();

    lcdInit(); // 추가: LCD 초기화
    lcdGotoXY(0, 0);
    lcdPrintData("Light Sensor", 12);

    while (1)
    {

        OCR0 = (ADC_result - 40) * 255 / 700; // ADC 값의 따라 LED를 제어한다.
        if (ADC_result < 40)
        {
            OCR0 = 0;
        }
        else if (ADC_result > 700)
        {
            OCR0 = 255;
        }
        else
        {
            OCR0 = (ADC_result - 40) * 255 / 660;
        }

        // 추가: ADC 값을 LCD에 표시
        {
            char buf[16];
            sprintf(buf, "L:%u   ", ADC_result); // ADC 원시값 표시, 공백으로 이전 자리 지움.
            lcdGotoXY(0, 1);                     // LCD 두번째 줄에 표시
            lcdPrintData(buf, strlen(buf));
        }

        _delay_ms(200);
    }
}

SIGNAL(ADC_vect)
{
    cli();

    ADC_result = ADC; // 전압이 디지털로 변환된 값 읽어오기. 0-1023

    sei();
}