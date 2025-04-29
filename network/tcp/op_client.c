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
    int result, opnd_cnt, i;

    fputs("피 연산자 객수를 넣으세요!: ", stdout);
    scanf("%d", &opnd_cnt);
    message[0] = (char)opnd_cnt;

    for (i = 0; i < opnd_cnt; ++i)
    {
        printf(" %d 번째 피 연산자 를 넣으세요!: ", i + 1);
        scanf("%d", (int *)&message[i * 4 + 1]);
    }
    fgetc(stdin); // 버퍼에 남은것 버리기
    fputs("연산자를 넣으세요! :", stdout);
    scanf("%c", &message[opnd_cnt * 4 + 1]);

    write(sock, message, opnd_cnt * 4 + 2);
    read(sock, &result, 4);

    printf("연산의 결과는: %d \n", result);
    close(sock);

    return 0;
}
void error_handling(char *message)
{
    fputs(message, stderr);
    fputc('\n', stderr);
    exit(1);
}