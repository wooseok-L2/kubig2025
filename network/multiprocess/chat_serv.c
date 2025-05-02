#include <arpa/inet.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

#define BUF_SIZE 100
#define MAX_CLIENT 20

typedef struct
{
    int sockfd;
    struct sockaddr_in addr;
    int clnt_socks_index;
} ClientInfo;

void error_handling(char *message);
void handle_clnt(void *arg);
// void send_msg(char *msg, int len);

int clnt_cnt = 0;
int clnt_socks[MAX_CLIENT];
pthread_mutex_t mtx;
ClientInfo clients[MAX_CLIENT] = {0};

int main(int argc, char *argv[])
{
    int serv_sock, clnt_sock;

    struct sockaddr_in serv_addr, clnt_addr;
    socklen_t clnt_addr_size;
    pthread_t t_id;

    if (argc != 2)
    {
        printf("사용법: %s <port>\n", argv[0]);
        exit(1);
    }

    pthread_mutex_init(&mtx, NULL);
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

    while (1)
    {
        clnt_addr_size = sizeof(clnt_addr);
        clnt_sock = accept(serv_sock, (struct sockaddr *)&clnt_addr, &clnt_addr_size);

        pthread_mutex_lock(&mtx);
        clients[clnt_cnt].sockfd = clnt_sock;
        clients[clnt_cnt].addr = clnt_addr;
        clients[clnt_cnt].clnt_socks_index = clnt_cnt;
        // thread를 통해서 클라이언트 함수!!
        clnt_socks[clnt_cnt++] = clnt_sock;
        pthread_mutex_unlock(&mtx);

        pthread_create(&t_id, NULL, (void *)handle_clnt, (void *)&clnt_sock);
        pthread_detach(t_id);
        printf("%d 번째 클라이언트 IP : %s \n", clnt_cnt, inet_ntoa(clnt_addr.sin_addr));
    }
    close(serv_sock);
    return 0;
}

void handle_clnt(void *arg)
{
    // 쓰레드의 연결대상 == 클라이언트
    int str_len;
    char buf[BUF_SIZE];
    int fd = *(int *)arg;

    while (str_len = read(fd, buf, BUF_SIZE))
    {
        buf[str_len] = '\0'; // 널 문자 추가
        puts(buf);
        pthread_mutex_lock(&mtx);
        for (int i = 0; i < clnt_cnt; ++i)
            write(clnt_socks[i], buf, str_len);
        pthread_mutex_unlock(&mtx);
        // if (clnt_socks[i] != fd)
    }

    // clnt_cocks 안에 있는 fd 위치 확인!
    int cl_index;
    pthread_mutex_lock(&mtx);
    for (int i = 0; i < clnt_cnt; ++i)
        if (clnt_socks[i] == fd)
            cl_index = i;
    // 맨 끝의 fd 를 지워지는 위치로 이동
    // cnt 감소 및 fd 제거
    printf("fd가 %d 인 %s client 연결 종료...\n", fd, inet_ntoa(clients[cl_index].addr.sin_addr));

    clnt_socks[cl_index] = clnt_socks[--clnt_cnt];
    clients[clnt_cnt].clnt_socks_index = cl_index;
    pthread_mutex_unlock(&mtx);
    close(fd);
}

void error_handling(char *message)
{
    fputs(message, stderr);
    fputc('\n', stderr);
    exit(1);
}