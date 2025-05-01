// ./hello_server
// ./hello_client 127.0.0.1 8888

#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>
#include <signal.h>
#include <wait.h>

void error_handling(char *message);
void read_childproc(int sig);

#define BUF_SIZE 30

int main(int argc, char *argv[])
{
    int serv_sock;
    int clnt_sock;
    int str_len;
    char buf[BUF_SIZE];
    pid_t pid;
    int i;

    struct sockaddr_in serv_addr;
    struct sockaddr_in clnt_addr;
    socklen_t clnt_addr_size;

    struct sigaction act;
    act.sa_handler = read_childproc;
    sigemptyset(&act.sa_mask);
    act.sa_flags = 0;
    sigaction(SIGCHLD, &act, 0);

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
    while(1)
    {
        clnt_addr_size = sizeof(clnt_addr);
        clnt_sock = accept(serv_sock, (struct sockaddr *)&clnt_addr, &clnt_addr_size);
        if (clnt_sock == -1)
            error_handling("accept() 에러!!");
        else
            printf("Conneted client %d : %s \n", i + 1, inet_ntoa(clnt_addr.sin_addr));

        pid = fork();
        if (pid == -1)
        {
            close(clnt_sock);
            continue;
        }
        if (pid == 0)
        {
            close(serv_sock);
            while((str_len = read(clnt_sock, buf, sizeof(buf)-1)) != 0)
            {
                buf[str_len] = '\0';
                printf("%s : ", inet_ntoa(clnt_addr.sin_addr));
                puts(buf);
                write(clnt_sock, buf, str_len);
                //memset(&buf, 0, sizeof(buf));
            }
            close(clnt_sock);
            
            printf("client connect off.. %s \n", inet_ntoa(clnt_addr.sin_addr));
            
            return 0;
        }
        else
        {
            printf("자식 프로세스 ID: %d \n", pid);
            close(clnt_sock);
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

void read_childproc(int sig)
{
    int status;
    pid_t id = waitpid(-1, &status, WNOHANG);
    if (WIFEXITED(status))
    {
        printf("프로세스 제거 id: %d \n", id);
        printf("자식이 보낸 번호: %d \n", WEXITSTATUS(status));
    }
}