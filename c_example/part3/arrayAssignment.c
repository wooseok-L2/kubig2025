#include <stdio.h>

int main(void){

    int nums1[] = {1, 2, 3, 4, 5};
    int nums2[5];

    for (int i = 0; i < 5; i++){
        nums2[i] = nums1[i];
    }

    for (int i = 0; i < 5; i++){

        printf("nums2 %d : %d, \n", i, nums2[i]);
        
    }

    printf("address of nums1 : %p \n", nums1);
    printf("address of nums2 : %p \n", nums2);

    nums2[3] = 13;

    int *nums3;
    nums3 = nums1;
    printf("address of nums3 : %p \n", nums3);
    nums3[2] = 23;

    for (int i = 0; i < 5; i++){

        printf("nums1 %d : %d, \n", i, nums1[i]);
        printf("nums2 %d : %d, \n", i, nums2[i]);
        
    }

    return 0;
}