// PWM 설정 fast pwm, timer3, COM3A1 설정
// FND 설정
// 버저를 이용한 프로그램
// 버튼 인터럽트로 활성화 PE4, 5, 6, 7
// 버튼에 맞는 소리를 2초 동안 출력합니다. 2초 후에는 무음이 되어야 합니다.
// FND 에 버튼이 눌린 번호(0, 1, 2, 3) 를 출력합니다.

#include <avr/delay.h>
#include <avr/interrupt.h>
#include <avr/io.h>

uint16_t doReMi[8] = {523, 587, 659, 698, 783, 880, 987, 1046};
volatile uint8_t playBuzzerOn = 0;
volatile uint8_t piano = 0;
uint8_t numbers[] = {0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x27, 0x7F, 0x67};
#define PWM_SETUP _BV(COM3A1) | _BV(WGM31)

int main(void)
{
    DDRE = 0x08; // PE3 출력 - com3a
    DDRA = 0xFF; // fnd 출력

    // 타이머 세팅
    TCCR3A = PWM_SETUP;
    TCCR3B = _BV(WGM33) | _BV(WGM32) | _BV(CS00); // 분주비 1, fast PWM
    // TCCR3B = 0x19;
    // TCCR1B = _BV(WGM13) | _BV(WGM12) | _BV(CS00); // 분주비 1, fast PWM
    TCCR3C = 0x00;

    // 인터럽트 세팅 스위치 4,5,6,7
    EIMSK = 0xF0; //
    EICRB = 0xFF; //

    sei();
    while (1)
    {
        if (playBuzzerOn)
        {
            // 스위치에 맞는 소리내기
            ICR3 = 14745600 / doReMi[piano];
            OCR3A = ICR3 / 2;
            TCCR3A = PWM_SETUP;
            TCCR3B = _BV(WGM33) | _BV(WGM32) | _BV(CS00); // 분주비 1, fast PWM
            PORTA = numbers[piano];

            _delay_ms(2000);
            TCCR3A = 0x00; // 버저 끄기
            PORTA = 0x00;  // FND 끄기
            playBuzzerOn = 0;
        }
    }
    return 0;
}

ISR(INT4_vect)
{
    cli(); // sei() 반대 설정 SREG -> I unset -> 0
    playBuzzerOn = 1;
    piano = 0;
    sei();
}

ISR(INT5_vect)
{
    cli();
    playBuzzerOn = 1;
    piano = 1;
    sei();
}

ISR(INT6_vect)
{
    cli();
    playBuzzerOn = 1;
    piano = 2;
    sei();
}

ISR(INT7_vect)
{
    cli();
    playBuzzerOn = 1;
    piano = 3;
    sei();
}