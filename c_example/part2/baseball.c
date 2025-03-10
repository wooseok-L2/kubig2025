#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>


int main(void){

    int question[3];
    int answer[3];
    srand(time(NULL));

    question[0] = rand() % 10;

    do{
        question[1] = rand() % 10;
    } while (question[0] == question[1]);

    do{
        question[2] = rand() % 10;
    } while (question[0] == question[2] || question[1] == question[2]);

     printf("%d %d %d \n", question[0], question[1], question[2]);
    int count = 0;

    while(true){
        
        // enter number
        printf("Enter number : \n Each number should not be same \n ");
        for (int i = 0; i < 3; i++){
            scanf("%d", &answer[i]);
        }

        // compare
        int strike = 0;
        int ball = 0;
        
        for (int i = 0; i < 3; i++){
            for (int j = 0; j < 3; j++){
                if (question[i] == answer[j]){
                    if (i == j){
                        strike++;
                    }
                    else ball++;
                }
            }
        }
        
        printf("Strike: %d, Ball: %d \n", strike, ball);
        count++;

        if (strike == 3){
            printf("%d Strike Out! your are win!!! \n", strike);
            break;
        }
    }
    printf("you tried only %d times! \n", count);
    return 0;
}