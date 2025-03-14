#include <stdio.h>

int main(void){
    printf("hello, world!");
    fflush(stdout);
    sleep(1);
    printf("hello, world!");
    fflush(stdout);
    sleep(1);
    printf("hello, world!");
    fflush(stdout);
    sleep(1);

    return 0;
}