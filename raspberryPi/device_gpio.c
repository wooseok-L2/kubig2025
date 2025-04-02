#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>

#define LED1 23
#define LED2 24
#define LED3 25
#define LED4 1

int main(void){

    // linux blocked access to resiter directly. it means you cannot access resiter directly on user mode

    // gpio pin open
    int fd = open("/sys/class/gpio/export", O_WRONLY);
    write(fd, "23", strlen("23"));
    close(fd);

    // gpio in/out set
    fd = open("/sys/class/gpio/gpio23/direction", O_WRONLY);
    write(fd, "out", strlen("out"));
    close(fd);

    // input the gpio vlaue
    fd = open("/sys/class/gpio/gpio23/value", O_WRONLY);
    for (int i = 0; i <5; i++){

        write(fd, "1", strlen("1"));
        sleep(1);
        write(fd, "0", strlen("0"));
        sleep(1);
    }
    close(fd);

    fd = open("/sys/class/gpio/unexport", O_WRONLY);
    write(fd, "23", strlen("23"));
    close(fd);
    

    return 0;
}