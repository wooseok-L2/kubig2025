#include <stdio.h>

// int main(void){

//     int a, b;
//     int greater;

//     printf("Enter two integer : ");
//     scanf("%d %d", &a, &b);

//     greater = a > b;
//     printf("greater's value : %d \n", greater);

//     return 0;


// }

int main(void){

    int a;

    printf("Enter number(1~9) : ");
    scanf("%d", &a);

    printf("1 <= %d <= 9 : %d \n", a, 1<=a && a<=9);

    return 0;
}