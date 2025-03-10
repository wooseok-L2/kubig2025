#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int compare(const void *a, const void* b){

    return (*(int*)a - *(int*)b);
}

int main(void){

    int count;
    int nums[20] = {0};
    srand(time(NULL));

    for (int i = 0; i < 20; i++){
        nums[i] = rand() % 101;
    }

    for (int i = 0; i < 20; i++){
        printf("%d, ", nums[i]);
        count++;

        if (count == 10){
            printf("\n");
            count = 0;
        }
    }

    printf("After Q Sorting : \n");

    qsort(nums, 20, sizeof(nums[0]), compare);

    for (int i = 20 - 1; i >= 1; --i){
        for (int j = 0; j < i; j++){
            if (nums[j]>nums[j+1]){
                int temp = nums[j];
                nums[j] = nums[j+1];
                nums[j+1] = temp;
            }
        }
    }

    for (int i = 0; i < 20; i++){
        printf("%d, ", nums[i]);
        count++;

        if (count == 10){
            printf("\n");
            count = 0;
        }
    }
    

    return 0;
}