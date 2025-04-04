// 스위치 1,2,3 을 이용해서
// 1-> R 색 변화
// 2-> G 색 변화
// 3-> B 색 변화
// 스위치를 오래 누르면(0 ~ 1 초)-> (0~4095) 높은 값으로 변화 할 수 있게 만들기
// 스위치를 누르고 떼면 -> FND 에 숫자 출력 (0 ~1 초) -> ( 00 ~ 99) ||| ms -> 10ms단위
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <wiringPi.h>
#include <wiringPiI2C.h>

#define RGB_SERVO_I2C_ADDR 0x5e
#define PCA9685_LED_ON_L 0x06
#define PCA9685_PRESCALE 0xFE
#define PCA9685_MODE1 0x00

#define SW1 4
#define SW2 17
#define SW3 27
#define SW4 22

#define DATA_PIN 0
#define LATCH_PIN 5
#define CLOCK_PIN 6

uint8_t numbers[] = {0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x27, 0x7F, 0x67};

void bit_74HC595_shift16(uint8_t digit1, uint8_t digit2);

void SW_ISR1R(void);
void SW_ISR2R(void);
void SW_ISR3R(void);
void SW_ISR1F(void);
void SW_ISR2F(void);
void SW_ISR3F(void);
void i2C_init(int fd, int freq);

int r_value, g_value, b_value;
int r_start_time, g_start_time, b_start_time;
int r_pushed, g_pushed, b_pushed;

int main(void)
{
    int rgb_servo_fd = wiringPiI2CSetup(RGB_SERVO_I2C_ADDR);
    i2C_init(rgb_servo_fd, 0x79); // 50 hz

    wiringPiISR(SW1, INT_EDGE_BOTH, SW_ISR1R);
    wiringPiISR(SW2, INT_EDGE_BOTH, SW_ISR2R);
    wiringPiISR(SW3, INT_EDGE_BOTH, SW_ISR3R);

    pinMode(SW1, INPUT);
    pinMode(SW2, INPUT);
    pinMode(SW3, INPUT);
    pinMode(SW4, INPUT);
    pinMode(DATA_PIN, OUTPUT);
    pinMode(LATCH_PIN, OUTPUT);
    pinMode(CLOCK_PIN, OUTPUT);

    digitalWrite(DATA_PIN, LOW);
    digitalWrite(LATCH_PIN, LOW);
    digitalWrite(CLOCK_PIN, LOW);

    while (1)
    {
        wiringPiI2CWriteReg16(rgb_servo_fd, PCA9685_LED_ON_L + 2, r_value);
        wiringPiI2CWriteReg16(rgb_servo_fd, PCA9685_LED_ON_L + 6, g_value);
        wiringPiI2CWriteReg16(rgb_servo_fd, PCA9685_LED_ON_L + 10, b_value);
    }

    return 0;
}

void i2C_init(int fd, int freq)
{
    wiringPiSetupGpio();
    wiringPiI2CWriteReg8(fd, PCA9685_MODE1, 0x10);    // 리셋
    delay(10);                                        // 리셋 후 대기
    wiringPiI2CWriteReg8(fd, PCA9685_PRESCALE, freq); // 주파수 설정
    wiringPiI2CWriteReg8(fd, PCA9685_MODE1, 0xA1);

    wiringPiI2CWriteReg16(fd, PCA9685_LED_ON_L, 0);     // 빨간색
    wiringPiI2CWriteReg16(fd, PCA9685_LED_ON_L + 4, 0); // 녹색
    wiringPiI2CWriteReg16(fd, PCA9685_LED_ON_L + 8, 0); // 파란색
}

void SW_ISR1R(void)
{
    if (!r_pushed)
    {
        r_start_time = millis();
        r_pushed = 1;
    }
    else
    {
        g_value = 0;
        b_value = 0;
        unsigned int press_time = millis() - r_start_time;
        r_value = (press_time * 4095 / 1000);
        if (r_value >= 4096)
            r_value = 4095;
        printf("R: %d\n", r_value);
        int de2 = (int)((float)r_value / 409.6);
        int de1 = (int)((float)r_value / 40.96) % 10;
        bit_74HC595_shift16(numbers[de1], numbers[de2]);
        r_pushed = 0;
    }
}

void SW_ISR2R(void)
{
    if (!g_pushed)
    {
        g_start_time = millis();
        g_pushed = 1;
    }
    else
    {
        r_value = 0;
        b_value = 0;
        unsigned int press_time = millis() - g_start_time;
        g_value = (press_time * 4095 / 1000);
        if (g_value >= 4096)
            g_value = 4095;
        printf("G: %d\n", g_value);
        int de2 = (int)((float)r_value / 409.6);
        int de1 = (int)((float)r_value / 40.96) % 10;
        bit_74HC595_shift16(numbers[de1], numbers[de2]);
        g_pushed = 0;
    }
}

void SW_ISR3R(void)
{
    if (!b_pushed)
    {
        b_start_time = millis();
        b_pushed = 1;
    }
    else
    {
        g_value = 0;
        r_value = 0;
        unsigned int press_time = millis() - b_start_time;
        b_value = (press_time * 4095 / 1000);
        if (b_value >= 4096)
            b_value = 4095;
        printf("B: %d\n", b_value);
        int de2 = (int)((float)r_value / 409.6);
        int de1 = (int)((float)r_value / 40.96) % 10;
        bit_74HC595_shift16(numbers[de1], numbers[de2]);
        b_pushed = 0;
    }
}

void bit_74HC595_shift16(uint8_t digit1, uint8_t digit2)
{
    uint16_t data = (digit1 << 8) | (digit2 << 0);

    for (int i = 15; i >= 0; i--)
    {
        digitalWrite(LATCH_PIN, LOW);
        digitalWrite(CLOCK_PIN, LOW);
        digitalWrite(DATA_PIN, (data >> i) & 1);
        // xxxxxxxx0 or xxxxxxxx1 & 0000000001
        digitalWrite(LATCH_PIN, HIGH);
        digitalWrite(CLOCK_PIN, HIGH);
        delayMicroseconds(10);
    }
    digitalWrite(LATCH_PIN, LOW);
    delayMicroseconds(10);
    digitalWrite(LATCH_PIN, HIGH);
}