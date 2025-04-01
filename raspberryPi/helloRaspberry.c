#include <stdio.h>
#include <wiringPi.h>

// LED GPIO PIN
#define LED1 23
#define LED2 24
#define LED3 25
#define LED4 1

int main(void){

    wiringPiSetupGpio();    //BCM GPIO PIN
    pinMode(LED1, OUTPUT);  // DDR
    pinMode(LED2, OUTPUT);  // DDR
    pinMode(LED3, OUTPUT);  // DDR
    pinMode(LED4, OUTPUT);  // DDR

    while(1){
        digitalWrite(LED1, HIGH);
        digitalWrite(LED2, HIGH);
        digitalWrite(LED3, HIGH);
        digitalWrite(LED4, HIGH);

    }

    printf("Hello! \n");
    return 0;
}