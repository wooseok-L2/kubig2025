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
    // 공유 메모리 생성
    int shm_fd = shm_open(SHM_NAME, O_CREAT | O_RDWR, 0666);
    if (shm_fd == -1)
    {
        perror("shm_open");
        exit(1);
    }
    ftruncate(shm_fd, SHM_SIZE);

    // 메모리 매핑
    char *shm = mmap(NULL, SHM_SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, shm_fd, 0);
    if (shm == MAP_FAILED)
    {
        perror("mmap");
        exit(1);
    }
    strcpy(shm, "Hello shared memory FROM process 1!");
    char temp[10];
    scanf("%s", temp);
    munmap(shm, 4096);
    shm_unlink("/myshm");


    // // 세마포어 생성
    // sem_t *sem = sem_open(SEM_NAME, O_CREAT, 0666, 1);
    // if (sem == SEM_FAILED)
    // {
    //     perror("sem_open");
    //     exit(1);
    // }

    // // 공유 메모리에 데이터 쓰기
    // sem_wait(sem);
    // strcpy(shm, "Hello from Server!");
    // printf("Server wrote: %s\n", shm);
    // sem_post(sem);

    // // 클라이언트가 읽을 때까지 대기
    // printf("Waiting for client to read data...\n");

    // // 초기 값을 저장해서 변경 여부를 확인할 수 있게 함
    // char initial_content[SHM_SIZE];
    // strcpy(initial_content, shm);

    // // 클라이언트가 데이터를 읽고 수정할 때까지 대기
    // int timeout = 30; // 30초 타임아웃
    // while (strcmp(shm, initial_content) == 0 && timeout > 0)
    // {
    //     sleep(1);
    //     timeout--;
    // }

    // if (timeout > 0)
    // {
    //     printf("Client read the data and modified it\n");
    // }
    // else
    // {
    //     printf("Timeout waiting for client\n");
    // }

    // printf("Server is shutting down...\n");

    // 정리
    //munmap(shm, SHM_SIZE);
    //close(shm_fd);
    // shm_unlink(SHM_NAME);
    // sem_close(sem);
    // sem_unlink(SEM_NAME);

    return 0;
}