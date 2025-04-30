#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

#define BUF_SIZE 30
void error_handling(char *message);

int main(int argc, char *argv[])
{
    int sock;
    FILE *fp;
    char buf[BUF_SIZE];

    struct sockaddr_in serv_addr;
    int read_cnt;
    int str_len, recv_len, recv_cnt;

    if (argc != 3)
    {
        printf("사용법: %s <IP> <port>\n", argv[0]);
        exit(1);
    }

    fp = fopen("/home/lws/kulws2025/kubig2025/network/tcp/receive.txt", "wb"); // ! 자신의 경로 확인!!

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

    while ((read_cnt = read(sock, buf, BUF_SIZE)) != 0)
        fwrite((void *)buf, 1, read_cnt, fp);

    puts("Received file data\n");
    write(sock, "Thank you!!", 12);

    fclose(fp);
    close(sock);

    return 0;
}
void error_handling(char *message)
{
    fputs(message, stderr);
    fputc('\n', stderr);
    exit(1);
}