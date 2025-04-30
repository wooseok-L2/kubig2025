#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>
#include <netdb.h>

void error_handling(char *message);

int main(int argc, char* argv[])
{
    int i;
    struct hostent *host;
    struct sockaddr_in addr;

    if (argc != 2){
        printf("usage : %s <addr> \n", argv[0]);
        exit(0);
    }

    memset(&addr, 0, sizeof(addr));
    addr.sin_addr.s_addr = inet_addr(argv[1]);

    host = gethostbyaddr((void *)&addr.sin_addr, 4, AF_INET);
    if (!host)
        error_handling("gethost.... error");

    printf("name : %s \n", host->h_name);

    for(i = 0; host->h_aliases[i]; i++)
        printf("Aliases %d : %s \n", i + 1, host->h_aliases[i]);

    printf("address type: %d \n", host->h_addrtype);

    for (i = 0; host->h_addr_list[i]; i++)
        printf("address %d : %s \n", i + 1, inet_ntoa(*(struct in_addr *)host->h_addr_list[i]));

    return 0;
}

void error_handling(char *message)
{
    fputs(message, stderr);
    fputc('\n', stderr);
    exit(1);
}