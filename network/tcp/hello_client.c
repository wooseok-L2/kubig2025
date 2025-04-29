#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
    int serv_sock;

    struct sockaddr_in serv_addr;

    if (argc != 3)
    {
        printf("사용법: %s <IP> <port>\n", argv[0]);
        exit(1);
    }

    serv_sock = socket(PF_INET, SOCK_STREAM, 0); // TCP 설정

    memset(&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = inet_addr(argv[1]);
    serv_addr.sin_port = htons(atoi(argv[2]));

    connect(serv_sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)); // listen 상태의 서버에 접속
    // 연결된 상태의 코드....
    // char message[30];
    // read(serv_sock, message, sizeof(message) - 1);
    // message[30] = '\0';

    // printf("서버에서 받은 메세지: %s \n", message);
    char message[] = "Hello, lws!!";
    write(serv_sock, message, sizeof(message));

    close(serv_sock);

    return 0;
}