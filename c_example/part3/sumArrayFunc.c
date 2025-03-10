#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int sumArray(int pArray[], int size);

int main(void){

    int nums[20] = {0};
    int size = sizeof(nums)/sizeof(nums[0]);

    srand(time(NULL));
    
    int cnt = 0;
    for (int i = 0; i < 20; i++){
        nums[i] = rand() % 101;

        printf("%d, ", nums[i]);
        cnt++;

        if (cnt % 10 == 0){
            printf("\n");
        }
    }

    int sum = sumArray(nums, size);

    printf("sum : %d \n", sum);

    int *p;

    printf("%ld \n", sizeof(p));

    return 0;
}

int sumArray(int pArray[], int size){

    int sum = 0;
    for (int i = 0; i < size; i++){
        sum += pArray[i];
    }


    return sum;
}