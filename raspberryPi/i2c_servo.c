
#include <stdio.h>
#include <wiringPi.h>
#include <wiringPiI2C.h>

#define RGB_SERVO_I2C_ADDR 0x5e
#define PCA9685_LED_ON_L 0x06
#define PCA9685_PRESCALE 0xFE
#define PCA9685_MODE1 0x00

void i2C_init(int fd, int freq);

int main(void)
{
    wiringPiSetupGpio();
    int rgb_servo_fd = wiringPiI2CSetup(RGB_SERVO_I2C_ADDR);
    i2C_init(rgb_servo_fd, 0x79); // 50 hz 20ms 1.0 ~ 2.0

    int servo_0 = 120;
    int servo_180 = 500;

    wiringPiI2CWriteReg16(rgb_servo_fd, PCA9685_LED_ON_L + 12, 0);       // servo1 on_off
    wiringPiI2CWriteReg16(rgb_servo_fd, PCA9685_LED_ON_L + 14, servo_0); // servo1 pwm duty
    delay(10);
    wiringPiI2CWriteReg16(rgb_servo_fd, PCA9685_LED_ON_L + 16, 0);       // servo2
    wiringPiI2CWriteReg16(rgb_servo_fd, PCA9685_LED_ON_L + 18, servo_0); // servo2 pwm duty
    delay(1000);
    printf("set \n");

    wiringPiI2CWriteReg16(rgb_servo_fd, PCA9685_LED_ON_L + 14, servo_180 / 2); // servo1 pwm duty
    wiringPiI2CWriteReg16(rgb_servo_fd, PCA9685_LED_ON_L + 18, servo_180 / 2); // servo2 pwm duty
    delay(1000);
    printf("set 90\n");

    wiringPiI2CWriteReg16(rgb_servo_fd, PCA9685_LED_ON_L + 14, servo_180); // servo1 pwm duty
    wiringPiI2CWriteReg16(rgb_servo_fd, PCA9685_LED_ON_L + 18, servo_180); // servo2 pwm duty
    delay(1000);
    printf("set 180\n");

    // free
    wiringPiI2CWriteReg16(rgb_servo_fd, PCA9685_LED_ON_L + 14, 0); // servo1 pwm duty
    wiringPiI2CWriteReg16(rgb_servo_fd, PCA9685_LED_ON_L + 18, 0); // servo2 pwm duty

    return 0;
}

void i2C_init(int fd, int freq)
{
    wiringPiI2CWriteReg8(fd, PCA9685_MODE1, 0x10);    // 리셋
    wiringPiI2CWriteReg8(fd, PCA9685_PRESCALE, freq); // 주파수 설정
    wiringPiI2CWriteReg8(fd, PCA9685_MODE1, 0xA1);
}