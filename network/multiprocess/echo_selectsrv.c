// ./echo_selectsrv 1234
// ./echo_selectcli 127.0.0.1 1234

#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/select.h>
#include <sys/socket.h>
#include <sys/time.h>
#include <unistd.h>
typedef struct
{
    int sockfd;
    struct sockaddr_in addr;
} ClientInfo;

#define BUF_SIZE 100
#define MAX_CLIENTS 20
void error_handling(char *message);

int main(int argc, char *argv[])
{
    int serv_sock, clnt_sock;
    int str_len, fd_max, fd_num;
    char buf[BUF_SIZE];
    fd_set reads, cpy_reads;

    struct sockaddr_in serv_addr, clnt_addr;
    struct timeval timeout;
    socklen_t clnt_addr_size;

    ClientInfo clients[MAX_CLIENTS] = {0};
    int client_count = 0;
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

    FD_ZERO(&reads);
    FD_SET(serv_sock, &reads);
    fd_max = serv_sock;

    while (1)
    {
        cpy_reads = reads;
        timeout.tv_sec = 5;
        timeout.tv_usec = 0;

        if ((fd_num = select(fd_max + 1, &cpy_reads, 0, 0, &timeout)) == -1)
            break;
        if (fd_num == 0)
            continue;

        for (int i = 0; i < fd_max + 1; i++)
        {
            if (FD_ISSET(i, &cpy_reads))
            {
                if (i == serv_sock) // 새로만들어진 클라이언트 인지 확인
                {
                    clnt_addr_size = sizeof(clnt_addr);
                    clnt_sock = accept(serv_sock, (struct sockaddr *)&clnt_addr, &clnt_addr_size);
                    // accept!! 대기
                    if (clnt_sock == -1)
                        continue;
                    else
                    {
                        FD_SET(clnt_sock, &reads);
                        if (fd_max < clnt_sock)
                            fd_max = clnt_sock;
                        if (client_count < MAX_CLIENTS)
                        {
                            clients[client_count].sockfd = clnt_sock;
                            clients[client_count].addr = clnt_addr;
                            client_count++;
                        }
                        printf("%d 번째 클라이언트 IP : %s \n", client_count, inet_ntoa(clnt_addr.sin_addr));
                    }
                }
                else // 이미 만들어진 클라이언트
                {
                    str_len = read(i, buf, BUF_SIZE);
                    if (str_len == 0)
                    {
                        FD_CLR(i, &reads);
                        close(i);
                        for (int j = 0; j < client_count; ++j)
                        {
                            if (clients[j].sockfd == i)
                            {
                                printf("client 연결 종료... %s \n", inet_ntoa(clients[j].addr.sin_addr));
                                clients[j] = clients[client_count - 1];
                                // 빠진 클라언트 배열의 자리에 맨끝 클라이언트를 이동.
                                client_count--;
                                break;
                            }
                        }
                    }
                    else
                    {
                        buf[str_len] = '\0'; // 널 문자 추가
                        for (int j = 0; j < client_count; ++j)
                        {
                            if (clients[j].sockfd == i)
                            {
                                printf("%s : ", inet_ntoa(clients[j].addr.sin_addr));
                                puts(buf);
                                write(i, buf, str_len);
                            }
                        }
                    }
                }
            }
        }
    }

    close(serv_sock);

    return 0;
}

void error_handling(char *message)
{
    fputs(message, stderr);
    fputc('\n', stderr);
    exit(1);
}