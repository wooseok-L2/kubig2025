// ./hello_server
// ./hello_client 127.0.0.1 8888

#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
    int serv_sock;
    int clnt_sock;

    struct sockaddr_in serv_addr;
    struct sockaddr_in clnt_addr;
    socklen_t clnt_addr_size;

    if (argc != 2)
    {
        printf("사용법: %s <port>\n", argv[0]);
        exit(1);
    }

    serv_sock = socket(PF_INET, SOCK_STREAM, 0); // TCP 설정

    memset(&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    serv_addr.sin_port = htons(atoi(argv[1]));

    int option = 1;
    setsockopt(serv_sock, SOL_SOCKET, SO_REUSEADDR, &option, sizeof(option));
    bind(serv_sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr));
    while (1)
    {
        listen(serv_sock, 5); // 대기!!!
        clnt_addr_size = sizeof(clnt_addr);
        clnt_sock = accept(serv_sock, (struct sockaddr *)&clnt_addr, &clnt_addr_size);
        // 연결된 상태의 코드....
        // char message[] = "Hello, TCP IP!!";
        // write(clnt_sock, message, sizeof(message));
        char message[30];
        read(clnt_sock, message, sizeof(message) - 1);
        message[30] = '\0';
        printf("서버 받은 메세지: %s \n", message);
        close(clnt_sock);
    }

    close(serv_sock);

    return 0;
}