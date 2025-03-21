#include <avr/interrupt.h>
#include <avr/io.h>
#include <util/delay.h>

int main(void)
{
    DDRC = 0x00;
    DDRB |= _BV(PB4);

    TCCR0 = _BV(WGM00) | _BV(WGM01) | _BV(COM01) | _BV(CS01); // clock select 1024 prescale

    uint8_t brightness = 0;
    int8_t delta = 1;

    while (1)
    {
        OCR0 = brightness; // 0~ 255
        _delay_ms(10);
        brightness += delta;
        if (brightness == 0 || brightness == 255)
        {
            delta = -delta;
        }
    }
    return 0;
}