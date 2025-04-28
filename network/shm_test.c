#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <stdlib.h>
#include <string.h>


int main()
{
    int shm_fd = shm_open("/myshm", O_CREAT | O_RDWR, 0666);
    if(shm_fd == -1)
    {
        perror("shm_open");
        exit(1);
    }

    ftruncate(shm_fd, 4096);
    char *shm = mmap(0, 4096, PROT_WRITE | PROT_READ, MAP_SHARED, shm_fd, 0);

    // 프로세스 1: 데이터 쓰기
    strcpy(shm, "Hello shared memory from Process 1!");

    char temp[10];
    scanf("%s", temp);

    // 프로세스 2: 데이터 읽기 (별도 프로세스에서 동일한 /myshm 열기)
    printf("Read: %s\n", shm);

    munmap(shm, 4096);
    shm_unlink("/myshm");

    return 0; 
}