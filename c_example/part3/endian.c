#include <stdio.h>

int main(void){

    int a  = 0x12345678;
    char *pA;
    pA = (char *)&a;

    printf(" *pA : 0x%x \n", *pA);

    return 0;
}