#include <stdio.h>

int main(void){

    double temp[12] = {0};

    for (int i = 0; i < 12; i++){
        scanf("%lf", &temp[i]);
    }
    
    double sum = 0.0;

    for (int i = 0; i < 12; i++){
        sum += temp[i];
    }

    double average = 0.0;
    average = sum / 12.0;

    printf("2022's Average Temp is %.2lf \n", average);

    return 0;
}