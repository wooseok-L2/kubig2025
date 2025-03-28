#include "pthread.h"

void *saveDataThread(void *arg) {
    SaveDataArgs *data_args = (SaveDataArgs *)arg;

    saveData(data_args->mysql, data_args->data);   // sql 데이터 저장

    return NULL;
}