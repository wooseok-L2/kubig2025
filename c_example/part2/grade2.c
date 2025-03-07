#include <stdio.h>
#include <stdlib.h>


int main(int argc, char* argv[]){

    int score;
    if(argc < 2){
        
        printf("Enter values \n");    
        return 0;
    }

    score = atoi(argv[1]);

    if (score>100 || score<0){
        printf("Enter score again \n");
    }
    else{

        
        switch(score/10){
        case 10 : 
            printf("Fantastic \n");
        case 9 : 
            printf("score : %d === A \n", score);
            break;
            case 8 : 
            printf("score : %d === B \n", score);
            break;
            case 7 :
            printf("score : %d === C \n", score);
            break;
        case 6 :
            printf("score : %d === D \n", score);
            break;
            default :
            printf("score : %d === F \n", score);
        }
        
        
        return 0;
    }
}