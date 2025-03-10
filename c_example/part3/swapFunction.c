#include <stdio.h>


void swap(int *pa, int *pb);


int main(void){

    int a = 100;
    int b = 200;

    printf("a : %d \tb : %d \n", a, b);

    swap(&a, &b);

    printf("a : %d \tb : %d \n", a, b);

    return 0;
}

void swap( int *pa, int *pb){

    int temp = *pa;
    *pa = *pb;
    *pb = temp;
}