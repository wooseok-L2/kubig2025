#include <stdio.h>
#include <sys/select.h>
#include <sys/time.h>
#include <unistd.h>

#define BUf_SIZE 30

int main()
{
    fd_set reads, temps;
    int result, str_len;
    char buf[BUf_SIZE];

    struct timeval timeout;

    FD_ZERO(&reads);
    FD_SET(0, &reads); // std input(console)

    while (1)
    {
        temps = reads;
        timeout.tv_sec = 5;
        timeout.tv_usec = 0;
        result = select(1, &temps, 0, 0, &timeout);
        if (result == -1)
        {
            puts("select 에러!!");
            break;
        }
        else if (result == 0)
        {
            puts("Time out !!");
        }
        else
        {
            if (FD_ISSET(0, &temps))
            {
                str_len = read(0, buf, BUf_SIZE);
                buf[str_len] = 0;
                printf("콘솔에서 나온 메세지는 : %s", buf);
            }
        }
    }
    return 0;
}