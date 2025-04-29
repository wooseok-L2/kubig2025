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

    printf("Client: Connecting to server...\n");

    // 서버로부터 메시지 받기
    fd1 = open(PIPE1, O_RDONLY); // pipe1 읽기 모드
    if (fd1 == -1)
    {
        perror("open pipe1");
        exit(EXIT_FAILURE);
    }
    read(fd1, buffer, BUFFER_SIZE);
    printf("Client: Received: %s\n", buffer);
    close(fd1);

    // 서버에게 메시지 보내기
    fd2 = open(PIPE2, O_WRONLY); // pipe2 쓰기 모드
    if (fd2 == -1)
    {
        perror("open pipe2");
        exit(EXIT_FAILURE);
    }
    char *response = "Hello from Client!";
    write(fd2, response, strlen(response) + 1);
    printf("Client: Sent: %s\n", response);
    close(fd2);

    return 0;
}