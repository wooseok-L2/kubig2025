//  cc -o switch_driver_native switch_driver_native.c
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(void)
{
    int fd;
    char buf[4] = {0};
    fd = open("/dev/switch_driver", O_RDONLY);
    if (fd < 0)
    {
        printf("driver open fail\n");
        return -1;
    }
    for (int i = 0; i < 10; ++i)
    {
        read(fd, &buf, 4);
        printf("sw1: %d, sw2: %d, sw3: %d, sw4: %d\n", buf[0], buf[1], buf[2], buf[3]);
        sleep(1);
    }
    close(fd);
    return 0;
}