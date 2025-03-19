#include <avr/io.h>
#include <util/delay.h>


int main(){

    while(1){
        DDRC = 0x03;    // 0011  0,1 is output mode
        PORTC = 0x0F;   // 1111  0,1,2,3 is ON(1) -> 5V output
        _delay_ms(500);

        PORTC = 0x00;   // 0000  0,1,2,3 is OFF(0) -> 0V output
        _delay_ms(500);
    }

    return 0;
}