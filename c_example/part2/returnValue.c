#include <stdio.h>

int f1(void);
void f2(int *pResult);

int main(void){

    int f1_result = f1();
    printf("f1 result is %d \n", f1_result);

    int f2_result;
    f2(&f2_result);
    printf("f2 result is %d \n", f2_result);

    return 0;
}

int f1(void){

    return 100;
}

void f2(int *pResult){

    *pResult = 100;
}