// LED 를 0.3 초 간격으로 좌우로 움직이세요.
// timer3 을 쓰서 인터럽트로 구현하세요.
// 분주비는 256을 쓰세요. 책 318 페이지.
// 인터럽트가 0.3초 마다 일어나게 하세요.

#include <avr/interrupt.h>
#include <avr/io.h>
#include <util/delay.h>

volatile uint8_t ledData = 0x01;
volatile uint8_t direction = 0;

int main()
{
    DDRC = 0x0F; // 1, 2, 3, 4 출력 설정

    TCCR3A = 0x00;
    TCCR3B = _BV(CS32); // 분주비 1 16Mhz 16000000/65536 = 244.144 Hz
    // 분주비 256 16Mhz 16000000/256 = 62500 Hz  18750--> 3.33 Hz--> 1950 count 46786
    ETIMSK = _BV(TOIE3);
    TCNT3 = 46786; // 시작 카운트 숫자
    sei();         // 전역 인터럽트 허용

    while (1)
        PORTC = ledData;
    return 0;
}

ISR(TIMER3_OVF_vect)
{
    cli();
    TCNT3 = 46786;
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

    PORTC = ledData;
    sei();
}
