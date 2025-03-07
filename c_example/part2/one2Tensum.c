#include <stdio.h>

int main(void){
    int sum = 0;

    for (int i = 100; i < 10001; ++i){
        sum += i;
    }

    printf("100 to 10000 of sum : %d \n", sum);

    return 0;
}