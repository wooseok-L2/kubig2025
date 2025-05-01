// 1. server 프로그램 실행
// 2. cat /tmp/pipe1
// 3. echo 'data from cli' >> /tmp/pipe2
#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/epoll.h>
#include <sys/stat.h>
#include <unistd.h>

#define BUFFER_SIZE 256
#define NUM_PIPES 30
#define PIPE_PREFIX "/tmp/pipe"
#define BUF_SIZE 128
#define MAX_EVENT 10
typedef struct
{
    char path[32];
    int fd;
} Pipe;

void create_pipe(const char *path)
{
    unlink(path);
    if (mkfifo(path, 0666) == -1 && errno != EEXIST)
    {
        perror("mkfifo");
        exit(EXIT_FAILURE);
    }
}

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

void read_pipe(int fd, const char *path, char *buffer, size_t buf_size)
{
    ssize_t read_cnt = read(fd, buffer, buf_size - 1);
    if (read_cnt > 0)
    {
        buffer[read_cnt] = '\0';
        printf("파이프%d 에서 읽은 메세지: %s", fd, buffer);
    }
    else if (read_cnt == -1 && errno != EAGAIN && errno != EWOULDBLOCK)
        perror("read pipe1");
}

void reopen_pipe(Pipe *pipe, int epfd)
{
    close(pipe->fd);
    pipe->fd = open_pipe(pipe->path);
}

int main()
{
    Pipe pipes[NUM_PIPES];     //파이프 객체 배열 생성
    char buffer[BUFFER_SIZE];
    int epfd;
    struct epoll_event event, events[NUM_PIPES];    //epoll event 객체, 객체 배열 생성

    epfd = epoll_create1(0);           // epoll 인스턴스 생성
    if (epfd == -1)
    {
        perror("eoll_create 에러1!!");
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < NUM_PIPES; ++i)
    {
        snprintf(pipes[i].path, sizeof(pipes[i].path), "%s%d", PIPE_PREFIX, i + 1);   //파이프 경로 배열에 경로 저장       
        create_pipe(pipes[i].path);     //파이프 생성
    }

    for (int i = 0; i < NUM_PIPES; ++i)
    {
        pipes[i].fd = open_pipe(pipes[i].path);      // 파이프 열기
        event.events = EPOLLIN;                      // epoll event 객체 이벤트 설정
        event.data.ptr = &pipes[i];                  // 파이프 파일디스크립터 저장
        if (epoll_ctl(epfd, EPOLL_CTL_ADD, pipes[i].fd, &event) == -1)     //epoll 파일 디스크립터에 관리할 파이프 파일디스크립터 저장
        {
            perror("epoll 에러!!!");
            exit(EXIT_FAILURE);
        }
    }

    printf("메세지 수신 대기 \n");
    while (1)
    {
        int nfds = epoll_wait(epfd, events, MAX_EVENT, 10000); // 멀티플렉싱을 위한 대기!!  epoll 인스턴스에서 이벤트가 발생할때까지 대기
        if (nfds == -1)
        {
            puts("epoll wait 에러!!");
            break;
        }
        else if (nfds == 0)
        {
            puts("Time out !!");
            break;
        }
        else
        {
            for (int i = 0; i < nfds; ++i)
            {
                Pipe *pipe = (Pipe *)events[i].data.ptr;
                if (events[i].events & EPOLLIN)
                {
                    read_pipe(pipe->fd, pipe->path, buffer, BUFFER_SIZE);
                }
                if (events[i].events & EPOLLERR)
                {
                    fprintf(stderr, "%s에서 오류 \n", pipe->path);
                }
                // if (events[i].events & EPOLLHUP)
                // {
                //     fprintf(stderr, "%s에서 연결 종료 \n", pipe->path);
                //     reopen_pipe(pipe, epfd);
                // }
            }
        }
    }
    for (int i = 0; i < NUM_PIPES; ++i)
    {
        close(pipes[i].fd);
        unlink(pipes[i].path);
    }

    return 0;
}