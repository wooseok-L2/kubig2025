// cc helloRaspberry.c -lwiringPi

#include <stdio.h>
#include <wiringPi.h>
#include <softPwm.h>

// gpio pin
#define LED1 23
#define LED2 24
#define LED3 25
#define LED4 1

int main(void)
{
    wiringPiSetupGpio(); // BCM 기준 gpio 핀번호
    pinMode(LED1, OUTPUT);
    pinMode(LED2, OUTPUT);
    pinMode(LED3, OUTPUT);
    pinMode(LED4, OUTPUT);

    // set pwm (this is software pwm -> do not use this code for cpu)
    softPwmCreate(LED1, 255, 255);
    softPwmCreate(LED2, 120, 255);
    softPwmCreate(LED3, 0, 255);
    softPwmCreate(LED4, 0, 255);

    while (1)
    {
        for (int i = 0; i < 255; i++){
            softPwmWrite(LED4, i);
            delay(100);
        }
        
    }
    printf("안녕하세요!");
    return 0;
}