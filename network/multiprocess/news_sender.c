#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

#define TTL 64
#define BUF_SIZE 30
void error_handling(char *message);

int main(int argc, char *argv[])
{
    int sock;
    char buf[BUF_SIZE];
    int str_len, recv_len, recv_cnt;

    struct sockaddr_in mul_addr, from_addr;
    socklen_t from_addr_size;
    int time_live = TTL;
    FILE *fp;

    if (argc != 3)
    {
        printf("사용법: %s <GroupIP> <port>\n", argv[0]);
        exit(1);
    }

    sock = socket(PF_INET, SOCK_DGRAM, 0); // UDP 설정
    if (sock == -1)
        error_handling("socker() 열기 실패!!");

    memset(&mul_addr, 0, sizeof(mul_addr));
    mul_addr.sin_family = AF_INET;
    mul_addr.sin_addr.s_addr = inet_addr(argv[1]); // localhost 는 입력 받을 수 없는 코드
    mul_addr.sin_port = htons(atoi(argv[2]));

    setsockopt(sock, IPPROTO_IP, IP_MULTICAST_TTL, (void *)&time_live, sizeof(time_live));

    if ((fp = fopen("/home/aa/kuBig2025/network/tcp_udp/file_server.txt", "r")) == NULL)
        error_handling("fopen() error");

    while (!feof(fp))
    {
        fgets(buf, BUF_SIZE, fp);
        sendto(sock, buf, strlen(buf), 0, (struct sockaddr *)&mul_addr, sizeof(mul_addr));
        sleep(2);
    }
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