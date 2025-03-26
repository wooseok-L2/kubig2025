#ifndef SERIAL_H
#define SERIAL_H

#include "pjsql.h"
#include <serialport.h>
#include <pthread.h>

// 데이터 송수신 및 DB 작업에 필요한 구조체 정의
typedef struct {
    struct sp_port *port;
    MYSQL *conn;
} ThreadData;

// 시리얼 포트 설정 함수
struct sp_port *setup_serial_port(const char *port_name);

// 시리얼 데이터 전송
void *send_serial_data(void *arg, char *tx);

// 시리얼 데이터 수신 함수
void *receive_serial_data(void *arg, char *buffer);

