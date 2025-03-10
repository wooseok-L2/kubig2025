#include <stdio.h>
#include <stdlib.h>
#include <time.h>

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

        if (count == 5){
            printf("\n");
            count = 0;
        }
    }


    // sorting

    for (int i = 0; i < 19; i++){
        for (int j = i+1; j < 20; j++){
            if (nums[i] > nums[j]){
                int temp = nums[i];
                nums[i] = nums[j];
                nums[j] = temp;
            }
        }
    }

    for (int i = 0; i < 20; i++ ){
        printf("%d, ", nums[i]);
        count++;
       
        if (count == 5){
            printf("\n");
            count = 0;
        }
    }


    return 0;
}