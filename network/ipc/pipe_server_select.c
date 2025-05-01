// 1. server 프로그램 실행
// 2. cat /tmp/pipe1
// 3. echo 'data from cli' >> /tmp/pipe2

// 1. server 프로그램 실행
// 2. client 프로그램 실행

#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/select.h>
#include <sys/stat.h>
#include <unistd.h>

#define BUFFER_SIZE 256
#define PIPE1 "/tmp/pipe1" // 서버 -> 클라이언트
#define PIPE2 "/tmp/pipe2" // 서버 -> 클라이언트
#define PIPE3 "/tmp/pipe3" // 서버 -> 클라이언트
#define PIPE4 "/tmp/pipe4" // 서버 -> 클라이언트
#define PIPE5 "/tmp/pipe5" // 서버 -> 클라이언트
#define BUF_SIZE 128

int main()
{
    int fd1, fd2, fd3, fd4, fd5;
    char buffer[BUFFER_SIZE];
    mkfifo(PIPE1, 0666);
    mkfifo(PIPE2, 0666);
    mkfifo(PIPE3, 0666);
    mkfifo(PIPE4, 0666);
    mkfifo(PIPE5, 0666);

    printf("클라이언트 기다림");

    fd1 = open(PIPE1, O_WRONLY);
    if (fd1 == -1)
    {
        perror("open pipe1");
        exit(EXIT_FAILURE);
    }
    fd2 = open(PIPE1, O_WRONLY);
    if (fd1 == -1)
    {
        perror("open pipe1");
        exit(EXIT_FAILURE);
    }
    fd3 = open(PIPE1, O_WRONLY);
    if (fd1 == -1)
    {
        perror("open pipe1");
        exit(EXIT_FAILURE);
    }
    fd4 = open(PIPE1, O_WRONLY);
    if (fd1 == -1)
    {
        perror("open pipe1");
        exit(EXIT_FAILURE);
    }
    fd5 = open(PIPE1, O_WRONLY);
    if (fd1 == -1)
    {
        perror("open pipe1");
        exit(EXIT_FAILURE);
    }

    // select 설정
    fd_set read_fds;
    struct timeval timeout;
    int max_fd = fd1 + 1;
    printf("메세지 수신 대기 \n");
    while (1)
    {
        FD_ZERO(&read_fds);
        FD_SET(fd1, &read_fds);
        FD_SET(fd2, &read_fds);
        FD_SET(fd3, &read_fds);
        FD_SET(fd4, &read_fds);
        FD_SET(fd5, &read_fds);
        timeout.tv_sec = 5; // 5초로 세팅 초기화
        timeout.tv_usec = 0;
        int result = select(1, &read_fds, 0, 0, &timeout);
        if (result == -1)
        {
            puts("select 에러!!");
            break;
        }
        else if (result == 0)
        {
            puts("Time out !!");
        }
        else
        {
            if (FD_ISSET(fd1, &read_fds))
            {
                read(fd2, buffer, BUFFER_SIZE);
                printf("파이프1에서 읽은 메세지: %s\n", buffer);
            }
            if (FD_ISSET(fd2, &read_fds))
            {
                read(fd2, buffer, BUFFER_SIZE);
                printf("파이프2에서 읽은 메세지: %s\n", buffer);
            }
            if (FD_ISSET(fd3, &read_fds))
            {
                read(fd2, buffer, BUFFER_SIZE);
                printf("파이프3에서 읽은 메세지: %s\n", buffer);
            }
            if (FD_ISSET(fd4, &read_fds))
            {
                read(fd2, buffer, BUFFER_SIZE);
                printf("파이프4에서 읽은 메세지: %s\n", buffer);
            }
            if (FD_ISSET(fd5, &read_fds))
            {
                read(fd2, buffer, BUFFER_SIZE);
                printf("파이프5에서 읽은 메세지: %s\n", buffer);
            }
        }
    }
    close(fd1);
    close(fd2);
    close(fd3);
    close(fd4);
    close(fd5);
    unlink(PIPE1);

    return 0;
}