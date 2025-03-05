#include <stdio.h>
#include <stdint.h>

int main(void){

    int num;

    printf("sizeof(char) : %ld \n", sizeof(char));
    printf("sizeof(short) : %ld \n", sizeof(short));
    printf("sizeof(int) : %ld \n", sizeof(int));
    printf("sizeof(long) : %ld \n", sizeof(long));
    printf("sizeof(long long) : %ld \n", sizeof(long long));
    printf("sizeof(float) : %ld \n", sizeof(float));
    printf("sizeof(double) : %ld \n", sizeof(double));
    printf("sizeof(num) : %ld \n", sizeof(num));
    printf("sizeof(3.141592) : %ld \n", sizeof(3.141592));
    printf("sizeof(uint32_t) : %ld \n", sizeof(uint32_t));

    return 0;
}