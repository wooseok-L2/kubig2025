#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>

#define BUFFER_SIZE 256
#define PIPE1 "/tmp/pipe1" // 서버 -> 클라이언트
#define PIPE2 "/tmp/pipe2" // 클라이언트 -> 서버

int main()
{
    int fd1, fd2;
    char buffer[BUFFER_SIZE];

    // 명명 파이프 생성
    mkfifo(PIPE1, 0666);
    mkfifo(PIPE2, 0666);

    printf("Server: Waiting for client...\n");

    // 클라이언트에게 메시지 보내기
    fd1 = open(PIPE1, O_WRONLY); // pipe1 쓰기 모드
    if (fd1 == -1)
    {
        perror("open pipe1");
        exit(EXIT_FAILURE);
    }
    char *message = "Hello from Server!";
    write(fd1, message, strlen(message) + 1);
    printf("Server: Sent: %s\n", message);
    close(fd1);

    // 클라이언트로부터 메시지 받기
    fd2 = open(PIPE2, O_RDONLY); // pipe2 읽기 모드
    if (fd2 == -1)
    {
        perror("open pipe2");
        exit(EXIT_FAILURE);
    }
    read(fd2, buffer, BUFFER_SIZE);
    printf("Server: Received: %s\n", buffer);
    close(fd2);

    // 파이프 삭제
    unlink(PIPE1);
    unlink(PIPE2);

    return 0;
}