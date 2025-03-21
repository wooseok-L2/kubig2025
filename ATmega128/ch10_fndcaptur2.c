#include <avr/interrupt.h>
#include <avr/io.h>

uint8_t numbers[] = {0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x27, 0x7F, 0x67};
volatile uint8_t timeS = 0x01;
volatile uint8_t timer1Cnt;

int main()
{
    DDRA = 0xFF; // FND led 출력 설정
    DDRE = 0x00;

    TCCR1A = 0x00;
    TCCR1B = 0x05; // 분주비 1024

    OCR1A = 14400;                                  // 65535 / 28800 에서 인터럽트 A
    OCR1B = 28800;                                  // 65535 / 28800 에서 인터럽트 B
    TIMSK = _BV(OCIE1A) | _BV(OCIE1B) | _BV(TOIE1); // compare 인터럽트 Enable
    // ETIFR |= _BV(ICF3);
    sei(); // 전역 인터럽트 허용
    PORTA = numbers[0];
    while (1)
    {
        PORTA = numbers[timeS];
        if (timeS > 10)
            timeS = 0;
    }
    return 0;
}

ISR(TIMER1_COMPA_vect)
{
    cli();
    timeS++;
    sei();
}

ISR(TIMER1_COMPB_vect)
{
    cli();
    timeS--;
    sei();
}

ISR(TIMER1_OVF_vect)
{
    cli();
    timeS++;
    sei();
}