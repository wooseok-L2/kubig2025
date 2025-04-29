#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

void print_addr(unsigned long conv_addr);

int main()
{
    const char *addr1 = "127.212.124.78";      // transfer to big endian
    const char *addr2 = "127.212.124.256";     //Error would be occured!

    struct sockaddr_in addr_inet, addr_inet2;

    unsigned long conv_addr = inet_addr(addr1);
    print_addr(conv_addr);

    conv_addr = inet_addr(addr2);
    print_addr(conv_addr);

    int ret = inet_pton(AF_INET, addr1, &addr_inet.sin_addr);   //inet_iton deleted

    if (ret)
    {
        printf("network integer addr : %#x \n", addr_inet.sin_addr.s_addr);
        // printf("sockaddr's s_data : %#x \n", ((struct sockaddr *)&addr_inet)->sa_data);
    }

    char buffer[20];
    char *buffer_ptr;
    // buffer_ptr = inet_ntoa(addr_inet.sin_addr);
    // strcpy(buffer, buffer_ptr);
    // printf("nework type (111.111.111.111)'s string : %s \n", buffer);
    printf("nework type (111.111.111.111)'s string : %s \n", inet_ntoa(addr_inet.sin_addr));


    addr_inet2.sin_addr.s_addr = htonl(0x10203040);

    buffer_ptr = inet_ntoa(addr_inet2.sin_addr);
    strcpy(buffer, buffer_ptr);
    printf("nework type (111.111.111.111)'s string : %s \n", buffer);

    return 0;
}

void print_addr(unsigned long conv_addr){
    
    if (conv_addr == INADDR_NONE)
        printf("Error occured! \n");
    else 
        printf("network int addr : %#lx \n", conv_addr);
}