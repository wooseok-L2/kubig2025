// It is source to print over score 60
#include <stdio.h>
#include <stdlib.h>


int main(int argc, char* argv[]){

    if(argc < 2){
        
        printf("Enter values");    
        return 0;
    }

    printf("score: %d --- %s \n", atoi(argv[1]), atoi(argv[1])>=60 ? "pass" : "fail");
    
    return 0;
}