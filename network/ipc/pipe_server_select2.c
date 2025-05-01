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
#define NUM_PIPES 5
#define PIPE_PREFIX "/tmp/pipe"
#define BUF_SIZE 128
void create_pipe(const char *path)
{
    unlink(path);
    if (mkfifo(path, 0666) == -1 && errno != EEXIST)
    {
        perror("mkfifo");
        exit(EXIT_FAILURE);
    }
}
typedef struct
{
    char path[32];
    int fd;
} Pipe;

int open_pipe(const char *path)
{
    int fd = open(path, O_RDONLY | O_NONBLOCK);
    if (fd == -1)
    {
        perror("open pipe1");
        exit(EXIT_FAILURE);
    }
    return fd;
}

int main()
{
    Pipe pipes[NUM_PIPES];
    char buffer[BUFFER_SIZE];
    for (int i = 0; i < NUM_PIPES; ++i)
    {
        snprintf(pipes[i].path, sizeof(pipes[i].path), "%s%d", PIPE_PREFIX, i + 1);
        create_pipe(pipes[i].path);
    }

    int max_fd;
    for (int i = 0; i < NUM_PIPES; ++i)
    {
        pipes[i].fd = open_pipe(pipes[i].path);
        if (max_fd < pipes[i].fd)
            max_fd = pipes[i].fd;
    }
    max_fd++;

    // select 설정
    fd_set read_fds;
    struct timeval timeout;
    int read_cnt;

    printf("메세지 수신 대기 \n");
    while (1)
    {
        FD_ZERO(&read_fds);
        for (int i = 0; i < NUM_PIPES; ++i)
        {
            FD_SET(pipes[i].fd, &read_fds);
        }
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
            for (int i = 0; i < NUM_PIPES; ++i)
            {
                if (FD_ISSET(pipes[i].fd, &read_fds))
                {
                    read_cnt = read(pipes[i].fd, buffer, BUFFER_SIZE);
                    buffer[read_cnt] = '\0';
                    if (read_cnt > 0)
                        printf("파이프%d 에서 읽은 메세지: %s", pipes[i].fd, buffer);
                    else if (read_cnt == -1 && errno != EAGAIN && errno != EWOULDBLOCK)
                        perror("read pipe1");
                }
            }

            if (!strcmp(buffer, "q\n") || !strcmp(buffer, "Q\n"))
                break;
        }
    }

    for (int i = 0; i < NUM_PIPES; ++i)
    {
        close(pipes[i].fd);
        unlink(pipes[i].path);
    }

    return 0;
}