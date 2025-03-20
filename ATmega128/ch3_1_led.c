#include <avr/io.h>
#include <util/delay.h>


int main(){

    unsigned char led_data;
    led_data = 0x01;
    int direction = 0;

    while(1){
    // led 1000 -> 0100 -> 0010 -> 0001 -> 0010 -> 0100 -> 1000

        while(1){

            if(led_data > 0x04){
                direction = 0;
            }

            if(led_data == 0){
                direction = 1;
                led_data = 1;
            }

            if(direction){
                led_data >>= 1;
            }
            else{
                led_data <<= 1;
            }

            PORTC = led_data;
            _delay_ms(500);
        }

    }

    return 0;
}