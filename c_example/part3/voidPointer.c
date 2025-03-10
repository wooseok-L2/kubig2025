#include <stdio.h>

int main(void){
    int i = 100;
    double d = 3.131529;

    void *p;

    p = (&i);
    printf("address of p : %p \n", p);
    printf("value of p : %d \n", *(int *)p);

    p = &d;
    printf("address of p : %p \n", p);
    printf("value of p is : %lf \n", *(double *)p);

    return 0;
}