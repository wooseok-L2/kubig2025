#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <wait.h>
#include <stdlib.h>


int main()
{
    pid_t pid = fork();
    int status;

    if (pid == 0)
    {
        printf("hi, i am child1 \n");
        return 3;
    }
    else
    {
        pid_t pid = fork();

        if (pid == 0)
        {
            printf("hi, i am child2 \n");
            exit(7);
        }
        else
        {
            printf("child process ID : %d \n", pid);
            wait(&status);
            if(WIFEXITED(status)){
                printf("message child1 sent : %d \n", WEXITSTATUS(status));
            }
            wait(&status);
            if(WIFEXITED(status)){
                printf("message child2 sent : %d \n", WEXITSTATUS(status));
            }

        }
    }

    if(pid == 0)
    {
        puts("end child process \n");
    }
    else
    {
        puts("end parents process \n");
    }


    return 0;
}