#include <fcntl.h>
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/mman.h>
#include <unistd.h>

#define SHM_NAME "/myshm"
#define SEM_NAME "/mysem"
#define SHM_SIZE 128

int main()
{
    // 공유 메모리 열기
    int shm_fd = shm_open(SHM_NAME, O_RDWR, 0666);
    if (shm_fd == -1)
    {
        perror("shm_open");
        exit(1);
    }

    // 메모리 매핑
    char *shm = mmap(NULL, SHM_SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, shm_fd, 0);
    if (shm == MAP_FAILED)
    {
        perror("mmap");
        exit(1);
    }

    printf("Client read: %s\n", shm);

    munmap(shm, 4096);


    // // 세마포어 열기
    // sem_t *sem = sem_open(SEM_NAME, 0);
    // if (sem == SEM_FAILED)
    // {
    //     perror("sem_open");
    //     exit(1);
    // }

    // // 공유 메모리에서 데이터 읽기
    // sem_wait(sem);
    // printf("Client read: %s\n", shm);
    // memset(shm, 0, SHM_SIZE); // 0으로 채워서 초기화
    // sem_post(sem);

    // // 정리
    // munmap(shm, SHM_SIZE);
    //close(shm_fd);
    //sem_close(sem);

    return 0;
}