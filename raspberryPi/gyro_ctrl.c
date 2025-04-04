// Book didnt explain how to use gyro.. Dont be cry.. We have AI friend!
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <wiringPi.h>
#include <wiringPiI2C.h>

#define GYRO_ADDR 0x68

#define MPU6050_PWR_MGMT_1 0x6B
#define GYRO_CONFIG 0x1B
#define ACCEL_CONFIG 0x1C
#define ACCEL_XOUT_H 0x3B
#define GYRO_XOUT_H 0x43


int main(void)
{
    // MPU 6050 I2C file descriptor
    int gyro_fd = wiringPiI2CSetup(GYRO_ADDR);
    delay(100);

    // MPU 6050 initialize
    wiringPiI2CWriteReg8(gyro_fd, MPU6050_PWR_MGMT_1, 0x00);   // release sleep mode  
    wiringPiI2CWriteReg8(gyro_fd, GYRO_CONFIG, 0x00);          // gyro range : 250 degree/s
    wiringPiI2CWriteReg8(gyro_fd, ACCEL_CONFIG, 0x00);         // +- 2g
    delay(100);

    int16_t ax = wiringPiI2CReadReg16(gyro_fd, ACCEL_XOUT_H);
    int16_t ay = wiringPiI2CReadReg16(gyro_fd, ACCEL_XOUT_H + 2);
    int16_t az = wiringPiI2CReadReg16(gyro_fd, ACCEL_XOUT_H + 4);
    int16_t gx = wiringPiI2CReadReg16(gyro_fd, GYRO_XOUT_H);
    int16_t gy = wiringPiI2CReadReg16(gyro_fd, GYRO_XOUT_H + 2);
    int16_t gz = wiringPiI2CReadReg16(gyro_fd, GYRO_XOUT_H + 4);

    printf("ax: %f \n", (float)ax / 16348.0);
    printf("ay: %f \n ", (float)ay / 16348.0);
    printf("az: %f \n", (float)az / 16348.0);
    printf("gx: %f \n", (float)gx / 131.0);
    printf("gy: %f \n", (float)gy / 131.0);
    printf("gz: %f \n", (float)gz / 131.0);

    return 0;
}// Book didnt explain how to use gyro.. Dont be cry.. We have AI friend!
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <wiringPi.h>
#include <wiringPiI2C.h>

#define GYRO_ADDR 0x68

#define MPU6050_PWR_MGMT_1 0x6B
#define GYRO_CONFIG 0x1B
#define ACCEL_CONFIG 0x1C
#define ACCEL_XOUT_H 0x3B
#define GYRO_XOUT_H 0x43


int main(void)
{
    // MPU 6050 I2C file descriptor
    int gyro_fd = wiringPiI2CSetup(GYRO_ADDR);
    delay(100);

    // MPU 6050 initialize
    wiringPiI2CWriteReg8(gyro_fd, MPU6050_PWR_MGMT_1, 0x00);   // release sleep mode  
    wiringPiI2CWriteReg8(gyro_fd, GYRO_CONFIG, 0x00);          // gyro range : 250 degree/s
    wiringPiI2CWriteReg8(gyro_fd, ACCEL_CONFIG, 0x00);         // +- 2g
    delay(100);

    int16_t ax = wiringPiI2CWriteReg16(gyro_fd, ACCEL_XOUT_H);
    int16_t ay = wiringPiI2CWriteReg16(gyro_fd, ACCEL_XOUT_H + 2);
    int16_t az = wiringPiI2CWriteReg16(gyro_fd, ACCEL_XOUT_H + 4); 
    int16_t gx = wiringPiI2CWriteReg16(gyro_fd, GYRO_XOUT_H) << 8
    int16_t gy = wiringPiI2CWriteReg16(gyro_fd, GYRO_XOUT_H + 2);
    int16_t gz = wiringPiI2CWriteReg16(gyro_fd, GYRO_XOUT_H + 4);

    printf("%f", (float)ax / 16348.0);
    printf("%f", (float)ay / 16348.0);
    printf("%f", (float)az / 16348.0);
    printf("%f", (float)gx / 131.0);
    printf("%f", (float)gy / 131.0);
    printf("%f", (float)gz / 131.0);

    return 0;
}