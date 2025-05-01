// 1. server 프로그램 실행
// 2. cat /tmp/pipe1
// 3. echo 'data from cli' >> /tmp/pipe2

// 1. server 프로그램 실행
// 2. client 프로그램 실행

#include <errno.h>
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
#define BUF_SIZE 128

int main()
{
    int fd1, fd2;
    char buffer[BUFFER_SIZE];
    mkfifo(PIPE1, 0666);
    mkfifo(PIPE2, 0666);

    printf("클라이언트 기다림\n");

    fd1 = open(PIPE1, O_RDONLY | O_NONBLOCK);
    if (fd1 == -1)
    {
        perror("open pipe1");
        exit(EXIT_FAILURE);
    }
    fd2 = open(PIPE2, O_RDONLY | O_NONBLOCK);
    if (fd2 == -1)
    {
        perror("open pipe1");
        exit(EXIT_FAILURE);
    }

    // select 설정
    fd_set read_fds;
    struct timeval timeout;
    int max_fd = fd1;
    if (max_fd < fd1)
        max_fd = fd1;
    if (max_fd < fd2)
        max_fd = fd2;
    max_fd++;
    int read_cnt;

    printf("메세지 수신 대기 \n");
    while (1)
    {
        FD_ZERO(&read_fds);
        FD_SET(fd1, &read_fds);
        FD_SET(fd2, &read_fds);
        timeout.tv_sec = 10; // 5초로 세팅 초기화
        timeout.tv_usec = 0;
        int result = select(max_fd, &read_fds, 0, 0, &timeout);
        if (result == -1)
        {
            puts("select 에러!!");
            break;
        }
        else if (result == 0)
        {
            puts("Time out !!");
            break;
        }
        else
        {
            if (FD_ISSET(fd1, &read_fds))
            {
                read_cnt = read(fd1, buffer, BUFFER_SIZE);
                buffer[read_cnt] = '\0';
                if (read_cnt > 0)
                    printf("파이프1에서 읽은 메세지: %s", buffer);
                else if (read_cnt == -1 && errno != EAGAIN && errno != EWOULDBLOCK)
                    perror("read pipe1");
            }
            if (FD_ISSET(fd2, &read_fds))
            {
                read_cnt = read(fd2, buffer, BUFFER_SIZE);
                buffer[read_cnt] = '\0';
                if (read_cnt > 0)
                    printf("파이프2에서 읽은 메세지: %s", buffer);
                else if (read_cnt == -1 && errno != EAGAIN && errno != EWOULDBLOCK)
                    perror("read pipe2");
            }
        }
    }
    close(fd1);
    close(fd2);
    unlink(PIPE1);
    unlink(PIPE2);

    return 0;
}