// This prgram is practice for C
#include <stdio.h>

int main(){
    int celsius;
    //celsius = 15;
    printf("input celsius temp : ");
    scanf("%d", &celsius);  
    printf("celsius temp : %d \n", celsius);

    double fahr;
    fahr = celsius*9/5 + 32;
           // 9/5 celsius + 32 --> if int devide, result would be int not float 
           //                   => it can be out non-correct result
    printf("fahr temp : %f \n", fahr);

    return 0;
}