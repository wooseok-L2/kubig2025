#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <wiringPi.h>
#include <wiringPiI2C.h>

#define GYRO_ADDR 0x68

// 자이로 센서 레지스트리 MPU6050
#define MPU6050_PWR_MGMT_1 0x6B
#define GYRO_CONFIG 0x1B
#define ACCEL_CONFIG 0x1C
#define ACCEL_XOUT_H 0x3B
#define GYRO_XOUT_H 0x43

#define BUZZER1 659
#define BUZZER2 880
#define BUZZER_PIN 26

#define LED1 23
#define LED2 24
#define LED3 25
#define LED4 1

void setPWMFrequency(int freq);

int main(void)
{
    wiringPiSetupGpio(); // BCM 기준 gpio 핀번호
    wiringPiSetup(); // wiring pin 번호
    pinMode(BUZZER_PIN, PWM_OUTPUT);
    int led[4] = {LED1, LED2, LED3, LED4};

    // MPU 6050 I2C file descriptor
    int gyro_fd = wiringPiI2CSetup(GYRO_ADDR);
    delay(100);

    // initiation MPU 6050
    wiringPiI2CWriteReg8(gyro_fd, MPU6050_PWR_MGMT_1, 0x00); // 슬립 모드 해제
    wiringPiI2CWriteReg8(gyro_fd, GYRO_CONFIG, 0x00);        // 자이로 범위 250 도/s
    wiringPiI2CWriteReg8(gyro_fd, ACCEL_CONFIG, 0x00);       // 가속도 범위 +-2g
    delay(100);

    const int samples = 100;

    int32_t accel_x_offset = 0, accel_y_offset = 0, accel_z_offset = 0;
    int32_t gyro_x_offset = 0, gyro_y_offset = 0, gyro_z_offset = 0;
    for (int i = 0; i < samples; i++)
    {
        int16_t ax = (wiringPiI2CReadReg8(gyro_fd, ACCEL_XOUT_H) << 8) | wiringPiI2CReadReg8(gyro_fd, ACCEL_XOUT_H + 1);
        int16_t ay = (wiringPiI2CReadReg8(gyro_fd, ACCEL_XOUT_H + 2) << 8) | wiringPiI2CReadReg8(gyro_fd, ACCEL_XOUT_H + 3);
        int16_t az = (wiringPiI2CReadReg8(gyro_fd, ACCEL_XOUT_H + 4) << 8) | wiringPiI2CReadReg8(gyro_fd, ACCEL_XOUT_H + 5);
        int16_t gx = (wiringPiI2CReadReg8(gyro_fd, GYRO_XOUT_H) << 8) | wiringPiI2CReadReg8(gyro_fd, GYRO_XOUT_H + 1);
        int16_t gy = (wiringPiI2CReadReg8(gyro_fd, GYRO_XOUT_H + 2) << 8) | wiringPiI2CReadReg8(gyro_fd, GYRO_XOUT_H + 3);
        int16_t gz = (wiringPiI2CReadReg8(gyro_fd, GYRO_XOUT_H + 4) << 8) | wiringPiI2CReadReg8(gyro_fd, GYRO_XOUT_H + 5);
        accel_x_offset += ax;
        accel_y_offset += ay;
        accel_z_offset += az;
        gyro_x_offset += gx;
        gyro_y_offset += gy;
        gyro_z_offset += gz;
        delay(10);
    }
    accel_x_offset /= 100;
    accel_y_offset /= 100;
    accel_z_offset /= 100;
    gyro_x_offset /= 100;
    gyro_y_offset /= 100;
    gyro_z_offset /= 100;
    accel_z_offset -= 16384.0;

    for (int i = 0; i < 4; ++i)
    {
        pinMode(led[i], OUTPUT);
    }

    while (1)
    {

        int16_t ax = (wiringPiI2CReadReg8(gyro_fd, ACCEL_XOUT_H) << 8) | wiringPiI2CReadReg8(gyro_fd, ACCEL_XOUT_H + 1);
        int16_t ay = (wiringPiI2CReadReg8(gyro_fd, ACCEL_XOUT_H + 2) << 8) | wiringPiI2CReadReg8(gyro_fd, ACCEL_XOUT_H + 3);
        int16_t az = (wiringPiI2CReadReg8(gyro_fd, ACCEL_XOUT_H + 4) << 8) | wiringPiI2CReadReg8(gyro_fd, ACCEL_XOUT_H + 5);
        int16_t gx = (wiringPiI2CReadReg8(gyro_fd, GYRO_XOUT_H) << 8) | wiringPiI2CReadReg8(gyro_fd, GYRO_XOUT_H + 1);
        int16_t gy = (wiringPiI2CReadReg8(gyro_fd, GYRO_XOUT_H + 2) << 8) | wiringPiI2CReadReg8(gyro_fd, GYRO_XOUT_H + 3);
        int16_t gz = (wiringPiI2CReadReg8(gyro_fd, GYRO_XOUT_H + 4) << 8) | wiringPiI2CReadReg8(gyro_fd, GYRO_XOUT_H + 5);

        printf("ax : %f\n", ((float)ax - accel_x_offset) / 16384.0);
        printf("ay : %f\n", ((float)ay - accel_y_offset) / 16384.0);
        printf("az : %f\n", ((float)az - accel_z_offset) / 16384.0);
        printf("gx : %f\n", ((float)gx - gyro_x_offset) / 131.0);
        printf("gy : %f\n", ((float)gy - gyro_y_offset) / 131.0);
        printf("gz : %f\n", ((float)gz - gyro_z_offset) / 131.0);

        int16_t aax = ((float)ax - accel_x_offset) / 16384.0;
        int16_t aay = ((float)ay - accel_x_offset) / 16384.0;
        int16_t aaz = ((float)az - accel_x_offset) / 16384.0;
        int16_t ggx = ((float)gx - gyro_x_offset) / 131.0;
        int16_t ggy = ((float)gy - gyro_x_offset) / 131.0;
        int16_t ggz = ((float)gz - gyro_x_offset) / 131.0;
        

        if (abs(aax) >= 3 || abs(aay) >= 3 || abs(aaz) >= 3){
            digitalWrite(led[0], HIGH);
            digitalWrite(led[1], HIGH);

            setPWMFrequency(BUZZER1);
            pwmWrite(BUZZER_PIN, 1000);
        }
        else if (abs(ggx) >= 3 || abs(ggy) >= 3 || abs(ggz) >= 3){
            digitalWrite(led[2], HIGH);
            digitalWrite(led[3], HIGH);

            setPWMFrequency(BUZZER2);
            pwmWrite(BUZZER_PIN, 1000);
        }
        else {
            for (int i = 0; i < 4; i++){
                digitalWrite(led[i], LOW);
            }
        }

        delay(1000);
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