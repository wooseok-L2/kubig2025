//  cc -o driver_exam_native driver_exam_native.c
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(void)
{
    int fd;
    char buf = 1;
    fd = open("/dev/driver_exam", O_RDWR);
    if (fd < 0)
    {
        printf("driver open fail\n");
        return -1;
    }
    write(fd, &buf, 1);
    read(fd, &buf, 1);
    close(fd);
    return 0;
}