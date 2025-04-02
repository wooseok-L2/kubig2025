// cc helloRaspberry.c -lwiringPi

#include <stdio.h>
#include <wiringPi.h>

// gpio pin
#define LED1 23
#define LED2 24
#define LED3 25
#define LED4 1

int main(void)
{
    wiringPiSetupGpio(); // BCM 기준 gpio 핀번호
    pinMode(LED1, OUTPUT);
    while (1)
    {
        digitalWrite(LED1, HIGH);
    }
    printf("안녕하세요!");
    return 0;
}