#include "farmsql.h"
#include "serial.h"

// 시리얼 포트 설정 함수   ATmega uart 송수신 설정값과 동일하게 셋팅 필요
struct sp_port *setup_serial_port(const char *port_name) {
    struct sp_port *port;
    sp_get_port_by_name(port_name, &port);
    sp_open(port, SP_MODE_READ_WRITE);  //SP_MODE_READ_WRITE는 상수로 정의된 값
    sp_set_baudrate(port, 9600);  // Baud rate 설정
    printf("Serial port %s opened successfully.\n", port_name);
    
    return port;
}

// 시리얼 데이터 전송    아마 사용안 할 듯?
void *send_serial_data(struct sp_port *port, SensorData *tx) {
    int tx_bytes;

    tx_bytes = sp_blocking_write(port, tx, sizeof(*tx), 1000);
    if (tx_bytes > 0){
        printf("Sent serial data\n");
    }
    else {
        printf("Error reading data: %d\n", tx_bytes);
    }

    return 0;
}

// 시리얼 데이터 수신 함수
void *receive_serial_data(struct sp_port *port, uint16_t *buffer) {
    int read_bytes;

    read_bytes = sp_blocking_read(port, buffer, sizeof(buffer), 1000);
    if (read_bytes == sizeof(buffer)){
        
        // SensorData 구조체로 매핑
        // memcpy(rx, buffer, sizeof(SensorData));   구조체 바이트 배열로 데이터 수신받으면 사용 가능
        rx.temperature = buffer[0];
        rx.humidity = buffer[1];
        rx.soil = buffer[2];
        rx.sun = buffer[3];
        rx.cond = buffer[4];
        printf("Received serial data \n");
        
        // 구조체 저장 데이터 확인
        printf("Received data: temp=%d, humid=%d, soil=%d, sun=%d, cond=%d\n",
            rx->temperature, rx->humidity, rx->soil, rx->sun, rx->cond);
        
    }
    else{
        printf("Error reading data: %d\n", read_bytes);
    }
    return 0;
}

// https://www.joinc.co.kr/w/Site/Thread/Beginning/PthreadApiReference              pthread
// https://sigrok.org/api/libserialport/unstable/a00018.html                        libserialport
// https://docs.oracle.com/cd/E26502_01/html/E35303/tlib-1.html#tlib-79569          pthread