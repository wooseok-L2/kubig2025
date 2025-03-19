// 인터럽트로 FND 를 점멸.
// INT5  phase 1 -> phase 2 or phase 2 -> phase 1
// phase 1 : FND 가 빠르게 상승하는 코드 ms 100
// phase 2 : FND 를 순간 멈추게 함.
#include <avr/interrupt.h>
#include <avr/io.h>
#include <util/delay.h>

volatile uint8_t timeStop = 0; // 인터럽트에서 쓸 변수

int main()
{
    uint8_t numbers[] = {0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x27, 0x7F, 0x67};
    uint8_t count = 0;
    DDRA = 0xFF;

    EIMSK = 0x20; // 0b00100000  INT5, INT7
    // EICRB = 0x08; // 0b11001000인터럽트 5는 하강, 인터럽트7은 상승.
    EICRB = _BV(ISC50) | _BV(ISC51);
    sei();

    while (1)
    {
        if (timeStop == 0)
        {
            PORTA = numbers[count];
            count = (count + 1) % 10;
        }
        _delay_ms(100);
    }
    return 0;
}

SIGNAL(INT5_vect)
{
    cli(); // sei() 반대 설정 SREG -> I unset -> 0
    timeStop ^= 1;
    sei();
}