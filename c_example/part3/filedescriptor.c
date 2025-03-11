#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

int main(void){
    int fd;
    fd = open("test2.dat", O_WRONLY | O_CREAT | O_TRUNC, 0644);

    if (fd == -1){
        printf("can't open file \n");
    }
    write(fd, "it is example data as file to save \n", 35);
    close(fd);
    return 0;
}