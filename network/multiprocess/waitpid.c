#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <wait.h>

int main()
{
    pid_t pid = fork();
    int status;

    if (pid == 0) // 자식1
    {
        sleep(15);
        return 3;
    }
    else
    {
        printf("자식 프로세스 ID: %d \n", pid);
        while (!waitpid(-1, &status, WNOHANG)) // 논 블럭!!
        {
            sleep(3);
            puts("sleep 3초.");
        }
        if (WIFEXITED(status))
            printf("자식 이 보낸 메세지: %d \n", WEXITSTATUS(status));
        sleep(30);
    }
    return 0;
}