#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define MAX 50
#define MAXC 100

int main(void){
    
    int max_input;
    int scores[max_input];
    int sum = 0;
    double avg;
    int cnt;

    printf("Enter length of array : ");
    scanf("%d", &max_input);

    srand((unsigned int)time(NULL));

    for (int i = 0; i < max_input; i++){
        scores[i] = rand() % (MAXC + 1);
        printf("%d, ", scores[i]);
        sum += scores[i];
    }
    printf("\n");
    avg = (double)sum / max_input;

    printf("average is %.2lf \n", avg);

    return 0;
}