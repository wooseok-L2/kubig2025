//  cc -o led_driver_native led_driver_native.c
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(void)
{
    int fd;
    char buf[4] = {0};
    fd = open("/dev/led_driver", O_RDWR);
    if (fd < 0)
    {
        printf("driver open fail\n");
        return -1;
    }
    for (int i = 0; i < 4; ++i)
    {
        buf[i] = 1;
        write(fd, &buf, 4);
        sleep(1);
    }
    close(fd);
    return 0;
}