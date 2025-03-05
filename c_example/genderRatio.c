#include <stdio.h>

int main(void){

    int man, woman;
    double sum, manRate, womanRate;
    
    printf("man count : ");
    scanf("%d", &man);
    printf("woman count : ");
    scanf("%d", &woman);

    sum = man + woman;
    manRate = man/sum*100;
    womanRate = woman/sum*100;

    printf("man count %d, woman count %d \n", man, woman);
    printf("total count %.f \nmanRate %.2f%% \nwomanRate %.2f%% \n", sum, manRate, womanRate);

    return 0;
}