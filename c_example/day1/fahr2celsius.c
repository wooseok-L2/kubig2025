#include <stdio.h>

int main(){
    float fahr = 98.0;
    float celsius = fahr*5.0/9.0 - 32.0;

    printf("fahr temp : %.1f \n", fahr);
    printf("celsius temp : %.1f \n", celsius);

    return 0;
}   