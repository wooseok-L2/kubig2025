#include "pjsql.h"
#include "serial.h"

// 시리얼 포트 설정 함수
struct sp_port *setup_serial_port(const char *port_name) {
    struct sp_port *port;
    sp_get_port_by_name(port_name, &port);
    sp_open(port, SP_MODE_READ_WRITE);
    sp_set_baudrate(port, 9600);  // Baud rate 설정
    printf("Serial port %s opened successfully.\n", port_name);
    
    return port;
}

// 시리얼 데이터 전송
void *send_serial_data(void *arg, char *tx) {
    ThreadData *data = (ThreadData *)arg;
    int tx_bytes;

    tx_bytes = sp_blocking_write(data->port, tx, sizeof(tx), 1000);
    if (read_bytes > 0){
        printf("Sent serial data: %s\n", tx);
    }
    else {
        printf("Error reading data: %d\n", tx_bytes);
    }

    return tx;
}

// 시리얼 데이터 수신 함수
void *receive_serial_data(void *arg, char *buffer) {
    ThreadData *data = (ThreadData *)arg;
    int read_bytes;

    read_bytes = sp_blocking_read(data->port, buffer, sizeof(buffer), 1000);
    if (read_bytes > 0){
        printf("Received serial data: %s\n", buffer);
    }
    else{
        printf("Error reading data: %d\n", read_bytes);
    }
    return buffer;
}