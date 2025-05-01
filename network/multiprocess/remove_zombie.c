#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <wait.h>

void readChildprocCallback(int sig);

int main()
{
    struct sigaction act;
    act.sa_handler = readChildprocCallback;
    sigemptyset(&act.sa_mask);
    act.sa_flags = 0;
    sigaction(SIGCHLD, &act, 0);

    pid_t pid = fork();
    int status;

    if (pid == 0) // 자식1
    {
        puts("안녕! 나는 자식 프로세스야!!");
        sleep(10);
        return 12;
    }
    else
    {
        printf("자식1 프로세스 ID: %d \n", pid);
        pid = fork();
        if (pid == 0)
        {
            puts("안녕, 나는 두번째 자식 프로세스야!!");
            sleep(2);
            exit(24);
        }
        else
        {
            printf("자식2 프로세스 ID: %d \n", pid);
            for (int i = 0; i < 5; ++i)
            {
                puts("sleep 3초.");
                sleep(3);
            }
        }
    }
    return 0;
}

void readChildprocCallback(int sig)
{
    int status;
    pid_t id = waitpid(-1, &status, WNOHANG);
    if (WIFEXITED(status))
    {
        printf("프로세스 제거 id: %d \n", id);
        printf("자식이 보낸 번호: %d \n", WEXITSTATUS(status));
    }
}