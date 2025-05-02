#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define THREAD_NUM 5

char *thread_main(void *arg);

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
    }

    printf("쓰레드 끝 메인 시작!! \n");
    for (int i = 0; i < 3; i++)
    {
        sleep(1);
        puts("running main()");
    }
    free(thr_ret);
    return 0;
}

char *thread_main(void *arg)
{
    int start = ((int *)arg)[0];
    int end = ((int *)arg)[1];
    char *msg = (char *)malloc(sizeof(char) * 50);
    strcpy(msg, "Hello, I'am from thread--- \n");
    for (int i = start*1000000; i < end*1000000; i++)
    {
        num += 1;
        printf("running thread_main(), %d \n", i);
    }
    return msg;
}