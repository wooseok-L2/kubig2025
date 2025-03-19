#include <avr/interrupt.h>
#include <avr/io.h>

volatile unsigned long milliseconds = 0;

// void calcmilli(void)
// {
//     // 계산 하는 코드 ...
//     ++milliseconds;
// }
ISR(TIMER0_OVF_vect)
{
    ++milliseconds;
}

void timer0_init(void)
{
    TCCR0 = _BV(CS01) | _BV(CS00);
    TCNT0 = 6;
    TIMSK |= _BV(TOIE0);
    sei();
}

int main()
{
    timer0_init();
    DDRC = 0x01;  // C 0 비트 출력 설정
    PORTE = 0xFF; // 풀업 설정

    unsigned long lastDebounceTime = 0;
    const unsigned long debouceDelay = 20;
    uint8_t lastButtonState = 1;
    uint8_t buttonState = 1;

    while (1)
    {
        uint8_t reading = PINE & _BV(PE0);

        // 버튼 상태 변경 확인
        if (reading != lastButtonState)
        {
            lastDebounceTime = milliseconds;
        }

        // 디바운스 시간 경과 확인
        if ((milliseconds - lastDebounceTime) > debouceDelay)
        {
            // 실제 버튼 상태 업데이트
            if (reading != buttonState)
            {
                buttonState = reading;

                // 버튼이 눌렸을 때 동작 수행
                if (buttonState == 0)
                {
                    PORTC ^= _BV(PC0);
                }
            }
        }

        // 마지막 상태 저장
        lastButtonState = reading;
    }

    return 0;
}