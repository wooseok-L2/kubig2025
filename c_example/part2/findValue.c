#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(void){

    int findvalue[10];
    int find;

    printf("Enter number : ");
    scanf("%d", &find);

    srand((unsigned int)time(NULL));

    for (int i = 0; i < 10; i++){
        findvalue[i] = rand() % 101;
        printf("%d, ", findvalue[i]);
    }
    printf("\n");
    int i;
    for (int i = 0; i < 10; i++){
        if (find == findvalue[i]){
            break;
        }
    }
    if (i < 10){
        printf("There is number %d, index is %d. \n", find, i);
    }
    else{
        printf("Unfortunately don't have. \n");
    }

    return 0;
}