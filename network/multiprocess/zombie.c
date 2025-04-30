#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>


int main()
{
    pid_t pid = fork();

    if (pid == 0)
    {
        printf("hi, i am child \n");
    }
    else
    {
        printf("child process ID : %d \n", pid);
        sleep(30);
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