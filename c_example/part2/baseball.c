#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#define MAX 3

int main(void){

    int tag[MAX] = {0};
    int num[MAX] = {0};
    char res[MAX] = {0};
    int s_count = 0;
    int b_count = 0;
    
    srand((unsigned int)time(NULL));
    for (int i = 0; i < MAX; i++){
        tag[i] = rand() % 10;
    }
    while(true){

        printf("Enter 3 num : ");
        
        for (int i = 0; i < MAX; i++){
            
            scanf("%d", &num[i]);
        }
         
        for (int i = 0; i < MAX; i++){

            for (int j = 0; j < MAX; j++){

                if (tag[i] == num[j]){
                    
                    if (i == j){

                        *res[i] = "strike";
                    }
                    else{
                        *res[i] = "ball";
                    }
                }

                if (*res[i] == "strike"){
                    s_count++;
                }
                else if (*res[i] == "ball"){
                    b_count++;
                }
            }
        }
        printf("%d strike. %d ball \n", s_count, b_count);
    }
    
}
