// cc helloRaspberry.c -lwiringPi

#include <stdio.h>
#include <wiringPi.h>
#include <softPwm.h>
#include <softTone.h>

// gpio pin
#define BUZZER_PIN 12

int doReMi[8] = {523, 587, 659, 698, 783, 880, 987, 1046};

int main(void)
{
    wiringPiSetupGpio(); // BCM 기준 gpio 핀번호
    pinMode(BUZZER_PIN, OUTPUT);

    // set pwm (this is software pwm -> do not use this code for cpu)
    softToneCreate(BUZZER_PIN);
    while (1)
    {
        for (int i = 0; i < 255; i++){
            softToneWrite(BUZZER_PIN, doReMi[i]);
            delay(100);
        }
        
    }
    printf("안녕하세요!");
    return 0;
}