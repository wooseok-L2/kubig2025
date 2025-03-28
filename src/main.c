
#include "farmsql.h"
#include "serial.h"
#include "pthread.h"
#include "lcd.h"
#include "uart0.h"
#include <util/delay.h>
#include <avr/interrupt.h>
#include "SHT2x.h"
#include "TWI_driver.h"

void get_sensor_data(SensorData *tx);
uint16_t read_adc(uint8_t channel);
void send_uart_data(SensorData *tx);
void printf_2dot1(uint8_t sense, uint16_t sense_temp);
volatile unsigned int ADC_result = 0; // 범위 0~1023
uint16_t temperaturC, humidityRH;

int main(void){

    MySQLConnection sqlinfo; // sql 데이터 저장 변수
    SaveDataArgs args;       // sql, sensordata 넣는 구조체
    SensorData rx;           // 수신 sensor data 저장
    SensorData tx;           // 송신 sensor data 저장
    const char *port_name;   // 포트이름 설정
    uint16_t buffer[10];     // 수신데이터 저장
    struct sp_port *port;    // 포트 포인터 저장 변수
    pthread_t save_thread;   // pthread ID
    initMySQL(*sqlinfo);     // sql 초기화
    port = setup_serial_port(port_name);     //시리얼 포트 설정


    uart0Init();
    lcdInit();
    SHT2x_Init();
    nt16 sRH;
    nt16 sT;
    uint8_t error;

    stdin = &INPUT;
    stdout = &OUTPUT;

    DDRC = 0x0F; // 1, 2, 3, 4 출력 설정.
    ADMUX = 0x40;   // ADC0 single mode, 0번 채널, 3.3V 외부 기준 전압(AREF)
    ADCSRA = 0xAF;  // 10101111 ADC 허가, free running mode, Intterrupt en, 128 분주비
    ADCSRA |= 0x40; // ADC 개시
    sei();          // 전역 인터럽트 허용

    lcdGotoXY(0, 0);

    while(1){
        {
            error |= SHT2x_MeasureHM(HUMIDITY, &sRH);
            error |= SHT2x_MeasureHM(TEMP, &sT);
            temperaturC = SHT2x_CalcTemperatureC(sT.u16) * 10;
            humidityRH = SHT2x_CalcRH(sRH.u16) * 10;
            if (error == SUCCESS)
            {
                lcdGotoXY(0, 0);
                printf_2dot1(TEMP, temperaturC);
                lcdGotoXY(0, 1);
                printf_2dot1(HUMIDITY, humidityRH);
            }
            else
            {
                lcdGotoXY(0, 0);
                lcdPrintData(" Temp: --.-C", 12);
                lcdGotoXY(0, 1);
                lcdPrintData(" Humi: --.-%", 12);
            }
            _delay_ms(1000);
        }

        {
            char buf[16];
            sprintf(buf, "L:%u   ", ADC_result); // ADC 원시값 표시, 공백으로 이전 자리 지움.
            lcdGotoXY(0, 1);                     // LCD 두번째 줄에 표시
            lcdPrintData(buf, strlen(buf));
            _delay_ms(1000);
        }
        get_sensor_data(tx);

        // save data in sql
        receive_serial_data(port, buffer);    //SensorData rx에 데이터 저장
        args.mysql = sqlinfo;
        args.data = rx;

        // pthread를 사용해 스레드 생성
        pthread_create(&save_thread, NULL, saveDataThread, &args);
        // 스레드 종료 대기
        pthread_join(save_thread, NULL); // 스레드 종료 대기
        // MySQL 연결 종료
        closeMySQL(sqlinfo);


    
    }
}


void get_sensor_data(SensorData *tx) {
    tx->temperature = temperaturC; // ADC 채널 0에서 온도 데이터 읽기
    tx->humidity = humidityRH;    // ADC 채널 1에서 습도 데이터 읽기
    tx->light = ADC_result ;       // ADC 채널 3에서 조도 데이터 읽기
}


// atmega -> pc 구조체 저장된 데이터를 바이트 배열로 변환
void send_uart_data(SensorData *tx) {
    uint16_t *data = (uint16_t *)tx;
    for (int i = 0; i < sizeof(SensorData); i++) {
        while (!(UCSR0A & (1 << UDRE0)));   // UART 송신 가능 대기
        UDR0 = data[i];                     // 데이터 전송

    }
}

void printf_2dot1(uint8_t sense, uint16_t sense_temp)
{
    uint8_t s100, s10;
    if (sense == TEMP)
    {
        lcdPrintData(" Temp: ", 7);

        s100 = sense_temp / 100; // 100의 자리
        if (s100 > 0)
            lcdDataWrite(s100 + '0');

        s10 = sense_temp / 10 - s100 * 10; // 10의 자리
        if (s10 > 0)
            lcdDataWrite(s10 + '0');
        lcdDataWrite('.');                   // . 프린트
        lcdDataWrite(sense_temp % 10 + '0'); // 1의 자리
        lcdDataWrite('C');                   // C 프린트
    }
    else if (sense == HUMIDITY)
    {
        lcdPrintData(" Humi: ", 7);
        s100 = sense_temp / 100; // 100의 자리
        if (s100 > 0)
            lcdDataWrite(s100 + '0');

        s10 = sense_temp / 10 - s100 * 10; // 10의 자리
        if (s10 > 0)
            lcdDataWrite(s10 + '0');
        lcdDataWrite('.');                   // . 프린트
        lcdDataWrite(sense_temp % 10 + '0'); // 1의 자리
        lcdDataWrite('%');                   // % 프린트
    }
}

SIGNAL(ADC_vect)
{
    cli();

    ADC_result = ADC; // 전압이 디지털로 변환된 값 읽어오기. 0-1023

    sei();
}