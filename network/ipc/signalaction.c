#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <sigaction.h>

void timeoutCallback(int sig);

int main()
{
    struct sigaction act;
    act.sa_handler = timeoutCallback;
    sigemptyset(&act.sa_mask);
    act.sa_flags = 0;
    sigaction(SIGALRM, &act, 0);

    for(int i = 0; i < 10; i++)
    {
        puts("wait...");
        sleep(3);
    }

    return 0;
}


void timeoutCallback(int sig)
{
    if(sig == SIGALRM)
        puts("TIME out!");
    alarm(2);
}

