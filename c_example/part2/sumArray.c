#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(void){

    int arr[10];
    int sum = 0;
    srand(time(NULL));

    for ( int i = 0; i < 10; i++){
        arr[i] = rand() % 101;
    }
    printf("\n");
    for (int i = 0; i < 10; i++){
        sum += arr[i];
    }
    printf("\n sum array is %d \n", sum);

    return 0;
}