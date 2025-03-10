#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

int main(void){

    char grades[] = {'F', 'F', 'F', 'F', 'F', 'F', 'D', 'C', 'B', 'A', 'A'} ;

    int score;
    char grade;

    while(true){
        printf("Enter your score : ");
        scanf("%d", &score);
        grade = 'F';

        if (score > 0 && score <= 100){
            grade = grades[score/10];
        }

        printf("score id %d --- %c \n", score, grade);
        printf("Enter 1000 for exit \n");
        if (score == 1000){
            break;
        }
    }
}