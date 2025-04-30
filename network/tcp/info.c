#include <arpa/inet.h>
#include <linux/sockios.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ioctl.h>
#include <sys/socket.h>
#include <unistd.h>

void error_handling(char *message);

#define BUF_SIZE 30

int main(int argc, char *argv[])
{
    printf("INADDR_ANY: %d\n", INADDR_ANY);
    printf("INADDR_LOOPBACK %d\n", INADDR_LOOPBACK);
    printf("AF_INET: %d\n", AF_INET);
    printf("AF_INET6: %d\n", AF_INET6);

    int serv_sock;
    int clnt_sock;
    int str_len;
    FILE *fp;
    char buf[BUF_SIZE];
    int read_cnt;
    int snd_buf, rcv_buf, state;

    struct sockaddr_in serv_addr;
    struct sockaddr_in clnt_addr;
    socklen_t clnt_addr_size;
    socklen_t len;

    if (argc != 2)
    {
        printf("사용법: %s <port>\n", argv[0]);
        exit(1);
    }

    serv_sock = socket(PF_INET, SOCK_STREAM, 0); // TCP 설정
    if (serv_sock == -1)
        error_handling("socker() 만들기 실패");

    state = getsockopt(serv_sock, SOL_SOCKET, SO_SNDBUF, &snd_buf, &len);
    printf("서버소켓의 Snd buffer size: %d\n", snd_buf);

    fp = fopen("/home/lws/kulws2025/kubig2025/network/tcp/file_server.txt", "rb");

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

    clnt_addr_size = sizeof(clnt_addr);
    clnt_sock = accept(serv_sock, (struct sockaddr *)&clnt_addr, &clnt_addr_size);
    if (clnt_sock == -1)
        error_handling("accept() 에러!!");
    else
    {
        printf("Conneted client : %s \n", inet_ntoa(clnt_addr.sin_addr));
        printf("Conneted client port: %d \n", ntohs(clnt_addr.sin_port));
    }

    state = getsockopt(clnt_sock, SOL_SOCKET, SO_SNDBUF, &rcv_buf, &len);
    printf("서버소켓의 Rcv buffer size: %d\n", rcv_buf);

    int outq;
    while (1)
    {
        read_cnt = fread((void *)buf, 1, BUF_SIZE, fp);
        printf("outdata cnt \n");
        if (read_cnt < BUF_SIZE)
        {
            write(clnt_sock, buf, read_cnt);
            break;
        }
        write(clnt_sock, buf, BUF_SIZE);
        ioctl(clnt_sock, SIOCOUTQ, &outq);
        printf("현재 클라이언트 send 큐의 크기: %d bytes\n", outq);
        ioctl(serv_sock, SIOCOUTQ, &outq);
        printf("현재 서버 send 큐의 크기: %d bytes\n", outq);
    }

    // 우아한 종료
    shutdown(clnt_sock, SHUT_WR);
    // shutdown(clnt_sock, SHUT_RD); // recvQ흐름을 방해한다.
    shutdown(serv_sock, SHUT_RD);   // 서버의 recvQ 는 클라이언트 패킷 전달에 상관 없다!
    read(clnt_sock, buf, BUF_SIZE); // sendQ 종료!! recvQ 살아 있음.

    printf("Message from client: %s \n", buf); // sendQ 종료!! recvQ 살아 있음.

    fclose(fp);
    close(clnt_sock);
    close(serv_sock);

    return 0;
}

void error_handling(char *message)
{
    fputs(message, stderr);
    fputc('\n', stderr);
    exit(1);
}