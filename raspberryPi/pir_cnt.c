// cc helloRaspberry.c -lwiringPi

#include <stdio.h>
#include <wiringPi.h>

// gpio pin
#define LED1 23
#define LED2 24
#define LED3 25
#define LED4 1
#define PIR_PIN 7

void SW_ISR1(void);

int main(void)
{
    wiringPiSetupGpio(); // BCM 기준 gpio 핀번호
    int led[4] = {LED1, LED2, LED3, LED4};

    pinMode(LED1, OUTPUT);
    pinMode(LED2, OUTPUT);
    pinMode(LED3, OUTPUT);
    pinMode(LED4, OUTPUT);
    pinMode(PIR_PIN, INPUT);
    
    while (1)
    {
        if (digitalRead(PIR_PIN) == HIGH){
            printf("PIR detect \n");
            for (int i = 0; i < 4; i++){

                digitalWrite(led[i], HIGH);
            }
            delay(3000);   
            for (int i = 0; i < 4; i++){

                digitalWrite(led[i], LOW);
            }
        }
    }

    return 0;
}
