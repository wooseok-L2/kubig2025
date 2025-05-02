#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

#define BUF_SIZE 1024
void error_handling(char *message);

int main(int argc, char *argv[])
{
    int sock;

    struct sockaddr_in serv_addr;

    if (argc != 3)
    {
        printf("사용법: %s <IP> <port>\n", argv[0]);
        exit(1);
    }

    sock = socket(PF_INET, SOCK_STREAM, 0); // TCP 설정
    if (sock == -1)
        error_handling("socker() 열기 실패!!");

    memset(&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = inet_addr(argv[1]); // localhost 는 입력 받을 수 없는 코드
    serv_addr.sin_port = htons(atoi(argv[2]));

    if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) == -1)
        error_handling("connet() 연결 실패!!!"); // listen 상태의 서버에 접속
    else
        puts("Connected............");
    char message[BUF_SIZE];
    int str_len, recv_len, recv_cnt;

    while (1)
    {
        fputs("메세지를 넣으세요(Q 나가기): ", stdout);
        fgets(message, BUF_SIZE, stdin);
        if (!strcmp(message, "q\n") || !strcmp(message, "Q\n"))
            break;
        message[strlen(message) - 1] = '\0'; // 리턴 문자 제거
        write(sock, message, strlen(message));

        str_len = read(sock, message, BUF_SIZE - 1);
        if (str_len == -1)
        {
            fputs("read() 에러!!!", stderr);
            break;
        }
        message[str_len] = '\0';
        printf("서버에서 온 메세지: %s\n", message);
    }
    close(sock);

    return 0;
}

void error_handling(char *message)
{
    fputs(message, stderr);
    fputc('\n', stderr);
    exit(1);
}