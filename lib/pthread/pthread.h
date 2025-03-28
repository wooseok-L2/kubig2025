#ifndef PTHREAD_H
#define PTHREAD_H

#include "farmsql.h"
#include "serial.h"

// 데이터 송수신 및 DB 작업에 필요한 구조체 정의
typedef struct {
    MySQLConnection *mysql;
    SensorData data;
} SaveDataArgs;


void *saveDataThread(void *arg);


#endif 