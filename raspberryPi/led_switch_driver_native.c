//  cc -o led_switch_driver_native led_switch_driver_native.c
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(void)
{
    int fd;
    char swbuf[4] = {0};
    char ledbuf[4] = {0};

    fd = open("/dev/led_switch_driver", O_RDWR);
    if (fd < 0)
    {
        printf("driver open fail\n");
        return -1;
    }

    for (int i = 0; i < 4; ++i)
    {
        ledbuf[i] = 0;
        write(fd, &ledbuf, 4);
        sleep(1);
    }

    while(1)
    {

        read(fd, &swbuf, 4);
        printf("sw1: %d, sw2: %d, sw3: %d, sw4: %d\n", swbuf[0], swbuf[1], swbuf[2], swbuf[3]);
        if (swbuf[0] == 1) ledbuf[0] = 1;
        else ledbuf[0] = 0;
        if (swbuf[1] == 1) ledbuf[1] = 1;
        else ledbuf[1] = 0;
        if (swbuf[2] == 1) ledbuf[2] = 1;
        else ledbuf[2] = 0;
        if (swbuf[3] == 1) ledbuf[3] = 1;
        else ledbuf[3] = 0;
        write(fd, &ledbuf, 4);
        sleep(1);
    }

    close(fd);
    return 0;
}