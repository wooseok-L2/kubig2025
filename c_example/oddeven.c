#include <stdio.h>

int main(void){

    int num;
    printf("Enter number : ");
    scanf("%d", &num);

    int isOdd;
    // isOdd = (num % 2 == 1);
    isOdd = num % 2;
    printf("num : %d \t isOdd : %d\n", num, isOdd);

    return 0;
}