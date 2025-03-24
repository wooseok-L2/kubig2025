#include <avr/interrupt.h>
#include <avr/io.h>
#include <util/delay.h>

//uint16_t doReMi[8] = {523, 587, 659, 698, 783, 880, 987, 1046};
uint16_t doReMi[] = {783, 783, 880, 880, 783, 783, 659, 783, 783, 659, 659, 587, 783, 783, 880, 880, 783, 783, 659, 783, 659, 587, 659, 523};
uint8_t piano = 0;

int main()
{
    // PB7 핀 피에조 -> OCR1C
    DDRB = _BV(PB7); // 7번 출력 설정

    TCCR1A = _BV(COM1C1) | _BV(WGM11);            // com 10 -> clear on compare
    TCCR1B = _BV(WGM13) | _BV(WGM12) | _BV(CS00); // 분주비 1, fast PWM

    sei(); // 전역 인터럽트 허용

    while (1)
    {
        ICR1 = 14745600 / doReMi[piano]; // 주파수 만큼 duty cycle을 설정 하겠다.
        OCR1C = ICR1 / 2;                // 절반을 on 시키겠다.
        piano++;
        if (piano > 23)
            piano = 0;
        _delay_ms(300);
    }
    return 0;
}