#include <stdio.h>

int sumArray(const int *pArr, int size)
{
    int sum = 0;
    for (int i = 0; i < size; i++)
    {
        sum += pArr[i];
    }

    return sum;
}

int sumArray2(int arr[])         //int arr[]  => int *arr
{
    int sum = 0;
    //for (int i = 0; i < 10; i++)
    for (int i = 0; i < sizeof(arr) / sizeof(arr[0]); i++)
    {
        sum += *arr++;
    }

    return sum;
}

int main(void)
{
    int nums[] = {1,2,3,4,5,6,7,8,9,10};

    int sum1 = sumArray(nums, 10);
    printf("sum1 : %d \n", sum1);
    int sum2 = sumArray(nums + 5, 5);
    printf("sum2 : %d \n", sum2);

    int sum3 = sumArray2(nums);
    printf("sum2 : %d \n", sum3);

    return 0;
}