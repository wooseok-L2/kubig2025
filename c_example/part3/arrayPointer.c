#include <stdio.h>

int main(void){
    int num[] = {1,2,3,4,5};
    int *p;

    p = num;
    for (int i = 0; i < 5; i++){
        printf("%d st number : %d \n", i, num[i]);
        printf("%d st number : %d \n", i, p[i]);
    }
    return 0;
}