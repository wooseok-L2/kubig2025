#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

void *thread_main(void *arg);

int main()
{
    pthread_t t_id;
    int thread_param = 5;

    pthread_create(&t_id, NULL, (void *)thread_main, (void *)&thread_param);

    for (int i = 0; i < 10; i++){
        sleep(1);
        puts("running main()");
    }

    return 0;
}

void *thread_main(void *arg)
{
    int cnt = *((int *)arg);
    for (int i = 0; i < cnt; i++){
        sleep(1);
        puts("running thread_main()");
    }
}