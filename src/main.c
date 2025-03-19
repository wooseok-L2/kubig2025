
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

volatile unit8_t shiftFlag = 1;

int main()
{
    uint8_t ledData = 0x01;

    DDRC = 0x0f;
    EIMSK = 0xa0;     //0b10100000   int 5,  int 7
    EICRB = 0xc8;     // interrupt 5 is down, 7 is up
    EIFR = 0xa0;      // flag clear
    sei();

    while(1){
        PORTC
    }

    return 0;
}

ISR(INT5_vect){
    cli();
    shiftFlag = 1;
    sei();
}

ISR(INT7_vect){
    cli();
    shiftFlag = 2;
    sei();
}