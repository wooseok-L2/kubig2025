#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(void){

    int dice[30];
    srand(time(NULL));

    for ( int i = 0; i < 30; i++){
        printf("%ld \n", time(NULL));
        dice[i] = rand() % 6 + 1;
        printf("%d ", dice[i]);
        printf("%p", &dice[i]);
    }
    printf("\n");
    for (int i = 0; i < 30; i++){
        dice[i] *= 10;
        printf("%d ", dice[i]);
        printf("%p", &dice[i]);
    }
    printf("\n");

    return 0;
}