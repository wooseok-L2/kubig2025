#include <fcntl.h>
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/mman.h>
#include <unistd.h>
#include <wait.h>

#define SHM_NAME "/myshm_protected"
#define SEM_NAME "/mysem_counter"
#define SHM_SIZE 128
#define COUNT 10000000

int main()
{
    // 공유 메모리 생성
    int shm_fd = shm_open(SHM_NAME, O_CREAT | O_RDWR, 0666);
    ftruncate(shm_fd, SHM_SIZE);

    // 메모리 매핑
    int *counter = (int *)mmap(NULL, SHM_SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, shm_fd, 0);

    // 세마포어 생성
    sem_t *sem = sem_open(SEM_NAME, O_CREAT, 0666, 1);

    // 초기화
    *counter = 0;
    printf("초기 카운터 값: %d\n", *counter);

    pid_t pid = fork();
    if (pid < 0)
    {
        perror("fork");
        exit(1);
    }

    if (pid == 0)
    { // 자식 프로세스
        printf("child ");
        for (int i = 0; i < COUNT; i++)
        {
            sem_wait(sem); // 세마포어 획득
            (*counter)++;  // 카운터 증가
            sem_post(sem); // 세마포어 반환
        }

        printf("자식 프로세스 완료. 예상 증가량: %d\n", COUNT);

        // 정리
        munmap(counter, SHM_SIZE);
        sem_close(sem);
        exit(0);
    }
    else
    { // 부모 프로세스
        printf("parents ");
        for (int i = 0; i < COUNT; i++)
        {
            sem_wait(sem); // 세마포어 획득
            (*counter)++;  // 카운터 증가
            sem_post(sem); // 세마포어 반환
        }

        printf("부모 프로세스 완료. 예상 증가량: %d\n", COUNT);

        // 자식 종료 대기
        wait(NULL);

        // 결과 확인
        printf("최종 카운터 값: %d\n", *counter);
        printf("예상 최종 값: %d\n", COUNT * 2);
        printf("손실된 증가 횟수: %d\n", (COUNT * 2) - *counter);

        // 정리
        munmap(counter, SHM_SIZE);
        close(shm_fd);
        shm_unlink(SHM_NAME);
        sem_close(sem);
        sem_unlink(SEM_NAME);
    }

    return 0;
}