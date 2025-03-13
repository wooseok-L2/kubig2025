#include <stdio.h>

int main(void){

    int length;
    int height;
    int area;

    printf("Enter triangle's length : \n");
    scanf("%d", &length);
    printf("Enter triangle's height : \n");
    scanf("%d", &height);
    area = length * height / 2;
    printf("triangle's area is : %d \n", area);

    return 0;
}