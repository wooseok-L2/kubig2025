#include <stdio.h>
#include <wiringPi.h>

#define BUZZER_PIN 26

int doReMi[8] = {523, 587, 659, 698, 783, 880, 987, 1046};
void setPWMFrequency(int freq);

int main(void)
{
    wiringPiSetup(); // wiring pin 번호
    pinMode(BUZZER_PIN, PWM_OUTPUT);
    // set PWM
    while (1)
    {
        for (int i = 0; i < 8; ++i)
        {
            setPWMFrequency(doReMi[i]);
            pwmWrite(BUZZER_PIN, 1000);
            delay(1000);
        }
    }
    return 0;
}

void setPWMFrequency(int freq)
{
    int range = 2000;
    int clock = 19200000 / (range * freq); // 19.2Mhz base clock
    pwmSetMode(PWM_MODE_MS);
    pwmSetRange(range);
    pwmSetClock(clock);
}