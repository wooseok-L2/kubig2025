#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

int main()
{   
    int serv_sock;
    int clnt_sock;
    unsigned short host_port = 0x1234;
    unsigned short net_port;
    unsigned long host_addr = 0x12345678;
    unsigned long net_addr;

    net_port = htons(host_port);
    net_addr = htonl(host_addr);

    printf("host's port is : %#x \n", host_port);
    printf("network's port is : %#x \n", net_port);
    printf("host's addr is : %#lx \n", host_addr);
    printf("network's addr is : %#lx \n", net_addr);
    

    return 0;
}