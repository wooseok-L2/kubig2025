#include <stdio.h>

int sum(int a, int b);

int main(void){
    int a = 10, b = 20;
    int res;

    res = sum(a, b);
    printf("%d + %d = %d \n", a, b, res);

    return 0;
}

int sum(int a, int b){
    int temp;
    temp = a + b;

    return temp;
}


