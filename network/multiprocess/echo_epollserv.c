#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/epoll.h>
#include <sys/socket.h>
#include <unistd.h>

typedef struct
{
    int sockfd;
    struct sockaddr_in addr;
} ClientInfo;

#define BUF_SIZE 100
#define EPOLL_SIZE 20
void error_handling(char *message);

int main(int argc, char *argv[])
{
    int serv_sock, clnt_sock;
    int str_len;
    char buf[BUF_SIZE];
    fd_set reads, cpy_reads;

    struct sockaddr_in serv_addr, clnt_addr;
    socklen_t clnt_addr_size;

    struct epoll_event *ep_events, event;
    int epfd, event_cnt;

    ClientInfo clients[EPOLL_SIZE] = {0};

    if (argc != 2)
    {
        printf("사용법: %s <port>\n", argv[0]);
        exit(1);
    }

    serv_sock = socket(PF_INET, SOCK_STREAM, 0); // TCP 설정
    if (serv_sock == -1)
        error_handling("socker() 만들기 실패");

    memset(&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = htonl(INADDR_ANY); // localhost 내부 ip.loopback
    serv_addr.sin_port = htons(atoi(argv[1]));

    int option = 1;
    setsockopt(serv_sock, SOL_SOCKET, SO_REUSEADDR, &option, sizeof(option));
    if (bind(serv_sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) == -1)
        error_handling("바인드 에러!!!");
    if (listen(serv_sock, 5) == -1)
        error_handling("리슨 에러"); // 대기!!!

    epfd = epoll_create(EPOLL_SIZE);
    ep_events = malloc(sizeof(struct epoll_event) * EPOLL_SIZE);
    event.data.fd = serv_sock;
    epoll_ctl(epfd, EPOLL_CTL_ADD, serv_sock, &event);

    while (1)
    {
        event_cnt = epoll_wait(epfd, ep_events, EPOLL_SIZE, -1); // 무한 대기
        if (event_cnt == -1)
        {
            puts("epoll_wait 에러!!");
            break;
        }

        for (int i = 0; i < event_cnt; i++)
        {
            if (ep_events[i].data.fd == serv_sock) // 클라이언트 접속시도!!
            {
                clnt_addr_size = sizeof(clnt_addr);
                clnt_sock = accept(serv_sock, (struct sockaddr *)&clnt_addr, &clnt_addr_size);
                // epoll 에 새로운 클라이언트 등록
                event.events = EPOLLIN;
                event.data.fd = clnt_sock;
                epoll_ctl(epfd, EPOLL_CTL_ADD, clnt_sock, &event);
                printf("%ld 번째 클라이언트 IP : %s \n", sizeof(ep_events) / sizeof(ep_events[0]), inet_ntoa(clnt_addr.sin_addr)); // !사이즈체크
            }
            else // 이미 만들어진 클라이언트
            {
                str_len = read(ep_events[i].data.fd, buf, BUF_SIZE);
                if (str_len == 0)
                {
                    epoll_ctl(epfd, EPOLL_CTL_DEL, ep_events[i].data.fd, NULL);
                    close(ep_events[i].data.fd);
                    printf("client 연결 종료... \n");
                }
                else
                {
                    buf[str_len] = '\0'; // 널 문자 추가
                    puts(buf);
                    write(ep_events[i].data.fd, buf, str_len);
                }
            }
        }
    }

    free(ep_events);
    close(serv_sock);

    return 0;
}

void error_handling(char *message)
{
    fputs(message, stderr);
    fputc('\n', stderr);
    exit(1);
}