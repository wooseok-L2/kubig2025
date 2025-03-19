#include <avr/io.h>
#include <util/delay.h>

int main(){
    
    while(1){
    
        PORTC = 0x00;       // 0b00000000    
        _delay_ms(1000);    // wait 1 second
        PORTC = 0x0f;       // 0b00001111
        _delay_ms(1000);
    }

    return 0;
}

// int main(){
    
//     while(1){
    
//         PORTC = 0x00;       // 0b00000000    
//         _delay_ms(1000);    // wait 1 second
//         PORTC = 0x0f;       // 0b00001111
//         _delay_ms(1000);
//         PORTC = 0x00;       // 0b00000000    
//         _delay_ms(1000);    // wait 1 second
//         PORTC = 0x0e;       // 0b00001110
//         _delay_ms(1000);
//         PORTC = 0x00;       // 0b00000000
//         _delay_ms(1000);
//         PORTC = 0x0c;       // 0b00001100
//         _delay_ms(1000);
//         PORTC = 0x00;       // 0b00000000
//         _delay_ms(1000);
//         PORTC = 0x08;       // 0b00001000
//         _delay_ms(1000);
        
//     }

//     return 0;
// }