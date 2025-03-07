#include <stdio.h>

int main(void){

    double length;
    double height;
    double area;

    printf("Enter triangle's length : ");
    scanf("%lf", &length);
    printf("Enter triangle's height : ");
    scanf("%lf", &height);
    area= length * height / 2;
    printf("triangle 's area is : %.2lf \n", area);

    return 0;
}