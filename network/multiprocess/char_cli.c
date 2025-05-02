#include <arpa/inet.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

#define BUF_SIZE 1024
#define NAME_SIZE 20

void send_msg(void *arg);
void recv_msg(void *arg);
void error_handling(char *message);

char name[NAME_SIZE] = "[DEFAULT]";
char msg[BUF_SIZE];

int main(int argc, char *argv[])
{
    int sock;

    struct sockaddr_in serv_addr;
    pthread_t snd_thread, rcv_thread;
    void *thread_return;

    if (argc != 4)
    {
        printf("사용법: %s <IP> <port> <name>\n", argv[0]);
        exit(1);
    }
    sprintf(name, "[%s]", argv[3]);

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

    pthread_create(&snd_thread, NULL, (void *)send_msg, (void *)&sock);
    pthread_create(&rcv_thread, NULL, (void *)recv_msg, (void *)&sock);
    pthread_join(snd_thread, &thread_return);
    // pthread_join(rcv_thread, &thread_return); // recv_msg() 가 끝나지 않는다.

    close(sock);

    return 0;
}

void send_msg(void *arg)
{
    int fd = *((int *)arg);
    char name_msg[NAME_SIZE + BUF_SIZE];
    fputs("메세지를 넣으세요(Q 나가기): ", stdout);
    while (1)
    {
        fgets(msg, BUF_SIZE, stdin);
        if (!strcmp(msg, "q\n") || !strcmp(msg, "Q\n"))
            break;
        msg[strlen(msg) - 1] = '\0';           // 리턴 문자 제거
        sprintf(name_msg, "%s %s", name, msg); // 네임 변수 합침
        write(fd, name_msg, strlen(name_msg));
    }
    printf("end of sendmsg()\n");
}
void recv_msg(void *arg)
{
    int fd = *((int *)arg);
    char name_msg[NAME_SIZE + BUF_SIZE];
    int str_len;
    while (1)
    {
        str_len = read(fd, name_msg, NAME_SIZE + BUF_SIZE - 1);
        if (str_len == -1)
        {
            fputs("read() 에러!!!", stderr);
            break;
        }
        name_msg[str_len] = '\0';
        printf("%s\n", name_msg);
    }
    printf("end of recv_msg\n");
}

void error_handling(char *message)
{
    fputs(message, stderr);
    fputc('\n', stderr);
    exit(1);
}