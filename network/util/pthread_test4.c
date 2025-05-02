#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define THREAD_NUM 5

char *thread_main(void *arg);
long long num = 0;
pthread_mutex_t mtx;

int main()
{
    pthread_t t_id[THREAD_NUM];
    void *thr_ret;
    int range[5][2] = {{1, 5}, {6, 10}, {11, 15}, {16, 20}, {21, 25}};

    for (int i = 0; i < THREAD_NUM; ++i)
        pthread_create(&t_id[i], NULL, (void *)thread_main, (void *)&range[i]);
    // 쓰레드 동작!!

    for (int i = 0; i < THREAD_NUM; ++i)
    {
        pthread_join(t_id[i], &thr_ret); // 쓰레드가 리턴 될때까지 대기!!
        printf("쓰레드에서 받아온 메세지: %s \n", (char *)thr_ret);
        free(thr_ret);
    }
    printf("쓰레드 끝 메인 시작!! \n");
    for (int i = 0; i < 3; i++)
    {
        sleep(1);
        puts("running main()");
    }
    printf("num: %lld \n", num);
    return 0;
}

char *thread_main(void *arg)
{
    int start = ((int *)arg)[0];
    int end = ((int *)arg)[1];
    int incre = 1;
    char *msg = (char *)malloc(sizeof(char) * 50);
    strcpy(msg, "Hello, I'am from thread--- \n");
    if (start > 10)
    {
        incre = -1;
    }
    for (int i = start * 1000000; i < end * 1000000; i++)
    {
        pthread_mutex_lock(&mtx);
        num += incre;
        pthread_mutex_unlock(&mtx);
    }

    return msg;
}