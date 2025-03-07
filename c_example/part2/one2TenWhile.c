#include <stdio.h>
#include <stdbool.h>

int main(void){
    int i = 0;

    do{

        printf("%d print \n", i + 1);
        i++;
    }
    while(i < 10);
    
    return 0;
}