#include <fcntl.h>
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/mman.h>
#include <unistd.h>
#include <wait.h>

#define SHM_NAME "/myshm"
#define SEM_NAME "/mysem"
#define SHM_SIZE 128

int main()
{
    // 공유 메모리 생성
    int shm_fd = shm_open(SHM_NAME, O_CREAT | O_RDWR, 0666);
    ftruncate(shm_fd, SHM_SIZE);

    // 메모리 매핑
    char *shm = mmap(NULL, SHM_SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, shm_fd, 0);

    // 세마포어 생성
    sem_t *sem = sem_open(SEM_NAME, O_CREAT, 0666, 1);

    pid_t pid = fork();
    if (pid < 0)
    {
        perror("fork");
        exit(1);
    }

    if (pid == 0)
    {                  // 자식 프로세스
        sem_wait(sem); // 세마포어 획득
        printf("Child read: %s\n", shm);
        sem_post(sem); // 세마포어 반환

        // 정리
        munmap(shm, SHM_SIZE);
        sem_close(sem);
        exit(0);
    }
    else
    {                  // 부모 프로세스
        sem_wait(sem); // 세마포어 획득
        strcpy(shm, "Hello from Parent!");
        printf("Parent wrote: %s\n", shm);
        sem_post(sem); // 세마포어 반환

        // 자식 종료 대기
        wait(NULL);

        // 정리
        munmap(shm, SHM_SIZE);
        close(shm_fd);
        shm_unlink(SHM_NAME);
        sem_close(sem);
        sem_unlink(SEM_NAME);
    }

    return 0;
}