#include <stdio.h>

int add (int a, int b){
    return a+b;
}

int substract(int a, int b){
    return a-b;
}

int main(void){
    int x = 9;
    int y = 6;

    printf("add(x, y): %d \n", add(x, y));
    printf("substrack(x, y) : %d \n", substract(x, y));

    int (*fp)(int, int);  // function pointer
    fp = &add;
    fp = add;
    printf("add(x, y) : %d \n", (*fp)(x, y));

    fp = &substract;
    printf("substract(x, y) : %d \n", fp(x, y));

    return 0;
}